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
    void initializeTrackingModel(QSqlQueryModel *model, int type);
    void initializeExerciseModel(QSqlQueryModel *model, QString exercise);
    void loadTracking();
    void loadExercises();

private slots:

    void on_edit_clicked();
    void on_addWeight_clicked();
    void on_tabWidget_2_tabBarClicked();

    void on_changePassword_clicked();

    void on_logout_clicked();

    void on_recTable_doubleClicked(const QModelIndex &index);

    void on_cardioTable_doubleClicked(const QModelIndex &index);

    void on_coreTable_doubleClicked(const QModelIndex &index);

    void on_lowerTable_doubleClicked(const QModelIndex &index);

    void on_upperTable_doubleClicked(const QModelIndex &index);

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    QString received;


    void loadRecommendations();

    void initializeRecModel(QSqlQueryModel *model);
};
#endif // MAINWINDOW_H
