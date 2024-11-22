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


// вывод поверх всех окон
void MyQWidgetPlatform::SetTopMost(QWidget *w, bool topMost)
{
	HWND hwnd = reinterpret_cast<HWND>(w->winId());
	SetWindowPos(hwnd, topMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
					 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}
