
#include <iostream>
using namespace std;

#include <QDomDocument>
#include <QDebug>

int main()
{
	QDomDocument doc;
	QDomElement root = doc.createElement("MyML");
	doc.appendChild(root);

	QDomElement tag = doc.createElement("Greeting");
	root.appendChild(tag);
	tag.setAttribute("11","22\"sdvsdv\"fvdfbdfb\n");

	QDomText t = doc.createTextNode("Hello World");
	tag.appendChild(t);

	//QDomAttr attr;
	root.setAttribute("1","2");


	cout << doc.toString().toStdString();
	
	QString errMsg = "no error";
	int errLine = -1, errCol = -1;
	cout << doc.setContent(QString("<doc><O1/><O2/><O3/></doc>"), &errMsg, &errLine, &errCol) << endl;
	cout << doc.toString().toStdString();
	cout << QString("ConfigFile::Constructor errMsg: " + errMsg).toStdString() << endl;
	cout << QString("ConfigFile::Constructor errLine: " + QString::number(errLine)).toStdString() << endl;
	cout << QString("ConfigFile::Constructor errCol: " + QString::number(errCol)).toStdString() << endl;

	return 0;
}


//импорт элемента
void ToString(const QDomElement &element)
{
	QDomDocument tmpDoc;
	auto importedNode = tmpDoc.importNode(element,true);
	tmpDoc.appendChild(importedNode);
}