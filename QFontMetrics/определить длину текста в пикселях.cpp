QFontMetrics metrics(textEdit->font());  // QFontMetrics - целые числа, QFontMetricsF для более точных значений
QString line;
metrics.width(line);


btnAdd->setFixedWidth(QFontMetrics(btnAdd->font()).width(btnAdd->text()) + 10);