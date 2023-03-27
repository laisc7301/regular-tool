#ifndef LOAD_THREAD_H
#define LOAD_THREAD_H
#include <QThread>
#include <QString>

class load_thread : public QThread
{
    Q_OBJECT
public:
    load_thread();
    virtual void run();

signals:
    void loadback();
};

#endif // LOAD_THREAD_H
