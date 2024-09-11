#include <QTextCodec>

	QString encoding = "Windows-1251";

	//закодирование
	QString text = "АБВГДабвгдABCDEabcde";

	QByteArray byteArr = QTextCodec::codecForName(encoding.toUtf8())->fromUnicode(text);

	vector<int> bytes;
	for(int i=0; i<byteArr.size(); i++)
	{
		bytes.push_back(byteArr[i]);
		if(bytes.back() < 0 ) bytes.back() += 256;
		// если выход должен быть unsigned, нужно + 256 нужно потому что QByteArray содержит signed char и значения больше 127 отрицательны
	}
	qdbg << bytes;

	//раскодирование
	byteArr.clear();
	for(auto &byte:bytes)
	{
		int byteInt = byte;
		if(byteInt > 127) byteInt -= 256; // причина аналогична выше для +256
		byteArr.push_back(byteInt);
	}
	QString newValue = QTextCodec::codecForName(encoding.toUtf8())->toUnicode(byteArr);
	qdbg << newValue;
