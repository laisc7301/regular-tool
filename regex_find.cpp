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
//    QString str = ui->lineEdit->text();
//    ui->textEdit->find(str);

//    QTextCursor cursor = ui->textEdit->textCursor();

//    std::cout << cursor.columnNumber() << std::endl;


//std::cout<<ui->textEdit->toPlainText().toStdString()<< std::endl;

    ui->textEdit->setHtml("<style>#test{color: red;}</style><b id=\"test\">123</b>\n333");
    //ui->textEdit->setText("123\n333");
    qDebug()<<ui->textEdit->toPlainText();
}


void regex_find::on_pushButton_clicked()
{
    QString myRegularExpressionStr = ui->lineEdit->text();
    QString myInputStr = ui->textEdit->toPlainText();

    if(false){
    myInputStr = "A <i>bon mot</i>.";
    myRegularExpressionStr="<i>([^<]*)</i>";
    QRegularExpression regularExpression(myRegularExpressionStr);
    myInputStr.replace(regularExpression,"\\emph{\\1}");
    std::cout<<myInputStr.toStdString()<<std::endl;
    }
    QString myRegularExpressionStr2 = "("+myRegularExpressionStr+")";
}


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

