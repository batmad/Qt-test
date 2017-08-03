#ifndef WORKER_H
#define WORKER_H
#include <vector>
#include <QDateTime>
#include "role.h"
#include <set>

class Worker
{
public:
    enum {
        EMPLOYEE = 1,
        MANAGER,
        SALES
    };
    Worker(int id, QString username, QDateTime date, int salary, Role* roleId);
    ~Worker();
    double GetTotalSalary();
    void AddSlave(Worker* worker);
    int GetID(){return mId;}
    int GetBaseSalary(){return mBaseSalary;}
    QString GetName(){return mUsername;}
    QString GetDateStr(QString format){return mDateTime.toString(format);}
    Role* GetRole(){return mRole;}
    std::vector<Worker*> GetSlaves(){return slaves;}
private:
    std::vector<Worker*> GetTotalSlaves();
    std::vector<Worker*> GetSubSlaves();
    void GetSlavesRecursively(std::set<Worker*>& slaves);
    std::vector<Worker*> slaves;
    Role* mRole;
    QString mUsername;
    QDateTime mDateTime;
    int mId;
    int mBaseSalary;

};

#endif // WORKER_H
