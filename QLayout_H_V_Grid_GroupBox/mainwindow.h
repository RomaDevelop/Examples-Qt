#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private slots:
    void on_pushButton_clicked1();

};

#endif // MAINWINDOW_H
