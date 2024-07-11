#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTextCodec>

QTextCodec *codec1251 = QTextCodec::codecForName("Windows-1251");
QString vers_str;

//QString str = codec1251->toUnicode(ba);
//QMessageBox::information(this,"",str);

for(int i=2; i<8; i++) { vers_strBA += msg.data[i]; vers_str += QString::number(msg.data[i]) + " "; }

qdbg << "\nФрагмент версии: " + codec1251->toUnicode(vers_strBA) +
		"\n----------------------------------------------------------";
