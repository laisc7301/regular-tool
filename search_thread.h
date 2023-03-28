#ifndef SEARCH_THREAD_H
#define SEARCH_THREAD_H
#include <QThread>
#include <QString>

class search_thread : public QThread
{
    Q_OBJECT
public:
    search_thread();
    virtual void run();

    QString url;
    QString filter;
    QString regularExpression;

signals:
    void sendmsg(QString msg);
    void setProgressBar(int value);
    void finish();

private:
    void doSearch();
    QStringList getFileListUnderDir(const QString &dirPath2,const QString &filter2);
    QString getFileContentString(QString fileurl);
};

#endif // SEARCH_THREAD_H
