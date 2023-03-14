#include "regex_find.h"
#include "ui_regex_find.h"
#include <iostream>
#include <qDebug>

regex_find::regex_find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_find)
{
    ui->setupUi(this);
}

regex_find::~regex_find()
{
    delete ui;
}

void regex_find::on_pushButton_2_clicked()
{
//    QString str = ui->lineEdit->text();
//    ui->textEdit->find(str);

//    QTextCursor cursor = ui->textEdit->textCursor();

//    std::cout << cursor.columnNumber() << std::endl;


//std::cout<<ui->textEdit->toPlainText().toStdString()<< std::endl;
    qDebug()<<ui->textEdit->toPlainText();
}

