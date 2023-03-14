#include "regex_match.h"
#include "ui_regex_match.h"
#include "global.h"

#include <QRegularExpression>
#include <qDebug>
#include <QSettings>

#include <iostream>

regex_match::regex_match(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_match)
{
    ui->setupUi(this);


    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = mysetting->value("regexMatch/regularExpressionStr").toString();
    if(str1!="")ui->lineEdit->setText(str1);
    QString str2 = mysetting->value("regexMatch/inputStr").toString();
    if(str2!="")ui->textEdit->setText(str2);
}

regex_match::~regex_match()
{
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = ui->lineEdit->text();
    mysetting->setValue("regexMatch/regularExpressionStr",str1);
    QString str2 = ui->textEdit->toPlainText();
    mysetting->setValue("regexMatch/inputStr",str2);
    delete ui;
}

void regex_match::on_pushButton_clicked()
{
    QString regularExpressionStr = ui->lineEdit->text();
    if(regularExpressionStr==""){
        ui->textEdit_2->setText("共找到 0 处匹配：");
        return;
    }
    QString inputStr = ui->textEdit->toPlainText();
    //QString pattern("23[0-9]");
    QRegularExpression regularExpression(regularExpressionStr);
    //QString inputStr("12392345");

    QRegularExpressionMatch match;
    int startIndex = 0;
    int length = 0;
    int endIndex = 0;
    QStringList result1;
    QString result2 = "";
    for(;endIndex < inputStr.length();){
        match = regularExpression.match(inputStr, endIndex);
        if(match.hasMatch()) {
            startIndex = match.capturedStart();
            length = match.capturedLength();
            endIndex = match.capturedEnd();
            QString result0 = inputStr.mid(startIndex,length);
            //qDebug()<<result0;
            result1<<result0;
        }
        else{
            break;
        }

    }
    //qDebug()<<result1.length();
    QString result1_length = QString::number(result1.length());
    result2 += "共找到 " + result1_length + " 处匹配：";
    QStringListIterator result1_Iterator(result1);
    for(;result1_Iterator.hasNext();){
        result2 += "\n" + result1_Iterator.next();
    }
    ui->textEdit_2->setText(result2);
}


void regex_match::on_lineEdit_textChanged(const QString &arg1)
{
    regex_match_regularExpressionStr = ui->lineEdit->text();
    isRegexMatch_RegularExpressionStrChange = true;
}


void regex_match::on_textEdit_textChanged()
{
    regex_match_inputStr = ui->textEdit->toPlainText();
    isRegexMatch_InputStrChange = true;
}

