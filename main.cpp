#include "mainwindow.h"

#include <QApplication>
#include "global.h"

QString version = "v1.2.1";

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

QString regex_find_regularExpressionStr = "";
QString regex_find_SearchStr = "";

bool isRegexFind_RegularExpressionStrChange = false;
bool isRegexFind_SearchStrChange = false;

QString regular_file_search_fileExtension = "";
QString regular_file_search_regularExpressionStr = "";
bool isRegularFileSearch_FileExtensionChange = false;
bool isRegularFileSearch_RegularExpressionStrChange = false;

QString regular_file_replacement_fileExtension = "";
QString regular_file_replacement_regularExpressionStr = "";
QString regular_file_replacement_replace = "";
bool isRegularFileReplacement_FileExtensionChange = false;
bool isRegularFileReplacement_RegularExpressionStrChange = false;
bool isRegularFileReplacement_ReplaceChange = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
