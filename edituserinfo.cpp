#include "edituserinfo.h"
#include "ui_edituserinfo.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

EditUserInfo::EditUserInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserInfo)
{
    ui->setupUi(this);
}

EditUserInfo::~EditUserInfo()
{
    delete ui;
}

void EditUserInfo::on_editButton_clicked()
{
    const QString age = ui->userAge->text();
    const QString height = ui->userHeight->text();
    const QString weight = ui->userWeight->text();
    const QString gender = ui->userGender->text();
    const QString goal = ui->goalCombo->currentText();

    QSqlQuery updatedata;
    QString goalID;

    if(ui->goalCombo->currentText() == "Losing weight"){
        goalID = "1";
    }
    else if(ui->goalCombo->currentText() == "Gaining muscle"){
        goalID = "2";
    }
    else if(ui->goalCombo->currentText() == "Staying fit"){
        goalID = "3";
    }

    if (fieldValidation()) {
        updatedata.prepare(
                "UPDATE userinfo SET Age='" + age + "', Weight='" + weight + "', HeightInches='" + height +
                "', Gender='" + gender + "', Goal='" + goalID + "' WHERE userID='" + getUser() + "'"
        );
        updatedata.exec();
        //qDebug() << updatedata.lastQuery();
        close();
    }
}

void EditUserInfo::setUser(QString rec) {
    received = rec;
}

QString EditUserInfo::getUser() {
    return received;
}

bool EditUserInfo::fieldValidation() {
    const QString age = ui->userAge->text();
    const QString height = ui->userHeight->text();
    const QString weight = ui->userWeight->text();
    const QString gender = ui->userGender->text();
    const QString goal = ui->goalCombo->currentText();

    std::string ageStr = age.toStdString();
    std::string heightStr = height.toStdString();
    std::string weightStr = weight.toStdString();
    std::string genderStr = gender.toStdString();
    std::string goalStr = goal.toStdString();

    if (ageStr != "" && heightStr != "" && weightStr != "" && genderStr != "" && goalStr != "Make a selection...") {
        if (checkDigits(ageStr)) {
            if (checkDigits(heightStr)) {
                if (checkDigits(weightStr)) {
                    return true;
                }
                else {
                    QMessageBox msgBox;
                    msgBox.setText("Weight must be in digit form");
                    msgBox.exec();
                }
            }
            else {
                QMessageBox msgBox;
                msgBox.setText("Height must be in digit form");
                msgBox.exec();
            }
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Age must be in digit form");
            msgBox.exec();
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Not all field are filled in!");
        msgBox.exec();
    }
}

bool EditUserInfo::checkDigits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}
void EditUserInfo::on_close_clicked()
{
    close();
}
