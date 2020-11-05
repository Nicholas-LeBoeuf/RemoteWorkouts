#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setUser(QString rec);
    QString getUser();
    ~MainWindow();
    void loadData();
    void initializeTrackingModel(QSqlQueryModel *model);
    void initializeExerciseModel(QSqlQueryModel *model, QString exercise);
    void loadTracking();
    void loadExercises();

private slots:

    void on_edit_clicked();
    void on_addWeight_clicked();
    void on_tabWidget_2_tabBarClicked();

private:
    Ui::MainWindow *ui;
    QString received;


};
#endif // MAINWINDOW_H
