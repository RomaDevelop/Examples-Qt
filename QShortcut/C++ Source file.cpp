	QShortcut *enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
	connect(enterShortcut, &QShortcut::activated, [](){ qdbg << "enterShortcut"; });