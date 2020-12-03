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

    void updateUI();
    void setTableIndex(int rec);
    int getTableIndex();
    void loadData();


private slots:
    void on_start_clicked();
    void updateTime();

    void on_stop_clicked();

    void on_reset_clicked();

private:
    Ui::descriptionDialog *ui;
    QTimer *timer;
    int indexID;
    int tableIndex;
    int time;
    std::string timeStr;
};

#endif // DESCRIPTIONDIALOG_H
