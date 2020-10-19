#include <stdlib.h>
#include <iostream>

//The following are c++/connector header files
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


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

    if (checkPassword() == false) {
        QMessageBox msgBox;
        msgBox.setText("Passwords do not match.");
        msgBox.exec();
    }

    if (checkFields() == true && checkPassword() == true)
    {
        main();
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

bool newuserwindow::checkPassword() {
    const QString passwordInputAttempt = ui->PasswordInput->text();
    const QString confirmPwInputAttempt = ui->ConfirmPwInput->text();
    std::string password = passwordInputAttempt.toStdString();
    std::string confirmPw = confirmPwInputAttempt.toStdString();

    if (password != confirmPw)
        return false;

    return true;
}

int newuserwindow::main() {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::PreparedStatement *pstmt;

    const QString usernameInputAttempt = ui->UsernameInput->text();
    const QString fNameInputAttempt = ui->FNameInput->text();
    const QString lNameInputAttempt = ui->LNameInput->text();
    const QString passwordInputAttempt = ui->PasswordInput->text();

    std::string username = usernameInputAttempt.toStdString();
    std::string firstName = fNameInputAttempt.toStdString();
    std::string lastName = lNameInputAttempt.toStdString();
    std::string password = passwordInputAttempt.toStdString();


    pstmt = con->prepareStatement("INSERT INTO Users(Username, FirstName, LastName, Password) Values(?, ?, ?, ?)");
    pstmt->setString(1, username);
    pstmt->execute();
    pstmt->setString(2, firstName);
    pstmt->execute();
    pstmt->setString(3, lastName);
    pstmt->execute();
    pstmt->setString(4, password);
    pstmt->execute();
    delete pstmt;
    delete con;
    system("pause");

    return 0;
}
