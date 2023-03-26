#include "regex_replacement.h"
#include "ui_regex_replacement.h"

#include "global.h"

#include <iostream>
#include <qDebug>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QSettings>
#include <QClipboard>
#include <QTimer>

//QTimer *timer = new QTimer();

regex_replacement::regex_replacement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_replacement)
{
    ui->setupUi(this);

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = mysetting->value("regularExpression/regularExpression").toString();
    if(str1!="")ui->lineEdit->setText(str1);
    QString str2 = mysetting->value("regularExpression/replace").toString();
    if(str2!="")ui->lineEdit_2->setText(str2);
    QString str3 = mysetting->value("regularExpression/replaceInput").toString();
    if(str3!=""){
        //std::cout << "not null" << std::endl;
        ui->textEdit->setText(str3);
    }

//    connect(timer,&QTimer::timeout,this,[=](){

//        //std::cout << "time" << std::endl;

//        if(isRegexReplacement_RegularExpressionChange){
//            isRegexReplacement_RegularExpressionChange = false;
//            QString str1 = ui->lineEdit->text();
//            mysetting->setValue("regularExpression/regularExpression",str1);
//        }
//        if(isRegexReplacement_ReplaceChange){
//            isRegexReplacement_ReplaceChange = false;
//            QString str1 = ui->lineEdit_2->text();
//            mysetting->setValue("regularExpression/replace",str1);
//        }
//        if(isRegexReplacement_ReplaceInputChange){
//            isRegexReplacement_ReplaceInputChange = false;
//            QString str1 = ui->textEdit->toPlainText();
//            mysetting->setValue("regularExpression/replaceInput",str1);
//        }
//    });
//    timer->start(1000);
}

regex_replacement::~regex_replacement()
{
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString str1 = ui->lineEdit->text();
    mysetting->setValue("regularExpression/regularExpression",str1);
    QString str2 = ui->lineEdit_2->text();
    mysetting->setValue("regularExpression/replace",str2);
    QString str3 = ui->textEdit->toPlainText();
    mysetting->setValue("regularExpression/replaceInput",str3);


    myconfig->setValue("mainwindow/tagList",tagList.join(","));
    delete ui;
}

void regex_replacement::on_pushButton_clicked()
{
    QString str1 = ui->lineEdit->text();
    QString str2 = ui->lineEdit_2->text();
    QString str3 = ui->textEdit->toPlainText();
    QString str = str3;
    str.replace(QRegularExpression(str1),str2);
    ui->textEdit_2->setText(str);
}


void regex_replacement::on_pushButton_2_clicked()
{
    QString str4 = ui->textEdit_2->toPlainText();
    QClipboard *clip = QApplication::clipboard();
    clip->setText(str4);
}


void regex_replacement::on_lineEdit_textChanged(const QString &arg1)
{
    regex_replacement_regularExpression = ui->lineEdit->text();
    isRegexReplacement_RegularExpressionChange = true;
}


void regex_replacement::on_lineEdit_2_textChanged(const QString &arg1)
{
    regex_replacement_replace = ui->lineEdit_2->text();
    isRegexReplacement_ReplaceChange = true;
}


void regex_replacement::on_textEdit_textChanged()
{
    regex_replacement_replaceInput = ui->textEdit->toPlainText();
    isRegexReplacement_ReplaceInputChange = true;
}


void regex_replacement::on_toolButton_clicked()
{
    myMainWindow->removeid(id);
    qmdiArea->closeActiveSubWindow();
}
void regex_replacement::saveContent(){

}

