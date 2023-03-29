#include "replacement_thread.h"
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QRegularExpression>

replacement_thread::replacement_thread()
{

}

void replacement_thread::run()
{
    //qDebug()<<"replacement_thread";
    //qDebug()<<number;
    //QThread::sleep(3);
    //    int i=0;
    //    for(;;){
    //    emit sendmsg(QString::number(i++));

    //    QString threadId = QString::number(quintptr(QThread::currentThreadId()));
    //    emit sendmsg(threadId);
    //    QThread::sleep(1);
    //    }

    doReplace();
}

void replacement_thread::doReplace(){
    emit sendmsg("正在索引...");
    QStringList list = getFileListUnderDir(url,filter);
    for(int i=0;i<list.size();i++)
    {
        QString fileurl = list.at(i);
        emit sendmsg("正在处理："+fileurl);
        QString fileContent = getfileContent(fileurl);
        fileContent.replace(QRegularExpression(regularExpression),replace);
        writeFile(fileurl,fileContent);
        //QThread::sleep(1);
        int progressRate = (i+1)*100/list.size();
        emit setProgressBar(progressRate);
    }
    emit setProgressBar(100);
    emit sendmsg("完成！");
    emit finish();
}

QString replacement_thread::getfileContent(const QString &url){

    QString fileContentString = "";
    QFile file(url);
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
    return fileContentString;

}
void replacement_thread::writeFile(const QString &url,const QString &content)
{
    QFile file(url);

    //不存在创建，存在则打开
    file.open(QIODevice::Truncate|QIODevice::WriteOnly|QIODevice::Text);
    //写入内容，注意需要转码，否则会报错
    QByteArray str = content.toUtf8();
    //写入QByteArray格式字符串
    file.write(str);


    file.close();
}

QStringList replacement_thread::getFileListUnderDir(const QString &dirPath,const QString &filter)
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
            if(fileInfo.isFile()){
                fileList.append(fileInfo.absoluteFilePath());
            }
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
