#include "worker.h"
#include <QDebug>

Worker::Worker(int id, QString username, QDateTime date, int salary, Role* roleId)
{
    mId = id;
    mUsername = username;
    mDateTime = date;
    mBaseSalary = salary;
    mRole = roleId;
}

Worker::~Worker()
{

}

double Worker::GetTotalSalary()
{
    QDateTime workStart(mDateTime);
    workStart = workStart.addYears(1);
    int years = 0;
    while (workStart <= QDateTime::currentDateTime()){
        years++;
        workStart = workStart.addYears(1);
    }

    double percent = mRole->mYearPercent * years;
    if(percent > mRole->mYearPercentLimit)
        percent = mRole->mYearPercentLimit;


    double slaves_tribute = 0;
    if(mRole->mIsMaster){
        for(const auto& slave : GetTotalSlaves()){
            slaves_tribute += slave->GetTotalSalary();
        }
    }

    return mBaseSalary + mBaseSalary * percent/100 + slaves_tribute * mRole->mSlavePercent / 100;
}

void Worker::AddSlave(Worker *worker)
{
    slaves.push_back(worker);
}

std::vector<Worker*> Worker::GetSubSlaves()
{
    std::set<Worker*> subSlaves;
    GetSlavesRecursively(subSlaves);
    subSlaves.erase(this);

    std::vector<Worker*> workers;
    workers.insert(workers.begin(), subSlaves.begin(), subSlaves.end());
    return workers;
}

void Worker::GetSlavesRecursively(std::set<Worker*>& slaves)
{
    slaves.insert(this);
    for(const auto& slave : this->slaves){
        slave->GetSlavesRecursively(slaves);
    }
}

std::vector<Worker*> Worker::GetTotalSlaves()
{
    switch(mRole->mId){
    default:
    case EMPLOYEE:
    case MANAGER:
        return slaves;
        break;
    case SALES:
        return GetSubSlaves();
        break;
    }
}
