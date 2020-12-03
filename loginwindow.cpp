#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "newuserwindow.h"
#include "mainwindow.h"
#include "welcomescreen.h"
#include "forgotpassword.h"
#include <iostream>
#include <QDate>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

void LoginWindow::on_login_clicked()
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

    if (fieldCheck())
    {

        QSqlQuery unattempt;
        QSqlQuery pwattempt;
        QSqlQuery idsend;
        QSqlQuery logindate;

        unattempt.prepare("select username from users where username='" + username + "';");
        if (unattempt.exec()){
            unattempt.next();
            if (username == unattempt.value(0).toString()){
                pwattempt.prepare("select password from users where username='" + username + "' and password='" + password + "';");
                if (pwattempt.exec()){
                    pwattempt.next();
                    if (password == pwattempt.value(0).toString()) {
                        QDate date = QDate::currentDate();
                        QString datestr = date.toString();

                        logindate.prepare("update users set lastlogin= '" + datestr + "' where username='" + username + "';");
                        logindate.exec();
                        idsend.prepare("select ID from users where username='" + username + "';");
                        idsend.exec();
                        idsend.next();
                        QString idsent = idsend.value(0).toString();
                        //MainWindow *newMain = new MainWindow();
                        WelcomeScreen *newWelcome = new WelcomeScreen();
                        //newMain->setUser(idsent);
                        //newMain->loadData();
                        //newMain->show();
                        newWelcome->loadQuote();
                        newWelcome->setUser(idsent);
                        newWelcome->show();
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
    this->hide();
    newuserwindow.exec();
    update();
}

void LoginWindow::on_forgotPassword_clicked()
{
    QSqlDatabase loginbase;
    loginbase = QSqlDatabase::addDatabase("QMYSQL");

    loginbase.setHostName("localhost");
    loginbase.setDatabaseName("remoteworkouts");
    loginbase.setUserName("defaultuser");
    loginbase.setPassword("defaultuserpassword");
    loginbase.open();

    const QString username = ui->username->text();

    QSqlQuery idsend;
    QSqlQuery unattempt;

    if (usernameFieldCheck())
    {
        unattempt.prepare("select username from users where username='" + username + "';");
        if (unattempt.exec())
        {
            unattempt.next();
            qDebug()<<unattempt.lastQuery();
            if (username == unattempt.value(0).toString())
            {
                idsend.prepare("select ID from users where username='" + username + "';");
                idsend.exec();
                idsend.next();
                QString idsent = idsend.value(0).toString();
                ForgotPassword *newFP = new ForgotPassword();
                newFP->setUser(idsent);
                newFP->loadSecurityQ();
                newFP->show();
            }
        }
    }
}

bool LoginWindow::usernameFieldCheck()
{
    const QString username = ui->username->text();
    std::string userstr = username.toStdString();

    if (userstr != "")
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Please fill in the username to change password.");
        msgBox.exec();
    }
}
