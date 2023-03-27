#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMdiArea>
#include <QSettings>
#include <QList>
#include <QWidget>
#include <QThread>
#include "mainwindow.h"

extern QString version;
extern MainWindow *myMainWindow;
extern QMdiArea *qmdiArea;
extern QSettings *myconfig;
extern QStringList tagList;
extern QList<QWidget*> widgetList;
extern int nextId;

#endif // GLOBAL_H


