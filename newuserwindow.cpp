#include <stdlib.h>
#include <iostream>

//The following are c++/connector header files
/*#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
 */

#include "newuserwindow.h"
#include "ui_newuserwindow.h"
#include <QMessageBox>

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
    const QString usernameInputAttempt = ui->UsernameInput->text();
    const QString fNameInputAttempt = ui->FNameInput->text();
    const QString lNameInputAttempt = ui->LNameInput->text();
    const QString passwordInputAttempt = ui->PasswordInput->text();
    const QString confirmPwInputAttempt = ui->ConfirmPwInput->text();

    std::string username = usernameInputAttempt.toStdString();
    std::string firstName = fNameInputAttempt.toStdString();
    std::string lastName = lNameInputAttempt.toStdString();
    std::string password = passwordInputAttempt.toStdString();
    std::string confirmPw = confirmPwInputAttempt.toStdString();

    if (checkFields() == false) {
        QMessageBox msgBox;
        msgBox.setText("Please fill in all fields!");
        msgBox.exec();
    }

}

bool newuserwindow::checkFields() {
    const QString usernameInputAttempt = ui->UsernameInput->text();
    const QString fNameInputAttempt = ui->FNameInput->text();
    const QString lNameInputAttempt = ui->LNameInput->text();
    const QString passwordInputAttempt = ui->PasswordInput->text();
    const QString confirmPwInputAttempt = ui->ConfirmPwInput->text();

    std::string username = usernameInputAttempt.toStdString();
    std::string firstName = fNameInputAttempt.toStdString();
    std::string lastName = lNameInputAttempt.toStdString();
    std::string password = passwordInputAttempt.toStdString();
    std::string confirmPw = confirmPwInputAttempt.toStdString();

    if (username == "" || firstName == "" || lastName == "" || password == "" || confirmPw == "")
        return false;

    return true;
}
