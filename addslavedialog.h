#ifndef ADDSLAVEDIALOG_H
#define ADDSLAVEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include "workerscontroller.h"

namespace Ui {
class AddSlaveDialog;
}

class AddSlaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSlaveDialog(WorkersController* workersController, int id, QWidget *parent = 0);
    ~AddSlaveDialog();

private slots:
    void on_btnSave_clicked();

private:
    void LoadFreeWorkers();
    void CreateSlider();

    std::vector<Worker*> freeWorkers;
    Ui::AddSlaveDialog *ui;
    WorkersController* workersController;
    Worker* master;
    QVBoxLayout* mVerticalLayout;
};

#endif // ADDSLAVEDIALOG_H
