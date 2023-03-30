#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include "load_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void removeid(int id);
    void printIdList();
    void saveTag();
    void reloadTag();
    void saveAll();
    load_thread load2;

public slots:
    void myload2();

private slots:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;


    void showTag();


};
#endif // MAINWINDOW_H
