#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "addemployeedialog.h"
#include "addslavedialog.h"
#include "databasecontroller.h"
#include "workerscontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAddEmployee_clicked();
    void on_btnAddSlave_clicked();
    void on_currentIndexChanged(int index);
    void on_AddEmployee_closed();
    void on_AddSlave_closed();

private:
    void CreateTable(std::vector<Worker*> workers);
    void CreateMainTable();
    void CreateSlaveTable(int id);
    void CleanTable();
    void CreateMastersComboBox();

    DatabaseController* mDB;
    WorkersController* workersController;
    Ui::MainWindow *ui;
    AddEmployeeDialog* addEmployeeDialog;
    AddSlaveDialog* addSlaveDialog;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
