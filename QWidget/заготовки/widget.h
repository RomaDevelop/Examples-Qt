#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
	Q_OBJECT
public:
	explicit Widget(QWidget *parent = nullptr);
	~Widget();

private:
	void closeEvent (QCloseEvent *event) override;
	//void resizeEvent(QResizeEvent * event) override { }
	//void moveEvent(QMoveEvent * event) override { }
	QString settingsFile;
	void SaveSettings();
	void LoadSettings();

};

#endif // WIDGET_H
