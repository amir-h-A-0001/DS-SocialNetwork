#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <user.h>
#include <QtSql>
#include <list>
#include <suggestwidget.h>


class DataBase
{
private:
    QSqlDatabase DB;

    std::map<QString,User> users;
    std::map<QString,std::list<QString>> requests;
public:
    DataBase();

    User* checkPassword(QString username,QString password);
    std::list<QString>* recived_requests(QString username);
    bool has_requests(QString username);

    void editUser(QString username);
    void makeFriend(QString userA,QString userB);
    void editPost(QString username,QString hashCode);
    void deletePost(QString username,QString hashCode);

    std::list<suggestWidget*>* suggest(QString username);
};

#endif // DATABASE_H
