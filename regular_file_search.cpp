#include "regular_file_search.h"
#include "ui_regular_file_search.h"
#include "global.h"
#include "load_thread.h"
#include "search_thread.h"

#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <QSettings>


Regular_file_search::Regular_file_search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regular_file_search)
{
    ui->setupUi(this);

    QObject::connect(&searchThread, SIGNAL(sendmsg(QString)), this, SLOT(getmsg(QString)));
    QObject::connect(&searchThread, SIGNAL(setProgressBar(int)), this, SLOT(setProgressBar(int)));
    QObject::connect(&searchThread, SIGNAL(finish()), this, SLOT(threadFinish()));
    QObject::connect(&load2, SIGNAL(loadback()), this, SLOT(myload2()));
    load2.start();
}

Regular_file_search::~Regular_file_search()
{

    //alwaysSaveContent();
    delete ui;
}

void Regular_file_search::on_pushButton_clicked()
{
    QString filename = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(filename);
}

void Regular_file_search::on_pushButton_2_clicked(){
    QString dirpath = ui->lineEdit->text();
    QString filter = ui->lineEdit_2->text();
    QString regularExpressionStr = ui->lineEdit_3->text();
    if(regularExpressionStr=="")return;
    ui->textEdit->setText("");
    ui->progressBar->setValue(0);

    searchThread.url=dirpath;
    searchThread.filter=filter;
    searchThread.regularExpression=regularExpressionStr;
    ui->pushButton_2->setEnabled(false);
    searchThread.start();

}
void Regular_file_search::search()
{
    if(ui->lineEdit_3->text()=="")return;

    QString dirpath = ui->lineEdit->text();
    //设置要遍历的目录
    QString filter = ui->lineEdit_2->text();

    QStringList fileList = getFileListUnderDir(dirpath,filter);


    QString out1="";

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

        QRegularExpression regularExpression(regularExpressionStr);


        QRegularExpressionMatch match;
        int startIndex = 0;
        int length = 0;
        int endIndex = 0;
        QStringList result1;

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
        QString resultout1 = "";
        QString result1_length = QString::number(result1.length());
        QString result2 = "";
        if(result1.length()>0){
            result2 = "在" + fileurl + "找到 " + result1_length + " 处匹配：\n";
            QString result3 = result1.join("\n");

            resultout1 = result2 + result3;






            out1 += resultout1 + "\n";
        }

    }
    ui->textEdit->setText(out1);
}



QStringList Regular_file_search::getFileListUnderDir(const QString &dirPath,const QString &filter)
{
    QStringList fileList;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    foreach (auto fileInfo, fileInfoList) {
        if(fileInfo.isDir())
        {
            QStringList fileList2 = getFileListUnderDir(fileInfo.absoluteFilePath(),filter);
            fileList.append(fileList2);
        }
        if(filter==""){
            fileList.append(fileInfo.absoluteFilePath());

        }else{
            QStringList filterlist = filter.split(",");
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

    }
    return fileList;
}


void Regular_file_search::on_lineEdit_3_textChanged(const QString &arg1)
{
    regularExpressionStr = ui->lineEdit_3->text();
    isRegularExpressionStrChange = true;
}


void Regular_file_search::on_lineEdit_2_textChanged(const QString &arg1)
{
    fileExtension = ui->lineEdit_2->text();
    isFileExtensionChange = true;
}


void Regular_file_search::on_toolButton_clicked()
{
    myMainWindow->removeid(id);
    qmdiArea->closeActiveSubWindow();
}

void Regular_file_search::saveContent(){
    if (isFileExtensionChange){
        isFileExtensionChange=false;
        QString configName = QString::number(id)+"-regularFileSearch/fileExtension";
        myconfig->setValue(configName,fileExtension);
    }
    if (isRegularExpressionStrChange){
        isRegularExpressionStrChange=false;
        QString configName = QString::number(id)+"-regularFileSearch/regularExpression";
        myconfig->setValue(configName,regularExpressionStr);
    }


}

void Regular_file_search::alwaysSaveContent(){

        QString configName = QString::number(id)+"-regularFileSearch/fileExtension";
        myconfig->setValue(configName,fileExtension);

        QString configName2 = QString::number(id)+"-regularFileSearch/regularExpression";
        myconfig->setValue(configName2,regularExpressionStr);


}
void Regular_file_search::myload2(){
    QString fileExtension = myconfig->value(QString::number(id)+"-regularFileSearch/fileExtension").toString();
    if(fileExtension!="")ui->lineEdit_2->setText(fileExtension);

    QString regularExpression = myconfig->value(QString::number(id)+"-regularFileSearch/regularExpression").toString();
    if(regularExpression!="")ui->lineEdit_3->setText(regularExpression);
}



void Regular_file_search::getmsg(QString msg)
{
ui->textEdit->append(msg);
}
void Regular_file_search::setProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

void Regular_file_search::threadFinish(){
    ui->pushButton_2->setEnabled(true);
}
