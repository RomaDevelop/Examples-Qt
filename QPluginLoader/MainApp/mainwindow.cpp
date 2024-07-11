#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSelect_plugin_triggered()
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cd("../bin/Plugins");
    QFile FilePlugin;
    QFileDialog dialog;
    dialog.setDirectory(dir);
    QString fileName=dialog.getOpenFileName();
    PluginInteface *currentPlugin=0;
    //fileName=dir.absolutePath()+"/" +fileName;
    QPluginLoader loader(dir.absoluteFilePath(fileName));
    QObject *obj=0;
    obj=qobject_cast<QObject *>(loader.instance());
    if(!obj)return;
    currentPlugin=qobject_cast<PluginInteface *>(obj);
    if(currentPlugin)ui->lineEdit->setText(currentPlugin->GetString());

}
