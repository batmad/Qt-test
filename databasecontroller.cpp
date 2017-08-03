#include "databasecontroller.h"
#include <QDebug>
#include <QDir>

DatabaseController::DatabaseController()
{
    QString db_path = QDir::currentPath() + "/workers.db";
    qDebug() << db_path;
    mDB = QSqlDatabase::addDatabase("QSQLITE");
    mDB.setDatabaseName(db_path);
    QFileInfo checkFile(db_path);

    if(checkFile.isFile()){
        if(mDB.open()){
            qDebug() << "[+]Connected to Database File :)";
        }
        else{
            qDebug() << "[-]Couldn'y connect to Database File :[";
        }
    }else{
        qDebug() << "[!]Database File doesn't exist :(";
    }
}

DatabaseController::~DatabaseController(){
    mDB.close();
}


