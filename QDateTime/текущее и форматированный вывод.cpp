QDateTime curDateTime = QDateTime::currentDateTime();
QDateTime someDateTime = curDateTime;
qdbg << someDateTime.toString("yyyy.MM.dd hh:mm:ss"); // внимание, тут есть двоеточия!

// внимание! чтобы добавлять в имя файла не забыть убрать двоеточия!!!
qdbg << someDateTime.toString("yyyy.MM.dd hh_mm_ss");
