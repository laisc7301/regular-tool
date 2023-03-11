#include "mainwindow.h"

#include <QApplication>

QString regex_replacement_regularExpression = "";
QString regex_replacement_replace = "";
QString regex_replacement_replaceInput = "";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
