		QStatusBar *statusBar = new QStatusBar;
		QLabel *labeStBar = new QLabel;
		statusBar->addWidget(labeStBar);
		vLayout->addWidget(statusBar);

		QTextBrowser *tBrowserPtrForConnect = tBrowser;
		QObject::connect(btnClear, &QPushButton::clicked, [tBrowserPtrForConnect](){ tBrowserPtrForConnect->clear(); });
		QObject::connect(tBrowserPtrForConnect,&QTextBrowser::textChanged, [labeStBar](){
			labeStBar->setText("Предупреждений: " + QSn(Logs::WarningsCount()) + "\t\tОшибок: " + QSn(Logs::ErrorsCount()));
		});