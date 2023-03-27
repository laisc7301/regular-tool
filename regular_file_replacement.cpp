#include "regular_file_replacement.h"
#include "ui_regular_file_replacement.h"
#include "replacement_thread.h"
#include "global.h"

#include <QTextEdit>
#include <QFileDialog>
#include <QThread>
#include <QSettings>
#include <QMessageBox>

Regular_file_replacement::Regular_file_replacement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regular_file_replacement)
{
    ui->setupUi(this);
    QObject::connect(&thread, SIGNAL(sendmsg(QString)), this, SLOT(getmsg(QString)));
    QObject::connect(&thread, SIGNAL(setProgressBar(int)), this, SLOT(setProgressBar(int)));
    QObject::connect(&thread, SIGNAL(finish()), this, SLOT(threadFinish()));
    QObject::connect(&load2, SIGNAL(loadback()), this, SLOT(myload2()));
    load2.start();
}

Regular_file_replacement::~Regular_file_replacement()
{

    delete ui;
}

void Regular_file_replacement::getmsg(QString msg)
{
    //qDebug()<<msg;
    ui->textEdit->append(msg);
}
void Regular_file_replacement::setProgressBar(int value)
{
    ui->progressBar->setValue(value);

}

void Regular_file_replacement::threadFinish(){
    ui->pushButton_2->setEnabled(true);
}





void Regular_file_replacement::on_pushButton_clicked()
{
    QString filename = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(filename);
}


void Regular_file_replacement::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text()=="")return;

    QMessageBox box;
    box.setWindowTitle(tr("警告"));
    box.setIcon(QMessageBox::Warning);
    box.setText(tr("此操作将覆盖目录下所有文件，确定继续？"));
    QPushButton *yesBtn = box.addButton(tr("是(&Y)"),
                                        QMessageBox::YesRole);
    QPushButton *noBtn = box.addButton(tr("否(&N)"),
                                       QMessageBox::NoRole);
    box.exec();
    //box.show();
    if (box.clickedButton() != yesBtn)
    {
        return;
    }

    ui->pushButton_2->setEnabled(false);

    thread.url = ui->lineEdit->text();
    thread.filter = ui->lineEdit_2->text();
    thread.regularExpression = ui->lineEdit_3->text();
    thread.replace = ui->lineEdit_4->text();
    thread.start();
}


void Regular_file_replacement::on_lineEdit_2_textChanged(const QString &arg1)
{
    fileExtension = ui->lineEdit_2->text();
    isFileExtensionChange = true;
}


void Regular_file_replacement::on_lineEdit_3_textChanged(const QString &arg1)
{
    regularExpressionStr = ui->lineEdit_3->text();
    isRegularExpressionStrChange = true;
}


void Regular_file_replacement::on_lineEdit_4_textChanged(const QString &arg1)
{
    replace = ui->lineEdit_4->text();
    isReplaceChange = true;
}


void Regular_file_replacement::on_toolButton_clicked()
{
    myMainWindow->removeid(id);
    qmdiArea->closeActiveSubWindow();
}

void Regular_file_replacement::saveContent(){
    if (isFileExtensionChange){
        isFileExtensionChange=false;
        QString configName = QString::number(id)+"-regularFileReplacement/fileExtension";
        myconfig->setValue(configName,fileExtension);
    }
    if (isRegularExpressionStrChange){
        isRegularExpressionStrChange=false;
        QString configName = QString::number(id)+"-regularFileReplacement/regularExpression";
        myconfig->setValue(configName,regularExpressionStr);
    }
    if (isReplaceChange){
        isReplaceChange=false;
        QString configName = QString::number(id)+"-regularFileReplacement/replace";
        myconfig->setValue(configName,replace);
    }

}

void Regular_file_replacement::alwaysSaveContent(){

        QString configName = QString::number(id)+"-regularFileReplacement/fileExtension";
        myconfig->setValue(configName,fileExtension);

        QString configName2 = QString::number(id)+"-regularFileReplacement/regularExpression";
        myconfig->setValue(configName2,regularExpressionStr);

        QString configName3 = QString::number(id)+"-regularFileReplacement/replace";
        myconfig->setValue(configName3,replace);


}
void Regular_file_replacement::myload2(){

    QString fileExtension = myconfig->value(QString::number(id)+"-regularFileReplacement/fileExtension").toString();
    if(fileExtension!="")ui->lineEdit_2->setText(fileExtension);

    QString regularExpression = myconfig->value(QString::number(id)+"-regularFileReplacement/regularExpression").toString();
    if(regularExpression!="")ui->lineEdit_3->setText(regularExpression);

    QString replace = myconfig->value(QString::number(id)+"-regularFileReplacement/replace").toString();
    if(replace!="")ui->lineEdit_4->setText(replace);
}
