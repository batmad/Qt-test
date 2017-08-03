#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>
#include "workerscontroller.h"

namespace Ui {
class AddEmployeeDialog;
}

class AddEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeDialog( WorkersController* workersController, QWidget *parent = 0);
    ~AddEmployeeDialog();

private slots:
    void on_btnAdd_clicked();
    void on_btnClear_clicked();

private:
    void LoadRoles();
    Ui::AddEmployeeDialog *ui;
     WorkersController* workersController;
};

#endif // ADDEMPLOYEEDIALOG_H
