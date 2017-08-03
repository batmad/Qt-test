#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"
#include "QDateTime"
#include <QSqlQuery>
#include <QMessageBox>

AddEmployeeDialog::AddEmployeeDialog(WorkersController* wc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployeeDialog),
    workersController(wc)
{
    ui->setupUi(this);
    ui->txtDate->setDateTime(QDateTime::currentDateTime());
    LoadRoles();
}

AddEmployeeDialog::~AddEmployeeDialog()
{
    delete ui;
}

void AddEmployeeDialog::on_btnAdd_clicked()
{
    int role_id = ui->txtRole->itemData(ui->txtRole->currentIndex()).toInt();
    qDebug() << role_id;
    QDateTime date = ui->txtDate->dateTime();
    unsigned long long timestamp = date.toMSecsSinceEpoch() / 1000; 

    bool result = workersController->AddWorker(ui->txtName->text(), timestamp, ui->txtSalary->text().toInt(), role_id);
    if (result)
        QMessageBox::information(this,"Новый сотрудник", "Успешно добавлен!");
    else
        QMessageBox::critical(this,"Новый сотрудник", "Возникла ошибка");
}

void AddEmployeeDialog::on_btnClear_clicked()
{
    ui->txtName->clear();
    ui->txtDate->setDateTime(QDateTime::currentDateTime());
    ui->txtSalary->clear();
    ui->txtRole->setCurrentIndex(0);
}

void AddEmployeeDialog::LoadRoles(){
    for(const auto & role : workersController->GetRoles()){
        ui->txtRole->addItem(role->mName, QVariant(role->mId));
    }
}
