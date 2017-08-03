#include "workerscontroller.h"

WorkersController::WorkersController(DatabaseController* db)
{
    mDB = db;
    if(mDB->isOpen()){
        LoadRoles();
        LoadWorkers();
    }
}

WorkersController::~WorkersController()
{
    CleanRoles();
    CleanWorkers();
}

void WorkersController::CleanWorkers()
{
    for(auto & worker : workers){
        delete worker;
    }
    workers.clear();
}

void WorkersController::CleanRoles()
{
    for(auto & role : roles){
        delete role;
    }
    roles.clear();
}

void WorkersController::RefreshWorkers()
{
    CleanWorkers();
    LoadWorkers();
}

void WorkersController::LoadRoles()
{
    QSqlQuery query("SELECT id, name, percent, percent_limit, percent_slave, master FROM roles");
    while(query.next()){
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int percent = query.value(2).toInt();
        int limit = query.value(3).toInt();
        float percentSlave = query.value(4).toFloat();
        bool isMaster = query.value(5).toBool();

        Role* role = new Role(id, name, percent, limit, percentSlave, isMaster);
        roles.push_back(role);
    }
}

void WorkersController::LoadWorkers()
{
    QSqlQuery query("SELECT id, username, date, base_salary, role_id FROM workers");
    while(query.next()){
        int id = query.value(0).toInt();
        QString username = query.value(1).toString();
        QDateTime dTimeStamp;
        dTimeStamp.setTime_t(query.value(2).toLongLong());
        int salary = query.value(3).toInt();
        int roleId = query.value(4).toInt();

        Worker* tWorker = new Worker(id, username, dTimeStamp, salary, GetRole(roleId));
        workers.push_back(tWorker);
    }
    LoadSlaves();
}

void WorkersController::LoadSlaves()
{
    QSqlQuery query("SELECT master_id, slave_id FROM management");
    while(query.next()){
        Worker* master = GetWorker(query.value(0).toInt());
        Worker* slave = GetWorker(query.value(1).toInt());
        master->AddSlave(slave);
    }
}

bool WorkersController::AddWorker(QString username, unsigned long long timestamp, int base_salary, int role_id)
{
    if (!mDB->isOpen() || username == "" || base_salary == 0)
        return false;

    QSqlQuery query;
    query.prepare("INSERT INTO workers (username, date, base_salary, role_id) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(timestamp);
    query.addBindValue(base_salary);
    query.addBindValue(role_id);
    return query.exec();
}

bool WorkersController::AddSlave(int master_id, int slave_id)
{
    if (!mDB->isOpen())
        return false;
    QSqlQuery query;
    query.prepare("INSERT INTO management (master_id, slave_id) "
                  "VALUES (?, ?)");
    query.addBindValue(master_id);
    query.addBindValue(slave_id);
    return query.exec();
}

Worker* WorkersController::GetWorker(int id)
{
    for(const auto & worker : workers){
        if(id == worker->GetID())
            return worker;
    }
    return nullptr;
}

Role* WorkersController::GetRole(int id)
{
    for(const auto & role : roles){
        if(id == role->mId)
            return role;
    }
    return nullptr;
}
