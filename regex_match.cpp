#include "regex_match.h"
#include "ui_regex_match.h"

regex_match::regex_match(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regex_match)
{
    ui->setupUi(this);
}

regex_match::~regex_match()
{
    delete ui;
}
