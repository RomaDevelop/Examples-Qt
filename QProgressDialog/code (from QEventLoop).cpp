void Programm::StartProgrammClosing()
{
	if(HasWorkingProtocolsThreads())
	{
		const int maxWaitInterval = 3000;
		const int waitForInterupt = 2000;
		const int waitForInteruptStep = 10;

		QProgressDialog *progressDialog {};
		QEventLoop loop;
		QDateTime startWait = QDateTime::currentDateTime();
		QTimer t;
		QObject::connect(&t, &QTimer::timeout, &t, [this, &loop, &t, &startWait, &progressDialog](){
			bool hasWorkingThreads = HasWorkingProtocolsThreads();
			if(not hasWorkingThreads)
			{
				t.stop();

				loop.quit();
				return;
			}

			if(startWait.msecsTo(QDateTime::currentDateTime()) > maxWaitInterval)
			{
				t.stop();

				Error("StartProgrammClosing: timeout for threads to finish has expired");
				StartInterruptProtocolsThreads();
				MyQTimer::DeferredCall(waitForInterupt, waitForInteruptStep, *controlPanel,
					[this](){ return !HasWorkingProtocolsThreads(); },
					[&loop](){ loop.quit(); }
				);
				return;
			}

			if(not progressDialog)
			{
				progressDialog = new QProgressDialog("Закрытие программы. Пожалуйста, подождите...",
													 QString(), 0, 0, controlPanel.get());
				// Установка progressDialog модальным
				// (нужно ибо делается show, нельзя делать exec, нужно чтобы код пошел выполняться дальше)
				progressDialog->setWindowModality(Qt::ApplicationModal);
				progressDialog->setCancelButton(nullptr);
				progressDialog->setWindowFlag(Qt::WindowCloseButtonHint, false);
				progressDialog->show();
			}
		});
		t.start(100);

		loop.exec();
	}

	if(deleter) deleter();
	else Error("should call deleter, but deleter is null");
}