#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "newuserwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

bool LoginWindow::on_login_clicked()
{
    QSqlDatabase loginbase;
    loginbase = QSqlDatabase::addDatabase("QMYSQL");

    loginbase.setHostName("localhost");
    loginbase.setDatabaseName("remoteworkouts");
    loginbase.setUserName("defaultuser");
    loginbase.setPassword("defaultuserpassword");
    loginbase.open();

    const QString username = ui->username->text();
    const QString password = ui->password->text();
    //std::string userstr = username.toStdString();
    //std::string passstr = password.toStdString();

    QSqlQuery unattempt;
    QSqlQuery pwattempt;

    unattempt.prepare("select username from users where username='" + username + "';");
    if (unattempt.exec()){
        unattempt.next();
        if (username == unattempt.value(0).toString()){
            pwattempt.prepare("select password from users where password='" + password + "';");
            if (pwattempt.exec()){
                pwattempt.next();
                if (password == pwattempt.value(0).toString()){
                    QMessageBox msgBox;
                    msgBox.setText("you have logged in");
                    msgBox.exec();
                }
                else {
                    QMessageBox msgBox;
                    msgBox.setText("incorrect password");
                    msgBox.exec();
                }
            }
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("incorrect username");
            msgBox.exec();
        }
    }
}


LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_newuser_clicked()
{
    newuserwindow newuserwindow;
    newuserwindow.exec();
    update();
}
