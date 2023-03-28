#include "search_thread.h"
#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>


search_thread::search_thread()
{

}


void search_thread::run()
{

    doSearch();

}

void search_thread::doSearch(){
    emit sendmsg("正在索引...");

    QStringList fileList = getFileListUnderDir(url,filter);
    emit sendmsg("索引完成，正在查找...");
    for(int i=0;i<fileList.size();i++){
        QString fileurl=fileList.at(i);


        QString inputStr = getFileContentString(fileurl);

        QRegularExpression regularExpression0(regularExpression);
        QRegularExpressionMatch match;

        int startIndex = 0;
        int length = 0;
        int endIndex = 0;
        QStringList result1;

        for(;endIndex < inputStr.length();){
            match = regularExpression0.match(inputStr, endIndex);

            if(match.hasMatch()) {
                startIndex = match.capturedStart();
                length = match.capturedLength();
                endIndex = match.capturedEnd();
                QString result0 = inputStr.mid(startIndex,length);
                //qDebug()<<result0;
                result1.append(result0);
            }
            else{
                break;
            }
        }

        //---------------------------------------------------
        QString result1_length = QString::number(result1.length());
        QString result2 = "";
        if(result1.length()>0){
            result2 = "在" + fileurl + "找到 " + result1_length + " 处匹配：";
            emit sendmsg(result2);
            foreach (auto result4, result1) {
                emit sendmsg(result4);
            }
        }
        int progressBarValue=i*100/(fileList.size()-1);
        emit setProgressBar(progressBarValue);
    }
    emit sendmsg("完成！");
    emit setProgressBar(100);
    emit finish();
}



QString search_thread::getFileContentString(QString fileurl){
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

    return fileContentString;
}



QStringList search_thread::getFileListUnderDir(const QString &dirPath2,const QString &filter2)
{
    QStringList fileList;
    QDir dir(dirPath2);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    foreach (auto fileInfo, fileInfoList) {
        if(fileInfo.isDir())
        {
            QStringList fileList2 = getFileListUnderDir(fileInfo.absoluteFilePath(),filter2);
            fileList.append(fileList2);
        }
        if(filter2==""){
            fileList.append(fileInfo.absoluteFilePath());

        }else{
            QStringList filterlist = filter2.split(",");
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
