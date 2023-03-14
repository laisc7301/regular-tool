#include "about.h"
#include "ui_about.h"
#include <QMessageBox>


About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_4->setOpenExternalLinks(true);
    ui->label_6->setOpenExternalLinks(true);

}

About::~About()
{
    delete ui;
}

void About::on_pushButton_2_clicked()
{
    this->close();
}


void About::on_pushButton_clicked()
{
    QMessageBox::aboutQt(NULL, "About Qt");
}

