#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QMainWindow>

namespace Ui {
class AddFriend;
}

class AddFriend : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();

private slots:
    void on_AddButton_clicked();

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
