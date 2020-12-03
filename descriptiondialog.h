#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class descriptionDialog;
}

class descriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit descriptionDialog(QWidget *parent = nullptr);
    ~descriptionDialog();
    void setIndexID(int rec);
    int getIndexID();

    void setTableIndex(int rec);
    int getTableIndex();
    void loadData();

private:
    Ui::descriptionDialog *ui;
    int indexID;
    int tableIndex;
};

#endif // DESCRIPTIONDIALOG_H
