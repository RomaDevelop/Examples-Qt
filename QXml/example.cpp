QXmlStreamReader xmlReader("<div class=\"1\"><div class=\"2\">test</div></div>");
while (!xmlReader.atEnd())
{
	xmlReader.readNext();
	for(auto &attr:xmlReader.attributes())
		qdbg << xmlReader.name() << attr.name() << attr.value() << xmlReader.readElementText(QXmlStreamReader::IncludeChildElements);
}

https://evileg.com/ru/post/74/
https://habr.com/ru/articles/532436/
https://www.opennet.ru/docs/RUS/qt3_prog/c6631.html
https://pro-prof.com/archives/1496
