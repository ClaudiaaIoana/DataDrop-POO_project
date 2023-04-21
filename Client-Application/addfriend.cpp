#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("  Type...");
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_AddButton_clicked()
{

}

