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

#include "load_thread.h"


//QTimer *timer = new QTimer();

regex_replacement::regex_replacement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_replacement)
{
    ui->setupUi(this);
    QObject::connect(&load2, SIGNAL(loadback()), this, SLOT(myload2()));
    load2.start();


}

regex_replacement::~regex_replacement()
{
    //alwaysSaveContent();
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
    regularExpression = ui->lineEdit->text();
    isRegularExpressionChange = true;
}


void regex_replacement::on_lineEdit_2_textChanged(const QString &arg1)
{
    replace = ui->lineEdit_2->text();
    isReplaceChange = true;
}


void regex_replacement::on_textEdit_textChanged()
{
    replaceInput = ui->textEdit->toPlainText();
    isReplaceInputChange = true;
}


void regex_replacement::saveContent(){
    if (isRegularExpressionChange){
        isRegularExpressionChange=false;
        QString configName = QString::number(id)+"-regularReplace/regularExpression";
        myconfig->setValue(configName,regularExpression);
    }
    if (isReplaceChange){
        isReplaceChange=false;
        QString configName = QString::number(id)+"-regularReplace/replace";
        myconfig->setValue(configName,replace);
    }
    if (isReplaceInputChange){
        isReplaceInputChange=false;
        QString configName = QString::number(id)+"-regularReplace/replaceInput";
        myconfig->setValue(configName,replaceInput);
    }
}


void regex_replacement::alwaysSaveContent(){

        QString configName = QString::number(id)+"-regularReplace/regularExpression";
        myconfig->setValue(configName,regularExpression);

        QString configName2 = QString::number(id)+"-regularReplace/replace";
        myconfig->setValue(configName2,replace);

        QString configName3 = QString::number(id)+"-regularReplace/replaceInput";
        myconfig->setValue(configName3,replaceInput);

}
void regex_replacement::myload2()
{

    QString str1 = myconfig->value(QString::number(id)+"-regularReplace/regularExpression").toString();
    if(str1!="")ui->lineEdit->setText(str1);
    QString str2 = myconfig->value(QString::number(id)+"-regularReplace/replace").toString();
    if(str2!="")ui->lineEdit_2->setText(str2);
    QString str3 = myconfig->value(QString::number(id)+"-regularReplace/replaceInput").toString();
    if(str3!=""){
        //std::cout << "not null" << std::endl;
        ui->textEdit->setText(str3);
    }
}

void regex_replacement::closeEvent(QCloseEvent *event)
{

    myMainWindow->removeid(id);

}
