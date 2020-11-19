#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
#include <QDate>

#include "forgotpassword.h"
#include "ui_forgotpassword.h"

ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::setUser(QString rec){
    received = rec;
}

QString ForgotPassword::getUser(){
    return received;
}

void ForgotPassword::loadSecurityQ()
{
    QSqlDatabase logindata = QSqlDatabase::database("qt_sql_default_connection");

    QSqlQuery securityQ;
    securityQ.prepare("select SecurityQuestion from users where ID = '" + getUser() + "';");
    securityQ.exec();
    securityQ.next();

    if (securityQ.value(0).toString() == "1")
        ui->securityQLabel->setText("What city were you born in?");
    else if (securityQ.value(0).toString() == "2")
        ui->securityQLabel->setText("What town did you grow up in?");
    else if (securityQ.value(0).toString() == "3")
        ui->securityQLabel->setText("What was your first houses number?");
    else if (securityQ.value(0).toString() == "4")
        ui->securityQLabel->setText("What was the name of the street of your first house? (don't include st. etc.)");
    else if (securityQ.value(0).toString() == "5")
        ui->securityQLabel->setText("What was the name of your first pet?");
    else if (securityQ.value(0).toString() == "6")
        ui->securityQLabel->setText("Whats your favorite food?");
    else if (securityQ.value(0).toString() == "7")
        ui->securityQLabel->setText("Whats your favorite color?");
}

void ForgotPassword::on_close_clicked()
{
    close();
}

void ForgotPassword::on_resetPassword_clicked()
{
    const QString securityQAnswer = ui->securityQAnswer->text();
    const QString newPassword = ui->newPassword->text();
    const QString confirmPassword = ui->confirmPassword->text();

    if (fieldValidation())
    {
        if (passwordValidation())
        {
            if (securityValidation())
            {
                QSqlQuery updatePW;

                updatePW.prepare("UPDATE users SET password='" + newPassword + "' WHERE ID='" + getUser() + "';");

                updatePW.exec();
                qDebug() << updatePW.lastQuery();
                QMessageBox msgBox;
                msgBox.setText("Password successfully reset!");
                msgBox.exec();

                close();
            }
        }
    }
}

bool ForgotPassword::fieldValidation()
{
    const QString securityQAnswer = ui->securityQAnswer->text();
    const QString newPassword = ui->newPassword->text();
    const QString confirmPassword = ui->confirmPassword->text();

    std::string securityStr = securityQAnswer.toStdString();
    std::string newPassStr = newPassword.toStdString();
    std::string confirmPassStr = confirmPassword.toStdString();

    if (securityStr != "" && newPassStr != "" && confirmPassStr != "")
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Not all field are filled in!");
        msgBox.exec();
    }
}

bool ForgotPassword::passwordValidation() {
    const QString newPassword = ui->newPassword->text();
    const QString confirmPassword = ui->confirmPassword->text();

    if (newPassword.compare(confirmPassword) == 0)
        return true;
    else {
        QMessageBox msgBox;
        msgBox.setText("Passwords do not match!");
        msgBox.exec();
    }
}

bool ForgotPassword::securityValidation() {
    QSqlDatabase logindata = QSqlDatabase::database("qt_sql_default_connection");

    const QString securityQAnswer = ui->securityQAnswer->text();

    QSqlQuery securityattempt;

    securityattempt.prepare("select SecurityQAnswer from users where ID ='" + getUser() + "';");

    if (securityattempt.exec()) {
        securityattempt.next();

        if (securityQAnswer == securityattempt.value(0).toString()) {
            return true;
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Incorrect security question answer");
            msgBox.exec();
            return false;
        }
    }
}
