#include "regular_file_search.h"
#include "ui_regular_file_search.h"
#include "global.h"

#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <QSettings>


Regular_file_search::Regular_file_search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regular_file_search)
{
    ui->setupUi(this);
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString fileExtension = mysetting->value("regularFileSearch/fileExtension").toString();
    if(fileExtension!="")ui->lineEdit_2->setText(fileExtension);
    QString regularExpressionStr = mysetting->value("regularFileSearch/regularExpressionStr").toString();
    if(regularExpressionStr!="")ui->lineEdit_3->setText(regularExpressionStr);
}

Regular_file_search::~Regular_file_search()
{

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    QString fileExtension = ui->lineEdit_2->text();
    mysetting->setValue("regularFileSearch/fileExtension",fileExtension);
    QString regularExpressionStr = ui->lineEdit_3->text();
    mysetting->setValue("regularFileSearch/regularExpressionStr",regularExpressionStr);

    delete ui;
}

void Regular_file_search::on_pushButton_clicked()
{
    QString filename = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(filename);
}


void Regular_file_search::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text()=="")return;

    QString dirpath = ui->lineEdit->text();
    //设置要遍历的目录
    QString filter = ui->lineEdit_2->text();
    QStringList filterlist = filter.split(",");
    QStringList fileList = getFileListUnderDir(dirpath,filterlist);


    QString out1="";
    QString resultout1 = "";
    foreach (auto fileurl, fileList) {

        //out1 += fileurl + "\n";

        QString fileContentString = "";
        QFile file(fileurl);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<< "Can't open the file!" <<Qt::endl;
        }

        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            //qDebug()<< str;
            fileContentString.append(str);



        }



        QString inputStr = fileContentString;
        QString regularExpressionStr = ui->lineEdit_3->text();
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
        QString result1_length = QString::number(result1.length());
        if(result1.length()>0){
            result2 = "在" + fileurl + "找到 " + result1_length + " 处匹配：\n";
            QString result3 = result1.join("\n");

            resultout1 = result2 + result3;






            out1 += resultout1 + "\n";
        }

    }
    ui->textEdit->setText(out1);
}



QStringList Regular_file_search::getFileListUnderDir(const QString &dirPath,const QStringList filterlist)
{
    QStringList fileList;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    foreach (auto fileInfo, fileInfoList) {
        if(fileInfo.isDir())
        {
            QStringList fileList2 = getFileListUnderDir(fileInfo.absoluteFilePath(),filterlist);
            fileList.append(fileList2);
        }

        if(fileInfo.isFile())
        {
            QFileInfo fi(fileInfo.absoluteFilePath());

            QString ext= fi.suffix();

            foreach (auto filter, filterlist) {
                if(filter==ext){
                    fileList.append(fileInfo.absoluteFilePath());
                }
            }
        }
    }
    return fileList;
}


void Regular_file_search::on_lineEdit_3_textChanged(const QString &arg1)
{
    regular_file_search_regularExpressionStr = ui->lineEdit_3->text();
    isRegularFileSearch_RegularExpressionStrChange = true;
}


void Regular_file_search::on_lineEdit_2_textChanged(const QString &arg1)
{
    regular_file_search_fileExtension = ui->lineEdit_2->text();
    isRegularFileSearch_FileExtensionChange = true;
}

