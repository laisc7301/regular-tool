#include "about.h"
#include "ui_about.h"
#include <QMessageBox>
#include "global.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_4->setOpenExternalLinks(true);
    ui->label_6->setOpenExternalLinks(true);
    ui->label_8->setOpenExternalLinks(true);
    QString qtVersion = QT_VERSION_STR;
    QString qtVersionOut = "基于Qt" + qtVersion + "开发";
    ui->label_2->setText(qtVersionOut);

    ui->label_7->setText(version);

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

