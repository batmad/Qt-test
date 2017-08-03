#include "addslavedialog.h"
#include "ui_addslavedialog.h"
#include <QCheckBox>
#include <QMessageBox>

AddSlaveDialog::AddSlaveDialog( WorkersController* workersController, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSlaveDialog),
    workersController(workersController)
{
    ui->setupUi(this);
    master = workersController->GetWorker(id);
    ui->txtMaster->setText(master->GetName());

    LoadFreeWorkers();
    CreateSlider();
}

AddSlaveDialog::~AddSlaveDialog()
{
    delete ui;
}

void AddSlaveDialog::on_btnSave_clicked()
{
     int added = 0;
     for(int i = 0; i < ui->scrollAreaWidgetContents->layout()->count(); ++i){
         QWidget *widget = ui->scrollAreaWidgetContents->layout()->itemAt(i)->widget();
         QLayout *layout = widget->layout();
         QCheckBox* check = dynamic_cast<QCheckBox*>(layout->itemAt(0)->widget());
         if(check->isChecked()){
             QLabel* label_id = dynamic_cast<QLabel*>(layout->itemAt(2)->widget());
             int id = label_id->text().toInt();
             Worker* slave = workersController->GetWorker(id);
             if(workersController->AddSlave(master->GetID(), slave->GetID())){
                master->AddSlave(slave);                
                ++added;
             }
         }
     }
     if(added){
         QString str = added > 1 ? "Подчиненные успешно добавлены!" : "Подчиненный успешно добавлен!";
         QMessageBox::information(this, "Поздравляем!", str);
     }
     else
         QMessageBox::critical(this, "Ошибка", "Подчиненные не выбраны");

    LoadFreeWorkers();
    CreateSlider();
}

void AddSlaveDialog::LoadFreeWorkers()
{
    freeWorkers.clear();
    auto slaves = master->GetSlaves();
    for(const auto& worker : workersController->GetWorkers()){
        if(worker == master)
            continue;
        if(std::any_of(slaves.begin(), slaves.end(),[&worker](Worker* slave){ return worker == slave;}))
            continue;
        freeWorkers.push_back(worker);
    }
}

void AddSlaveDialog::CreateSlider()
{
    if(ui->scrollAreaWidgetContents->layout()){
        QLayoutItem *child;
        while ((child = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
            delete child->widget();
        }
        delete ui->scrollAreaWidgetContents->layout();
    }
    QVBoxLayout* v = new QVBoxLayout(ui->scrollAreaWidgetContents);
    for(const auto& worker : freeWorkers){
        QWidget *window = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignLeft);
        QCheckBox* checkBox = new QCheckBox();
        QLabel* text = new QLabel();
        text->setText(worker->GetName());
        QLabel* id = new QLabel();
        id->setText(QString::number(worker->GetID()));
        id->setVisible(false);
        layout->addWidget(checkBox);
        layout->addWidget(text);
        layout->addWidget(id);
        window->setLayout(layout);
        ui->scrollAreaWidgetContents->layout()->addWidget(window);
    }
}
