#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"

//创建菜单栏，工具栏，状态栏应当包含的头文件
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include <qDebug>
#include <iostream>
#include "regex_replacement.h"
#include "regex_match.h"
#include "regex_find.h"
#include "about.h"
#include "regular_file_search.h"
#include "regular_file_replacement.h"

#include <QMdiSubWindow>

QTimer *timer2 = new QTimer();
QTimer *timer3 = new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qmdiArea = ui->mdiArea;

    ui->mdiArea->setViewMode(QMdiArea::TabbedView);

    QObject::connect(&load2, SIGNAL(loadback()), this, SLOT(myload2()));
    load2.start();
    QToolBar *toolBar = new QToolBar();
    addToolBar(toolBar);

    QAction *m1 = toolBar->addAction("正则查找");
    connect(m1,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_find *regex_find1 = new regex_find;
        regex_find1->id = nextId++;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_find1);
        subWindow1->show();
        tagList.append("regex_find");

        widgetList.append(regex_find1);
        saveTag();
    });

    QAction *m2 = toolBar->addAction("正则匹配");
    connect(m2,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_match *regex_match1 = new regex_match;
        regex_match1->id=nextId++;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_match1);
        subWindow1->show();
        tagList.append("regex_match");

        widgetList.append(regex_match1);
        saveTag();
    });

    QAction *m3 = toolBar->addAction("正则替换");
    connect(m3,&QAction::triggered,this,[=](){

        regex_replacement *regex_replacement1 = new regex_replacement();
        regex_replacement1->id=nextId++;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_replacement1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));
        tagList.append("regex_replacement");

        widgetList.append(regex_replacement1);
        saveTag();
    });

    QAction *m4 = toolBar->addAction("正则文件查找");
    connect(m4,&QAction::triggered,this,[=](){

        Regular_file_search *regular_file_search1 = new Regular_file_search();
        regular_file_search1->id=nextId++;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_search1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));
        tagList.append("Regular_file_search");

        widgetList.append(regular_file_search1);
        saveTag();
    });

    QAction *m5 = toolBar->addAction("正则文件替换");
    connect(m5,&QAction::triggered,this,[=](){

        Regular_file_replacement *regular_file_replacement1 = new Regular_file_replacement();
        regular_file_replacement1->id=nextId++;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_replacement1);
        subWindow1->show();
        tagList.append("Regular_file_replacement");

        widgetList.append(regular_file_replacement1);
        saveTag();
        //subWindow1->resize(QSize(550,250));

    });

    QAction *m6 = toolBar->addAction("关于");
    connect(m6,&QAction::triggered,this,[=](){

        About *About2 = new About();
        About2->show();
    });

    //    QAction *m7 = toolBar->addAction("测试");
    //    connect(m7,&QAction::triggered,this,[=](){
    //        qDebug()<<widgetList;
    //        printIdList();
    //    });




    connect(timer3,&QTimer::timeout,this,[=](){
        //qDebug()<<"runhere";
        for(int i=0;i<nextId;i++){
            QString mytype = tagList.at(i);
            if(mytype=="regex_find"){
                regex_find *regex_find1 = (regex_find*)widgetList.at(i);
                regex_find1->saveContent();
            }else if(mytype=="regex_match"){
                regex_match *regex_match1 = (regex_match*)widgetList.at(i);
                regex_match1->saveContent();
            }else if(mytype=="regex_replacement"){
                regex_replacement *regex_replacement1 = (regex_replacement*)widgetList.at(i);
                regex_replacement1->saveContent();
            }else if(mytype=="Regular_file_search"){
                Regular_file_search *regular_file_search1 = (Regular_file_search*)widgetList.at(i);
                regular_file_search1->saveContent();
            }else if(mytype=="Regular_file_replacement"){
                Regular_file_replacement *regular_file_replacement1 = (Regular_file_replacement*)widgetList.at(i);
                regular_file_replacement1->saveContent();
            }
        }
    });
    timer3->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTag(){


    QStringList tag0 = myconfig->value("mainwindow/tagList").toString().split(",");
    for(int i=0;i<tag0.size();i++){
        QString tagName = tag0.at(i);

        if(tagName=="regex_find"){
            regex_find *regex_find1 = new regex_find;
            regex_find1->id=nextId++;
            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_find1);

            subWindow1->show();
            tagList.append("regex_find");
            widgetList.append(regex_find1);

        }else if(tagName=="regex_match"){
            regex_match *regex_match1 = new regex_match;
            regex_match1->id=nextId++;
            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_match1);

            subWindow1->show();
            tagList.append("regex_match");
            widgetList.append(regex_match1);

        }else if(tagName=="regex_replacement"){
            regex_replacement *regex_replacement1 = new regex_replacement();
            regex_replacement1->id=nextId++;
            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_replacement1);

            subWindow1->show();
            tagList.append("regex_replacement");
            widgetList.append(regex_replacement1);

        }else if(tagName=="Regular_file_search"){
            Regular_file_search *regular_file_search1 = new Regular_file_search();
            regular_file_search1->id=nextId++;
            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_search1);

            subWindow1->show();
            tagList.append("Regular_file_search");
            widgetList.append(regular_file_search1);

        }else if(tagName=="Regular_file_replacement"){
            Regular_file_replacement *regular_file_replacement1 = new Regular_file_replacement();
            regular_file_replacement1->id=nextId++;
            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_replacement1);

            subWindow1->show();
            tagList.append("Regular_file_replacement");
            widgetList.append(regular_file_replacement1);

        }
    }
}


void MainWindow::saveTag(){
    //qDebug()<<tagList.join(",");

    myconfig->setValue("mainwindow/tagList",tagList.join(","));
}

void MainWindow::removeid(int id){
    qDebug()<<QString::number(id);
    QString mytype0 = tagList.at(id);
    if(mytype0=="regex_find"){
        myconfig->remove(QString::number(id)+"-regexFind");
    }else if(mytype0=="regex_match"){
        myconfig->remove(QString::number(id)+"-regexMatch");
    }else if(mytype0=="regex_replacement"){
        myconfig->remove(QString::number(id)+"-regularReplace");
    }else if(mytype0=="Regular_file_search"){
        myconfig->remove(QString::number(id)+"-regularFileSearch");
    }else if(mytype0=="Regular_file_replacement"){
        myconfig->remove(QString::number(id)+"-regularFileReplacement");
    }


    for(int i=id+1;i<nextId;i++){
        QString mytype = tagList.at(i);
        if(mytype=="regex_find"){
            myconfig->remove(QString::number(i)+"-regexFind");
            regex_find *regex_find1 = (regex_find*)widgetList.at(i);
            std::cout<<regex_find1->id;
            regex_find1->id--;
            regex_find1->alwaysSaveContent();
        }else if(mytype=="regex_match"){
            myconfig->remove(QString::number(i)+"-regexMatch");
            regex_match *regex_match1 = (regex_match*)widgetList.at(i);
            regex_match1->id--;
            regex_match1->alwaysSaveContent();
        }else if(mytype=="regex_replacement"){
            myconfig->remove(QString::number(i)+"-regularReplace");
            regex_replacement *regex_replacement1 = (regex_replacement*)widgetList.at(i);
            regex_replacement1->id--;
            regex_replacement1->alwaysSaveContent();
        }else if(mytype=="Regular_file_search"){
            myconfig->remove(QString::number(i)+"-regularFileSearch");
            Regular_file_search *regular_file_search1 = (Regular_file_search*)widgetList.at(i);
            regular_file_search1->id--;
            regular_file_search1->alwaysSaveContent();
        }else if(mytype=="Regular_file_replacement"){
            myconfig->remove(QString::number(i)+"-regularFileReplacement");
            Regular_file_replacement *regular_file_replacement1 = (Regular_file_replacement*)widgetList.at(i);
            regular_file_replacement1->id--;
            regular_file_replacement1->alwaysSaveContent();
        }
    }
    widgetList.removeAt(id);
    nextId--;


    tagList.removeAt(id);
    saveTag();
}


void MainWindow::printIdList(){
    for(int i=0;i<nextId;i++){
        QString mytype = tagList.at(i);
        if(mytype=="regex_find"){
            regex_find *regex_find1 = (regex_find*)widgetList.at(i);
            std::cout<<regex_find1->id;

            regex_find1->saveContent();
        }else if(mytype=="regex_match"){
            regex_match *regex_match1 = (regex_match*)widgetList.at(i);
            std::cout<<regex_match1->id;

        }else if(mytype=="regex_replacement"){
            regex_replacement *regex_replacement1 = (regex_replacement*)widgetList.at(i);
            std::cout<<regex_replacement1->id;

        }else if(mytype=="Regular_file_search"){
            Regular_file_search *regular_file_search1 = (Regular_file_search*)widgetList.at(i);
            std::cout<<regular_file_search1->id;

        }else if(mytype=="Regular_file_replacement"){
            Regular_file_replacement *regular_file_replacement1 = (Regular_file_replacement*)widgetList.at(i);
            std::cout<<regular_file_replacement1->id;

        }
    }
}


void MainWindow::myload2()
{
    showTag();
}
