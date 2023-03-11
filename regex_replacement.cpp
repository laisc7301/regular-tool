#include "regex_replacement.h"
#include "ui_regex_replacement.h"

#include "global.h"

#include <iostream>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QSettings>
#include <QClipboard>
#include <QTimer>

QTimer *timer = new QTimer();

bool isRegularExpressionChange = false;
bool isReplaceChange = false;
bool isReplaceInputChange = false;

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

    connect(timer,&QTimer::timeout,this,[=](){

        //std::cout << "time" << std::endl;

        if(isRegularExpressionChange){
            isRegularExpressionChange = false;
            QString str1 = ui->lineEdit->text();
            mysetting->setValue("regularExpression/regularExpression",str1);
        }
        if(isReplaceChange){
            isReplaceChange = false;
            QString str1 = ui->lineEdit_2->text();
            mysetting->setValue("regularExpression/replace",str1);
        }
        if(isReplaceInputChange){
            isReplaceInputChange = false;
            QString str1 = ui->textEdit->toPlainText();
            mysetting->setValue("regularExpression/replaceInput",str1);
        }
    });
    timer->start(1000);
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

    std::cout << "unload" << std::endl;
    std::cout << str1.toStdString() << std::endl;

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
    isRegularExpressionChange = true;
    regex_replacement_regularExpression = ui->lineEdit->text();
}


void regex_replacement::on_lineEdit_2_textChanged(const QString &arg1)
{
    isReplaceChange = true;
    regex_replacement_replace = ui->lineEdit_2->text();
}


void regex_replacement::on_textEdit_textChanged()
{
    isReplaceInputChange = true;
    regex_replacement_replaceInput = ui->textEdit->toPlainText();
}

