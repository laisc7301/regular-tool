#ifndef REPLACEMENT_THREAD_H
#define REPLACEMENT_THREAD_H
#include <QThread>
#include <QString>
//#include <QTextEdit>

class replacement_thread : public QThread
{
    Q_OBJECT
public:
    replacement_thread();
    virtual void run();
    void stop();

    QString url;
    QString filter;
    QString regularExpression;
    QString replace;


signals:
    void sendmsg(QString msg);
    void setProgressBar(int value);
    void finish();
private:
    void doReplace();
    void writeFile(const QString &url,const QString &content);
    QStringList getFileListUnderDir(const QString &dirPath,const QString &filter);
    QString getfileContent(const QString &url);
};

#endif // REPLACEMENT_THREAD_H
