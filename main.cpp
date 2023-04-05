#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include "global.h"

QString version = "v1.4.7";
MainWindow *myMainWindow;
QMdiArea *qmdiArea = NULL;
QSettings *myconfig = new QSettings("config.ini", QSettings::IniFormat);
QStringList tagList;
QList<QWidget*> widgetList;
int nextId=0;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    myMainWindow=&w;
    w.show();
    return a.exec();
}
