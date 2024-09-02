void flashTaskbarIcon(bool start)
{
	qDebug() << "flashTaskbarIcon";
	FLASHWINFO flashInfo;
	flashInfo.cbSize = sizeof(FLASHWINFO);
	flashInfo.hwnd = (HWND)winId();
	flashInfo.dwFlags = start ? (FLASHW_ALL | FLASHW_TIMERNOFG) : FLASHW_STOP;
	flashInfo.uCount = 0;
	flashInfo.dwTimeout = 0;
	FlashWindowEx(&flashInfo);
}