#ifndef SAVE_THREAD_H
#define SAVE_THREAD_H
#include <QThread>
#include <QString>

class save_thread : public QThread
{
    Q_OBJECT
public:
    save_thread();
    virtual void run();

};

#endif // SAVE_THREAD_H
