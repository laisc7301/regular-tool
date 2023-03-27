#include "regex_find.h"
#include "ui_regex_find.h"
#include <iostream>
#include <qDebug>
#include <QRegularExpression>
#include "global.h"
#include <QSettings>
#include "load_thread.h"

regex_find::regex_find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_find)
{
    ui->setupUi(this);
//    QImage image("close.png");
//    ui->label_2->setPixmap(QPixmap::fromImage(image));


    ui->textEdit_2->setVisible(false);
    //ui->pushButton->setVisible(false);

    ui->textEdit->setStyleSheet("selection-background-color: #0078d7;selection-color: white;");

//    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
//    QString str1 = mysetting->value("regexFind/RegularExpressionStr").toString();
//    if(str1!="")ui->lineEdit->setText(str1);
//    QString str2 = mysetting->value("regexFind/SearchStr").toString();
//    if(str2!="")ui->textEdit->setText(str2);


    QObject::connect(&load2, SIGNAL(loadback()), this, SLOT(myload2()));

    load2.start();
}

regex_find::~regex_find()
{
//    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
//    QString str1 = ui->lineEdit->text();
//    mysetting->setValue("regexFind/regularExpressionStr",str1);
//    QString str2 = ui->textEdit->toPlainText();
//    mysetting->setValue("regexFind/SearchStr",str2);

    //myconfig->setValue("mainwindow/tagList",tagList.join(","));
    //myMainWindow->saveTag();
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
    regularExpressionStr = ui->lineEdit->text();
    isRegularExpressionStrChange = true;
//    save_thread saveThread;
//    saveThread.threadId=nextThreadId++;
//    threadList.append(&saveThread);
//    QString idString = QString::number(id);
//    saveThread.configName=idString+"regexFind/RegularExpressionStr";
//    saveThread.configContent=ui->lineEdit->text();
//    saveThread.start();
}


void regex_find::on_textEdit_textChanged()
{
    searchStr = ui->textEdit->toPlainText();
    isSearchStrChange = true;

//    save_thread saveThread;
//    saveThread.threadId=nextThreadId++;
//    threadList.append(&saveThread);
//    QString idString = QString::number(id);
//    saveThread.configName=idString+"regexFind/SearchStr";
//    saveThread.configContent=ui->textEdit->toPlainText();
//    saveThread.start();

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
        //qDebug()<<"change!";
    }



}


void regex_find::on_toolButton_clicked()
{
    myMainWindow->removeid(id);

    qmdiArea->closeActiveSubWindow();
}

void regex_find::saveContent(){
    if (isRegularExpressionStrChange){
        isRegularExpressionStrChange=false;
        QString configName = QString::number(id)+"-regexFind/RegularExpressionStr";
        myconfig->setValue(configName,regularExpressionStr);
    }
    if (isSearchStrChange){
        isSearchStrChange=false;
        QString configName = QString::number(id)+"-regexFind/SearchStr";
        myconfig->setValue(configName,searchStr);
    }
}

void regex_find::alwaysSaveContent(){

        QString configName = QString::number(id)+"-regexFind/RegularExpressionStr";
        myconfig->setValue(configName,regularExpressionStr);

        QString configName2 = QString::number(id)+"-regexFind/SearchStr";
        myconfig->setValue(configName2,searchStr);

}


void regex_find::myload2()
{
    QString str1 = myconfig->value(QString::number(id)+"-regexFind/RegularExpressionStr").toString();
    if(str1!="")ui->lineEdit->setText(str1);
    regularExpressionStr = str1;
    QString str2 = myconfig->value(QString::number(id)+"-regexFind/SearchStr").toString();
    if(str2!="")ui->textEdit->setText(str2);
    searchStr = str2;
}
