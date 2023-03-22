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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QToolBar *toolBar = new QToolBar();
    addToolBar(toolBar);


    QAction *m1 = toolBar->addAction("正则查找");
    connect(m1,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_find *regex_find1 = new regex_find;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_find1);
        subWindow1->show();
    });

    QAction *m2 = toolBar->addAction("正则匹配");
    connect(m2,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_match *regex_match1 = new regex_match;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_match1);
        subWindow1->show();
    });

    QAction *m3 = toolBar->addAction("正则替换");
    connect(m3,&QAction::triggered,this,[=](){

        regex_replacement *regex_replacement1 = new regex_replacement();
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_replacement1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));

    });

    QAction *m4 = toolBar->addAction("正则文件查找");
    connect(m4,&QAction::triggered,this,[=](){

        Regular_file_search *regular_file_search1 = new Regular_file_search();
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_search1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));

    });

    QAction *m5 = toolBar->addAction("正则文件替换");
    connect(m5,&QAction::triggered,this,[=](){

        Regular_file_replacement *regular_file_replacement1 = new Regular_file_replacement();
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regular_file_replacement1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));

    });

    QAction *m6 = toolBar->addAction("关于");
    connect(m6,&QAction::triggered,this,[=](){

        About *About2 = new About();
        About2->show();
    });


    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    regex_replacement_regularExpression = mysetting->value("regularExpression/regularExpression").toString();

    regex_replacement_replace = mysetting->value("regularExpression/replace").toString();

    regex_replacement_replaceInput = mysetting->value("regularExpression/replaceInput").toString();

    regex_match_regularExpressionStr = mysetting->value("regexMatch/regularExpressionStr").toString();

    regex_match_inputStr = mysetting->value("regexMatch/inputStr").toString();

    regex_find_regularExpressionStr = mysetting->value("regexFind/RegularExpressionStr").toString();

    regex_find_SearchStr = mysetting->value("regexFind/SearchStr").toString();

    regular_file_search_regularExpressionStr = mysetting->value("regularFileSearch/regularExpressionStr").toString();

    regular_file_search_fileExtension = mysetting->value("regularFileSearch/fileExtension").toString();

    connect(timer2,&QTimer::timeout,this,[=](){

        //std::cout << "time" << std::endl;

        if(isRegexReplacement_RegularExpressionChange){
            isRegexReplacement_RegularExpressionChange = false;
            //QString str1 = ui->lineEdit->text();
            mysetting->setValue("regularExpression/regularExpression",regex_replacement_regularExpression);
        }
        if(isRegexReplacement_ReplaceChange){
            isRegexReplacement_ReplaceChange = false;
            //QString str1 = ui->lineEdit_2->text();
            mysetting->setValue("regularExpression/replace",regex_replacement_replace);
        }
        if(isRegexReplacement_ReplaceInputChange){
            isRegexReplacement_ReplaceInputChange = false;
            //QString str1 = ui->textEdit->toPlainText();
            mysetting->setValue("regularExpression/replaceInput",regex_replacement_replaceInput);
        }
        if(isRegexMatch_RegularExpressionStrChange){
            isRegexMatch_RegularExpressionStrChange = false;

            mysetting->setValue("regexMatch/regularExpressionStr",regex_match_regularExpressionStr);
        }
        if(isRegexMatch_InputStrChange){
            isRegexMatch_InputStrChange = false;

            mysetting->setValue("regexMatch/inputStr",regex_match_inputStr);
        }
        if(isRegexFind_RegularExpressionStrChange){
            isRegexFind_RegularExpressionStrChange = false;

            mysetting->setValue("regexFind/RegularExpressionStr",regex_find_regularExpressionStr);
        }
        if(isRegexFind_SearchStrChange){
            isRegexFind_SearchStrChange = false;

            mysetting->setValue("regexFind/SearchStr",regex_find_SearchStr);
        }

        if(isRegularFileSearch_FileExtensionChange){
            isRegularFileSearch_FileExtensionChange = false;

            mysetting->setValue("regularFileSearch/fileExtension",regular_file_search_fileExtension);
        }

        if(isRegularFileSearch_RegularExpressionStrChange){
            isRegularFileSearch_RegularExpressionStrChange = false;

            mysetting->setValue("regularFileSearch/regularExpressionStr",regular_file_search_regularExpressionStr);
        }

        if(isRegularFileReplacement_FileExtensionChange){
            isRegularFileReplacement_FileExtensionChange = false;

            mysetting->setValue("regularFileReplacement/fileExtension",regular_file_replacement_fileExtension);
        }
        if(isRegularFileReplacement_RegularExpressionStrChange){
            isRegularFileReplacement_RegularExpressionStrChange = false;

            mysetting->setValue("regularFileReplacement/regularExpression",regular_file_replacement_regularExpressionStr);
        }
        if(isRegularFileReplacement_ReplaceChange){
            isRegularFileReplacement_ReplaceChange = false;

            mysetting->setValue("regularFileReplacement/replace",regular_file_replacement_replace);
        }

    });
    timer2->start(1000);

}

MainWindow::~MainWindow()
{

    qDebug()<<regex_replacement_regularExpression;
    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    mysetting->setValue("regularExpression/regularExpression",regex_replacement_regularExpression);
    mysetting->setValue("regularExpression/replace",regex_replacement_replace);
    mysetting->setValue("regularExpression/replaceInput",regex_replacement_replaceInput);


    mysetting->setValue("regexMatch/regularExpressionStr",regex_match_regularExpressionStr);
    mysetting->setValue("regexMatch/inputStr",regex_match_inputStr);

    mysetting->setValue("regexFind/RegularExpressionStr",regex_find_regularExpressionStr);
    mysetting->setValue("regexFind/SearchStr",regex_find_SearchStr);

    mysetting->setValue("regularFileSearch/regularExpressionStr",regular_file_search_regularExpressionStr);
    mysetting->setValue("regularFileSearch/fileExtension",regular_file_search_fileExtension);

    mysetting->setValue("regularFileReplacement/fileExtension",regular_file_replacement_fileExtension);
    mysetting->setValue("regularFileReplacement/regularExpression",regular_file_replacement_regularExpressionStr);
    mysetting->setValue("regularFileReplacement/replace",regular_file_replacement_replace);

    delete ui;
}

