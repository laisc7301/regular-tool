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

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString fileExtension = mysetting->value("regularFileReplacement/fileExtension").toString();
    if(fileExtension!="")ui->lineEdit_2->setText(fileExtension);

    QString regularExpression = mysetting->value("regularFileReplacement/regularExpression").toString();
    if(regularExpression!="")ui->lineEdit_3->setText(regularExpression);

    QString replace = mysetting->value("regularFileReplacement/replace").toString();
    if(replace!="")ui->lineEdit_4->setText(replace);
}

Regular_file_replacement::~Regular_file_replacement()
{
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString fileExtension = ui->lineEdit_2->text();
    mysetting->setValue("regularFileReplacement/fileExtension",fileExtension);
    QString regularExpression = ui->lineEdit_3->text();
    mysetting->setValue("regularFileReplacement/regularExpression",regularExpression);
    QString replace = ui->lineEdit_4->text();
    mysetting->setValue("regularFileReplacement/replace",replace);


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





    thread.url = ui->lineEdit->text();
    thread.filter = ui->lineEdit_2->text();
    thread.regularExpression = ui->lineEdit_3->text();
    thread.replace = ui->lineEdit_4->text();
    thread.start();
}


void Regular_file_replacement::on_lineEdit_2_textChanged(const QString &arg1)
{
    regular_file_replacement_fileExtension = ui->lineEdit_2->text();
    isRegularFileReplacement_FileExtensionChange = true;
}


void Regular_file_replacement::on_lineEdit_3_textChanged(const QString &arg1)
{
    regular_file_replacement_regularExpressionStr = ui->lineEdit_3->text();
    isRegularFileReplacement_RegularExpressionStrChange = true;
}


void Regular_file_replacement::on_lineEdit_4_textChanged(const QString &arg1)
{
    regular_file_replacement_replace = ui->lineEdit_4->text();
    isRegularFileReplacement_ReplaceChange = true;
}

