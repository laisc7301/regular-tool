#ifndef REGEX_REPLACEMENT_H
#define REGEX_REPLACEMENT_H
#include "load_thread.h"
#include <QWidget>

namespace Ui {
class regex_replacement;
}

class regex_replacement : public QWidget
{
    Q_OBJECT

public:
    explicit regex_replacement(QWidget *parent = nullptr);
    ~regex_replacement();

    int id=0;
    void saveContent();
    QString regularExpression="";
    bool isRegularExpressionChange=false;
    QString replace="";
    bool isReplaceChange=false;
    QString replaceInput="";
    bool isReplaceInputChange=false;
    load_thread load2;
    void alwaysSaveContent();

public slots:
    void myload2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

    void on_toolButton_clicked();

private:
    Ui::regex_replacement *ui;
};

#endif // REGEX_REPLACEMENT_H
