#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "newuserwindow.h"
#include "mainwindow.h"
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

    loginbase.setHostName("24.61.234.35");
    loginbase.setDatabaseName("remoteworkouts");
    loginbase.setUserName("defaultuser");
    loginbase.setPassword("defaultuserpassword");
    loginbase.open();

    const QString username = ui->username->text();
    const QString password = ui->password->text();
    //std::string userstr = username.toStdString();
    //std::string passstr = password.toStdString();

    if (fieldCheck())
    {

        QSqlQuery unattempt;
        QSqlQuery pwattempt;

        unattempt.prepare("select username from users where username='" + username + "';");
        if (unattempt.exec()){
            unattempt.next();
            if (username == unattempt.value(0).toString()){
                pwattempt.prepare("select password from users where password='" + password + "';");
                if (pwattempt.exec()){
                    pwattempt.next();
                    if (password == pwattempt.value(0).toString()) {
                        MainWindow *newMain = new MainWindow();
                        newMain->show();
                        this->hide();
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
}


bool LoginWindow::fieldCheck() {
    const QString username = ui->username->text();
    const QString password = ui->password->text();
    std::string userstr = username.toStdString();
    std::string passstr = password.toStdString();

    if (userstr != "" && passstr != "")
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Username or Password not filled in!");
        msgBox.exec();
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
