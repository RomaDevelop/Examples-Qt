QDateTime curDateTime = QDateTime::currentDateTime();
QDateTime someDateTime = curDateTime;
qdbg << someDateTime.toString("yyyy.MM.dd hh:mm:ss"); // внимание, тут есть двоеточия! не годится в путь к папке!
qdbg << someDateTime.toString("yyyy.MM.dd hh:mm:ss.zzz"); // + микросекунды внимание, тут есть двоеточия! не годится в путь к папке!

// внимание! чтобы добавлять в имя файла не забыть убрать двоеточия!!!
qdbg << someDateTime.toString("yyyy.MM.dd hh_mm_ss");
