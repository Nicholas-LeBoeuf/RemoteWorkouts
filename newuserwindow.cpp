#include "newuserwindow.h"
#include "loginwindow.h"
#include "ui_newuserwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <string.h>

newuserwindow::newuserwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newuserwindow)
{
    ui->setupUi(this);
}

void newuserwindow::on_CreateButton_clicked() {
    QSqlDatabase loginbase;
    loginbase = QSqlDatabase::addDatabase("QMYSQL");

    loginbase.setHostName("24.61.234.35");
    loginbase.setDatabaseName("remoteworkouts");
    loginbase.setUserName("defaultuser");
    loginbase.setPassword("defaultuserpassword");
    loginbase.open();

    const QString username = ui->username->text();
    const QString fname = ui->firstname->text();
    const QString lname = ui->lastname->text();
    const QString password = ui->password->text();
    const QString securityQuestion = ui->securityQCombo->currentText();
    const QString securityQAnswer = ui->SecurityQAnswer->text();

    QString securityQuestionID;

    if (ui->securityQCombo->currentText() == "City were you born in?")
        securityQuestionID = "1";
    else if (ui->securityQCombo->currentText() == "Town you grew up in?")
        securityQuestionID = "2";
    else if (ui->securityQCombo->currentText() == "First houses number?")
        securityQuestionID = "3";
    else if (ui->securityQCombo->currentText() == "Name of your first pet?")
        securityQuestionID = "4";
    else if (ui->securityQCombo->currentText() == "Favorite food?")
        securityQuestionID = "5";
    else if (ui->securityQCombo->currentText() == "Favorite color?")
        securityQuestionID = "6";

    if (fieldValidation()) {
        if (passwordValidation()) {


            QSqlQuery unattempt, createacct, createdefaultinfo, logindate;
            QDate date = QDate::currentDate();
            QString datestr = date.toString();

            unattempt.prepare("select username from users where username='" + username + "';");
            if (unattempt.exec()) {
                unattempt.next();
                if (username != unattempt.value(0).toString()) {
                    createacct.prepare(
                            "insert into users (username, firstname, lastname, password, SecurityQuestion, SecurityQAnswer) values ('" + username +
                            "', '" +
                            fname + "', '" + lname + "', '" + password + "', '" + securityQuestionID + "', '" + securityQAnswer +"');");

                    createacct.exec();
                    qDebug() << createacct.lastQuery();

                    QSqlQuery IDtemp; "select ID from users where username = '" + username + "';";
                    IDtemp.prepare("select ID from users where username = '" + username + "';");
                    IDtemp.exec();
                    IDtemp.next();
                    QString ID = IDtemp.value(0).toString();
                    createdefaultinfo.prepare(
                            "insert into userInfo(UserID, Age, Weight, HeightInches, Gender, Goal) values ('" + ID + "', '" + "1" +
                            "', '" + "1" + "', '" + "1" + "', '" + "NULL" + "', '" + "0" "');");

                    createdefaultinfo.exec();
                    qDebug() << createdefaultinfo.lastQuery();
                    QMessageBox msgBox;

                    QSqlQuery wh;
                    wh.prepare("create table " + ID + "_wh (ID int auto_increment not null primary key, weight double not null, date varchar(30) not null);");
                    wh.exec();

                    msgBox.setText("account created");
                    msgBox.exec();
                    LoginWindow *login = new LoginWindow();
                    this->close();
                    login->show();
                }
                else if(username == unattempt.value(0).toString()) {
                    QMessageBox msgBox;
                    msgBox.setText("Username already being used");
                    msgBox.exec();
                }
            } else {
                QMessageBox msgBox;
                msgBox.setText("failed");
                msgBox.exec();
            }
        }
    }
}

bool newuserwindow::fieldValidation(){
    const QString username = ui->username->text();
    const QString fName = ui->firstname->text();
    const QString lName = ui->lastname->text();
    const QString password = ui->password->text();
    const QString confirmPassword = ui->confpw->text();
    const QString securityQuestion = ui->securityQCombo->currentText();
    const QString securityQAnswer = ui->SecurityQAnswer->text();

    std::string usernameStr = username.toStdString();
    std::string fNameStr = fName.toStdString();
    std::string lNameStr = lName.toStdString();
    std::string passwordStr = password.toStdString();
    std::string confirmPwStr = confirmPassword.toStdString();
    std::string securityQuestionStr = securityQuestion.toStdString();
    std::string securityQAnswerStr = securityQAnswer.toStdString();

    if (usernameStr != "" && fNameStr != "" && lNameStr != "" && passwordStr != "" && passwordStr != "" && confirmPwStr != "" && securityQuestionStr != "Make a selection..." && securityQAnswer != "")
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Not all field are filled in!");
        msgBox.exec();
    }
}

bool newuserwindow::passwordValidation() {
    const QString password = ui->password->text();
    const QString confirmPassword = ui->confpw->text();

    std::string passwordStr = password.toStdString();
    std::string confirmPwStr = confirmPassword.toStdString();

    if (password.compare(confirmPassword) == 0)
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Passwords do not match!");
        msgBox.exec();
    }
}

newuserwindow::~newuserwindow()
{
    delete ui;
}

void newuserwindow::on_close_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}
