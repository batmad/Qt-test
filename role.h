#ifndef ROLE_H
#define ROLE_H
#include <QString>

struct Role
{
public:
    Role(int roleId, QString name, float percent, int limit, float slavePercent, bool isMaster){
        mId = roleId;
        mName = name;
        mYearPercent = percent;
        mYearPercentLimit = limit;
        mSlavePercent = slavePercent;
        mIsMaster = isMaster;
    }
    QString mName;
    int mId;
    int mYearPercentLimit;
    int mYearPercent;
    float mSlavePercent;
    bool mIsMaster;
};

#endif // ROLE_H
