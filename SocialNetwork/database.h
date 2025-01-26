#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <user.h>
#include <QtSql>
#include <list>
#include <suggestwidget.h>
#include <QSqlDatabase>
#include <QString>

class DataBase
{
    QSqlDatabase DB;

    std::map<QString,User> users;
    std::map<QString,std::list<QString>> requests;

private:
    void editFriends(User* user);
    void editAllRequests();
public:
    DataBase();

    void addUser (User& user);

    User* findUser(QString username);
    std::list<QString>* recived_requests(QString username);
    bool has_requests(QString username);
    void cancel_request(QString sender,QString receiver);

    void editUserData(QString username);
    void makeFriend(QString userA,QString userB);
    void editPost(QString username,QString hashCode,QString newText);
    void deletePost(QString username,QString hashCode);
    void deleteUser(QString username);

    std::list<suggestWidget*>* suggest(QString username);
};

#endif // DATABASE_H
