#include <QCoreApplication>

#include "main.h"

#include "QTimer"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SharedMemoryWatcher watcher;
	QTimer::singleShot(3000,[&](){
		watcher.start();
	});

	QTimer *t = new QTimer;
	QObject::connect(t, &QTimer::timeout, [](){
		static QSharedMemory sharedMemory("MySharedMemoryKey");
		static QSystemSemaphore semaphore("MySemaphoreKey", 0, QSystemSemaphore::Open);

		QBuffer buffer;
		buffer.open(QBuffer::WriteOnly);
		QDataStream out(&buffer);
		static int counter=0;
		out << counter << QString("dffff");
		qdbg << "sent" << counter << "dffff";
		counter++;

		//out << QString("dffff") << QSn(a++); // для повторной отправки нужно дважды считывать при получении in >> result;

		int size = buffer.size();

		// Создаем сегмент один раз, если еще не создан
		if (!sharedMemory.isAttached()) {
			if (!sharedMemory.create(size)) {
				sharedMemory.attach();
			}
		}

		sharedMemory.lock();
		// Если размер текста вырос, нужно пересоздать сегмент (редкий случай)
		if (sharedMemory.size() < size) {
			sharedMemory.unlock();
			sharedMemory.detach();
			sharedMemory.create(size);
			sharedMemory.lock();
		}

		memcpy(sharedMemory.data(), buffer.data().constData(), size);
		sharedMemory.unlock();

		semaphore.release(); // Сигнализируем
	});
	t->start(500);

	return a.exec();
}
