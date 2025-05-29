читаемый вид:
hash.result().toHex()

хеш файла:
QCryptographicHash hash(QCryptographicHash::Md5);
QFile file("F:/C++/CAN/ProtocolMy/Протокол1.xlsx");
file.open(QFile::ReadOnly);
hash.addData(&file);
qdbg << hash.result();

хеш строки:
QCryptographicHash hash(QCryptographicHash::Md5);
hash.addData("test password ~csdjh!~@$34cs");
qdbg << hash.result().toHex();

