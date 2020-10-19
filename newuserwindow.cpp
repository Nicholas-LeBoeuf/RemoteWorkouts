#include "newuserwindow.h"
#include "ui_newuserwindow.h"

newuserwindow::newuserwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newuserwindow)
{
    ui->setupUi(this);
}

newuserwindow::~newuserwindow()
{
    delete ui;
}

void newuserwindow::on_pushButton_2_clicked()
{
    close();
}

void newuserwindow::on_CreateButton_clicked()
{

}
