#ifndef REGEX_FIND_H
#define REGEX_FIND_H
#include "load_thread.h"
#include <QWidget>

namespace Ui {
class regex_find;
}

class regex_find : public QWidget
{
    Q_OBJECT

public:
    explicit regex_find(QWidget *parent = nullptr);
    ~regex_find();

    int id=0;
    QString regularExpressionStr="";
    bool isRegularExpressionStrChange=false;
    QString searchStr="";
    bool isSearchStrChange=false;
    void saveContent();
    load_thread load2;

public slots:
    void myload2();

private slots:
    void on_pushButton_2_clicked();

    //void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

    void on_pushButton_3_clicked();

    void search();

    void on_toolButton_clicked();

private:
    Ui::regex_find *ui;
};

#endif // REGEX_FIND_H
