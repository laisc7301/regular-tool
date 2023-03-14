#include "regex_find.h"
#include "ui_regex_find.h"
#include <iostream>
#include <qDebug>
#include <QRegularExpression>
#include "global.h"
#include <QSettings>


regex_find::regex_find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_find)
{
    ui->setupUi(this);
    ui->textEdit_2->setVisible(false);
    //ui->pushButton->setVisible(false);

    ui->textEdit->setStyleSheet("selection-background-color: #0078d7;selection-color: white;");

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = mysetting->value("regexFind/RegularExpressionStr").toString();
    if(str1!="")ui->lineEdit->setText(str1);
    QString str2 = mysetting->value("regexFind/SearchStr").toString();
    if(str2!="")ui->textEdit->setText(str2);
}

regex_find::~regex_find()
{
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = ui->lineEdit->text();
    mysetting->setValue("regexFind/regularExpressionStr",str1);
    QString str2 = ui->textEdit->toPlainText();
    mysetting->setValue("regexFind/SearchStr",str2);
    delete ui;
}

void regex_find::on_pushButton_2_clicked()
{
    search();
    QString myRegularExpressionStr = ui->lineEdit->text();
    QRegularExpression regularExpression(myRegularExpressionStr);
    ui->textEdit->find(regularExpression,QTextDocument::FindBackward);
}

void regex_find::on_pushButton_3_clicked()
{
    search();
    QString myRegularExpressionStr = ui->lineEdit->text();
    QRegularExpression regularExpression(myRegularExpressionStr);
    ui->textEdit->find(regularExpression);
}

//void regex_find::on_pushButton_clicked()
//{
//    search();
//}


void regex_find::on_lineEdit_textChanged(const QString &arg1)
{
    regex_find_regularExpressionStr = ui->lineEdit->text();
    isRegexFind_RegularExpressionStrChange = true;
}


void regex_find::on_textEdit_textChanged()
{
    regex_find_SearchStr = ui->textEdit->toPlainText();
    isRegexFind_SearchStrChange = true;

}


void regex_find::search()
{

    QString myRegularExpressionStr = ui->lineEdit->text();
    QString myInputStr = ui->textEdit->toPlainText();

    QString myRegularExpressionStr2 = "("+myRegularExpressionStr+")";
    QRegularExpression regularExpression(myRegularExpressionStr2);
    myInputStr.replace(regularExpression,"<b id=\"result\">\\1</b>");
    myInputStr.replace("\n","<br/>");
    QString style = "<style>#result{color: red;background-color: yellow;}</style>";
    myInputStr = style + myInputStr;
    QString str1 = ui->textEdit->toHtml();
    ui->textEdit_2->setHtml(myInputStr);
    if(ui->textEdit->toHtml()!= ui->textEdit_2->toHtml()){
        ui->textEdit->setHtml(myInputStr);
    }



}

