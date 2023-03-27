#ifndef REGEX_MATCH_H
#define REGEX_MATCH_H

#include "load_thread.h"
#include <QWidget>

namespace Ui {
class regex_match;
}

class regex_match : public QWidget
{
    Q_OBJECT

public:
    explicit regex_match(QWidget *parent = nullptr);
    ~regex_match();

    int id=0;
    void saveContent();
    QString regularExpressionStr="";
    bool isRegularExpressionStrChange=false;
    QString inputStr="";
    bool isInputStrChange=false;
    load_thread load2;
    void alwaysSaveContent();

public slots:
    void myload2();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

    void on_toolButton_clicked();

private:
    Ui::regex_match *ui;
};

#endif // REGEX_MATCH_H
