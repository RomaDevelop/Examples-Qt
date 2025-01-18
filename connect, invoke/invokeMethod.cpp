QMetaObject::invokeMethod(&w, [&w, i](){
	w.textEdit->append(QSn(i));
});
// вроде бы даже потокобезопасно