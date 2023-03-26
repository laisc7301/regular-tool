#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int nextId=0;
    void removeid(int id);
    void printIdList();
private:
    Ui::MainWindow *ui;


    void showTag();
    void saveTag();

};
#endif // MAINWINDOW_H
