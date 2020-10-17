#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

bool LoginWindow::on_login_clicked()
{
    const QString usernameattempt = ui->username->text();
    const QString passwordattempt = ui->password->text();
    std::string userstr = usernameattempt.toStdString();
    std::string passstr = passwordattempt.toStdString();
     std::string test = "test";
     std::string pw = "password";
    if (userstr == test && passstr == pw){
        QMessageBox msgBox;
        msgBox.setText("test");
        msgBox.exec();
        return true;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("false");
        msgBox.exec();
        return false;
    }
}


LoginWindow::~LoginWindow()
{
    delete ui;
}

