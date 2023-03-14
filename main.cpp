#include "mainwindow.h"

#include <QApplication>
#include "global.h"

QString regex_replacement_regularExpression = "";
QString regex_replacement_replace = "";
QString regex_replacement_replaceInput = "";

bool isRegexReplacement_RegularExpressionChange = false;
bool isRegexReplacement_ReplaceChange = false;
bool isRegexReplacement_ReplaceInputChange = false;


QString regex_match_regularExpressionStr = "";
QString regex_match_inputStr = "";

bool isRegexMatch_RegularExpressionStrChange = false;
bool isRegexMatch_InputStrChange = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
