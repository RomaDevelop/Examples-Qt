#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QtCharts>

#include "MyQShortings.h"
#include "MyCppDifferent.h"
#include "thread_box.h"

#include "MyQTimer.h"
#include "MyQDialogs.h"
#include "PlatformDependent.h"

#include <QApplication>
#include <QProgressDialog>
#include <QThread>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Widget window;
	window.show();

	window.TestSignals();

	return app.exec();
}
