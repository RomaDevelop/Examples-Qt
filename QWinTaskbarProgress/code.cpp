QT += winextras

#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

QWinTaskbarProgress *taskbarButtonProgress = nullptr;

QTimer::singleShot(100,[this](){
	QWinTaskbarButton *taskbarButton = new QWinTaskbarButton(this);
	taskbarButton->setWindow(this->windowHandle());
	taskbarButtonProgress = taskbarButton->progress();
	taskbarButtonProgress->setMinimum(0);
	taskbarButtonProgress->setMaximum(100);
	taskbarButtonProgress->setVisible(true);
});
		
if(taskbarButtonProgress) taskbarButtonProgress->setValue(value);

// полный минимальный пример:

#include <QApplication>
#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include <QVBoxLayout>
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
		progressBar = new QProgressBar(this);
		progressBar->setRange(0, 100);
		setCentralWidget(progressBar);

		// Запускаем таймер для обновления прогресса
		QTimer *timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
		timer->start(100); // обновление каждые 100 мс

		QTimer::singleShot(100,[this](){
			QWinTaskbarButton *taskbarButton = new QWinTaskbarButton(this);
			taskbarButton->setWindow(this->windowHandle());
			taskbarButtonProgress = taskbarButton->progress();
			taskbarButtonProgress->setMinimum(0);
			taskbarButtonProgress->setMaximum(100);
			taskbarButtonProgress->setVisible(true);
		});


	}

private slots:
	void updateProgress() {
		int value = progressBar->value() + 1;
		if (value > 100) {
			value = 0; // сброс прогресса
		}
		progressBar->setValue(value);
		setWindowTitle(QString("Progress: %1%").arg(value)); // обновление заголовка окна

		if(taskbarButtonProgress) taskbarButtonProgress->setValue(value);
	}

private:
	QProgressBar *progressBar;
	QWinTaskbarProgress *taskbarButtonProgress{};
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.resize(300, 100);
	window.show();

	return app.exec();
}