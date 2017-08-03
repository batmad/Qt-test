#ifndef WORKERSCONTROLLER_H
#define WORKERSCONTROLLER_H
#include "databasecontroller.h"
#include "worker.h"
#include "role.h"

class WorkersController
{
public:
    WorkersController(DatabaseController* db);
    ~WorkersController();

    void RefreshWorkers();
    bool AddWorker(QString username, unsigned long long timestamp, int base_salary, int role_id);
    bool AddSlave(int master_id, int slave_id);
    std::vector<Worker*> GetWorkers(){return workers;}
    std::vector<Role*> GetRoles() {return roles;}
    Worker* GetWorker(int id);
    Role *GetRole(int id);

private:
    void LoadRoles();
    void LoadWorkers();
    void LoadSlaves();
    void CleanWorkers();
    void CleanRoles();

    std::vector<Worker*> workers;
    std::vector<Role*> roles;
    DatabaseController* mDB;
};

#endif // WORKERSCONTROLLER_H
