#ifndef MAINWINDOW_THREAD_H
#define MAINWINDOW_THREAD_H
#include <QThread>
#include <QString>

class mainwindow_thread : public QThread
{
    Q_OBJECT
public:
    mainwindow_thread();
    virtual void run();
};

#endif // MAINWINDOW_THREAD_H
