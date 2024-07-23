QProcess cmdProcess;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{

	cmdProcess.start("cmd.exe");
	if (!cmdProcess.waitForStarted()) {
		qWarning() << "Failed to start cmd process";
		return;
	}

//	//cmdProcess.setReadChannelMode(QProcess::ForwardedChannels);
//	connect(&cmdProcess, &QProcess::readyReadStandardOutput, []() {
//		QString res = cmdProcess.readAllStandardOutput();
//		qdbg << res;
//		qdbg << "end";
//	});

//	connect(&cmdProcess, &QProcess::readyReadStandardError, []() {
//		QString res = cmdProcess.readAllStandardError();
//		qdbg << res;
//		qdbg << "end";
//	});

	QStringList commands;
	commands += "git status\n";
	commands += "cd C:/Work/C++/IncludeParser\n";
	commands += "git status\n";
	commands += "exit\n";

	// Выполняем команды
	for (const auto& command : commands) {
		// Добавляем команду к процессу
		cmdProcess.write(command.toUtf8());
		cmdProcess.waitForBytesWritten();
		cmdProcess.waitForReadyRead();
		qdbg << "error " << QString(cmdProcess.readAllStandardError());
		qdbg << "output " << QString(cmdProcess.readAllStandardOutput());
	}

	// Ожидаем завершения процесса
	cmdProcess.waitForFinished();