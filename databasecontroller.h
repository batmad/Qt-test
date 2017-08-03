#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QtSql>

class DatabaseController
{
public:
    DatabaseController();
    ~DatabaseController();

    bool isOpen(){ return mDB.open(); }

private:
    QSqlDatabase mDB;
};

#endif // DATABASECONTROLLER_H
