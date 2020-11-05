#ifndef EDITUSERINFO_H
#define EDITUSERINFO_H

#include <QDialog>

namespace Ui {
class EditUserInfo;
}

class EditUserInfo : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserInfo(QWidget *parent = nullptr);
    void setUser(QString rec);
    QString getUser();
    ~EditUserInfo();

    bool fieldValidation();
    bool checkDigits(const std::string &str);

private slots:
    void on_editButton_clicked();

    void on_close_clicked();

private:
    Ui::EditUserInfo *ui;
    QString received;
};

#endif // EDITUSERINFO_H
