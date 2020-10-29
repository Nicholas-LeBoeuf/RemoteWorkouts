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
    ~EditUserInfo();

private:
    Ui::EditUserInfo *ui;
};

#endif // EDITUSERINFO_H
