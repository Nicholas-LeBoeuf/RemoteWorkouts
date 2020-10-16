#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_3_clicked()
{
    QString attemptedun = username->text();
}
