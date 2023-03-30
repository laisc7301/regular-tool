#ifndef REGULAR_FILE_SEARCH_H
#define REGULAR_FILE_SEARCH_H

#include "load_thread.h"
#include "search_thread.h"
#include <QWidget>

namespace Ui {
class Regular_file_search;
}

class Regular_file_search : public QWidget
{
    Q_OBJECT

public:
    explicit Regular_file_search(QWidget *parent = nullptr);
    ~Regular_file_search();

    int id=0;

    QString regularExpressionStr="";
    bool isRegularExpressionStrChange=false;
    QString fileExtension="";
    bool isFileExtensionChange=false;

    void saveContent();
    void alwaysSaveContent();
    load_thread load2;
    search_thread searchThread;

    QString myURL="";
    bool isMyURLChange=false;

    void search();

public slots:
    void getmsg(QString msg);

    void setProgressBar(int value);

    void threadFinish();

private slots:
    void closeEvent(QCloseEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    QStringList getFileListUnderDir(const QString &dirPath,const QString &filter);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void myload2();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Regular_file_search *ui;
};

#endif // REGULAR_FILE_SEARCH_H
