#ifndef REGULAR_FILE_REPLACEMENT_H
#define REGULAR_FILE_REPLACEMENT_H

#include "replacement_thread.h"
#include <QWidget>

namespace Ui {
class Regular_file_replacement;
}

class Regular_file_replacement : public QWidget
{
    Q_OBJECT

public:
    explicit Regular_file_replacement(QWidget *parent = nullptr);
    ~Regular_file_replacement();

public slots:
    void getmsg(QString msg);

    void setProgressBar(int value);

    void threadFinish();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_toolButton_clicked();

private:
    Ui::Regular_file_replacement *ui;

    replacement_thread thread;
};

#endif // REGULAR_FILE_REPLACEMENT_H
