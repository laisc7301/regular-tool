#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMdiArea>
#include <QSettings>
#include <QList>
#include <QWidget>
#include <QThread>
#include "mainwindow.h"

extern QString version;
extern MainWindow *myMainWindow;
extern QMdiArea *qmdiArea;
extern QSettings *myconfig;
extern QStringList tagList;
extern QList<QWidget*> widgetList;
extern int nextId;
//extern QList<QThread*> threadList;
//extern int nextThreadId;


extern QString regex_replacement_regularExpression;
extern QString regex_replacement_replace;
extern QString regex_replacement_replaceInput;

extern bool isRegexReplacement_RegularExpressionChange;
extern bool isRegexReplacement_ReplaceChange;
extern bool isRegexReplacement_ReplaceInputChange;


//extern QString globaltest;
extern QString regex_match_regularExpressionStr;
extern QString regex_match_inputStr;

extern bool isRegexMatch_RegularExpressionStrChange;
extern bool isRegexMatch_InputStrChange;


extern QString regex_find_regularExpressionStr;
extern QString regex_find_SearchStr;

extern bool isRegexFind_RegularExpressionStrChange;
extern bool isRegexFind_SearchStrChange;

extern QString regular_file_search_regularExpressionStr;
extern QString regular_file_search_fileExtension;
extern bool isRegularFileSearch_RegularExpressionStrChange;
extern bool isRegularFileSearch_FileExtensionChange;


extern QString regular_file_replacement_fileExtension;
extern QString regular_file_replacement_regularExpressionStr;
extern QString regular_file_replacement_replace;
extern bool isRegularFileReplacement_FileExtensionChange;
extern bool isRegularFileReplacement_RegularExpressionStrChange;
extern bool isRegularFileReplacement_ReplaceChange;
#endif // GLOBAL_H


