#include "database.h"

DataBase::DataBase() {


    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("DATABASE ADDERESS"); // enter the adderess here

    if (!DB.open())
        qDebug("failed to open database");




}

User *DataBase::checkPassword(QString username, QString password)
{

}

std::list<QString> *DataBase::recived_requests(QString username)
{

}

bool DataBase::has_requests(QString username)
{

}

void DataBase::editUser(QString username)
{

}

void DataBase::makeFriend(QString userA, QString userB)
{

}

void DataBase::editPost(QString username, QString hashCode)
{

}

void DataBase::deletePost(QString username, QString hashCode)
{

}

std::list<suggestWidget *> *DataBase::suggest(QString username)
{

}
