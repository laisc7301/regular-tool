#ifndef REGEX_MATCH_H
#define REGEX_MATCH_H

#include <QWidget>

namespace Ui {
class regex_match;
}

class regex_match : public QWidget
{
    Q_OBJECT

public:
    explicit regex_match(QWidget *parent = nullptr);
    ~regex_match();

private:
    Ui::regex_match *ui;
};

#endif // REGEX_MATCH_H
