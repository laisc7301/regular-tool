#ifndef REGEX_FIND_H
#define REGEX_FIND_H

#include <QWidget>

namespace Ui {
class regex_find;
}

class regex_find : public QWidget
{
    Q_OBJECT

public:
    explicit regex_find(QWidget *parent = nullptr);
    ~regex_find();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::regex_find *ui;
};

#endif // REGEX_FIND_H
