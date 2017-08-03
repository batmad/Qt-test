#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addEmployeeDialog = nullptr;
    addSlaveDialog = nullptr;
    model = nullptr;
    mDB = new DatabaseController();
    workersController = new WorkersController(mDB);    
    CreateMainTable();
    CreateMastersComboBox();
}

MainWindow::~MainWindow()
{
    delete workersController;
    delete mDB;
    CleanTable();
    delete addSlaveDialog;
    delete addEmployeeDialog;
    delete ui;
}


void MainWindow::CleanTable(){
    if(model)
        model->clear();
    delete model;
    model = nullptr;
}

void MainWindow::CreateMastersComboBox()
{
    disconnect(ui->masters,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged(int)));
    ui->masters->clear();
    ui->masters->addItem(QString("Все"), QVariant(0));
    for(auto & worker : workersController->GetWorkers()){
       if(worker->GetRole()->mIsMaster){
           QString name = worker->GetName();
           int id = worker->GetID();
           ui->masters->addItem(name, QVariant(id));
       }
    }
    connect(ui->masters,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged(int)));
}

void MainWindow::CreateTable(std::vector<Worker*> workers)
{
    CleanTable();
    model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Дата приема" << "Базовая ставка" << "Должность" << "Зарплата");
    for(const auto & worker : workers){
        QList<QStandardItem*> items;
        items.append(new QStandardItem(worker->GetName()));
        items.append(new QStandardItem(worker->GetDateStr("dd-MM-yyyy")));
        items.append(new QStandardItem(QString::number(worker->GetBaseSalary())));
        items.append(new QStandardItem(worker->GetRole()->mName));
        items.append(new QStandardItem(QString::number(worker->GetTotalSalary())));
        model->appendRow(items);
    }
    ui->tableWorkers->setModel(model);
}

void MainWindow::CreateMainTable(){
    CreateTable(workersController->GetWorkers());
}

void MainWindow::CreateSlaveTable(int index)
{
    int id = ui->masters->itemData(index).toInt();
    CreateTable(workersController->GetWorker(id)->GetSlaves());
}

void MainWindow::on_btnAddEmployee_clicked()
{
    addEmployeeDialog = new AddEmployeeDialog(workersController, this);
    addEmployeeDialog->setModal(true);
    addEmployeeDialog->show();
    connect(addEmployeeDialog, SIGNAL(rejected()),this,SLOT(on_AddEmployee_closed()));
}

void MainWindow::on_btnAddSlave_clicked()
{
    int id = ui->masters->itemData(ui->masters->currentIndex()).toInt();
    if (id){
        Worker* master = workersController->GetWorker(id);
        if (master && master->GetRole()->mIsMaster){
            addSlaveDialog = new AddSlaveDialog(workersController, id, this);
            addSlaveDialog->setModal(true);
            addSlaveDialog->show();
            connect(addSlaveDialog, SIGNAL(rejected()),this,SLOT(on_AddSlave_closed()));
        }
        else
            QMessageBox::critical(this,"Ошибка полномочий", "Полномочия, выбранного сотрудника не позволяют добавлять подчиненных");
    }
    else
        QMessageBox::warning(this,"Ошибка, не выбран сотрудник", "Выберите сотрудника из выпадающего списка");
}

void MainWindow::on_currentIndexChanged(int index)
{
    if (index)
        CreateSlaveTable(index);
    else
        CreateMainTable();
}

void MainWindow::on_AddEmployee_closed()
{
    workersController->RefreshWorkers();
    CreateMainTable();
    CreateMastersComboBox();
}

void MainWindow::on_AddSlave_closed()
{
    CreateSlaveTable(ui->masters->currentIndex());
}

