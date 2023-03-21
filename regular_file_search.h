#ifndef REGULAR_FILE_SEARCH_H
#define REGULAR_FILE_SEARCH_H

#include <QWidget>

namespace Ui {
class Regular_file_search;
}

class Regular_file_search : public QWidget
{
    Q_OBJECT

public:
    explicit Regular_file_search(QWidget *parent = nullptr);
    ~Regular_file_search();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    QStringList getFileListUnderDir(const QString &dirPath,const QStringList filterlist);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::Regular_file_search *ui;
};

#endif // REGULAR_FILE_SEARCH_H
