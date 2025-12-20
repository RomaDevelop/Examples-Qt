#ifndef MAIN_H
#define MAIN_H

#include <QSharedMemory>
#include <QThread>
#include <QDebug>
#include <QSystemSemaphore>
#include <QBuffer>
#include <QDataStream>

#include "MyQShortings.h"

// Класс-наблюдатель для работы в отдельном потоке
class SharedMemoryWatcher : public QThread {
	Q_OBJECT
public:
	void run() override {
		// Ключи должны совпадать в обеих программах
		const char* key = "MySharedMemoryKey";
		const char* semKey = "MySemaphoreKey";

		QSharedMemory sharedMemory(key);
		// Семафор с начальным значением 0 (блокирует сразу)
		QSystemSemaphore semaphore(semKey, 0, QSystemSemaphore::Open);

		while (!isInterruptionRequested()) {
			// Ждем сигнала от второй программы (блокирующая операция)
			semaphore.acquire();

			if (sharedMemory.attach()) {
				sharedMemory.lock();

				// Читаем данные через QDataStream (безопасно для QString)
				QBuffer buffer;
				buffer.setData((const char*)sharedMemory.constData(), sharedMemory.size());
				buffer.open(QBuffer::ReadOnly);
				QDataStream in(&buffer);

				int counter;
				in >> counter;
				QString result;
				in >> result;

				qdbg << "get" << counter << result;

				sharedMemory.unlock();
				sharedMemory.detach();
			}
		}
	}
};

#endif // MAIN_H
