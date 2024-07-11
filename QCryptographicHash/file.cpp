	QCryptographicHash hash(QCryptographicHash::Md5);
	QFile file("F:/C++/CAN/ProtocolMy/Протокол1.xlsx");
	file.open(QFile::ReadOnly);
	hash.addData(&file);
	qdbg << hash.result();
