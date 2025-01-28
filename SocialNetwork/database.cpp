#include "database.h"


DataBase::DataBase() {


    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("F:/Projects/Instagraph/social-network-alo-amiram/SocialNetwork/DataBase"); // enter the adderess here
    //"F:/Projects/Instagraph/social-network-alo-amiram/SocialNetwork/DataBase"
    //"E:/Code/4031/DataStracture/Social Network Final Project/social-network-alo-amiram/SocialNetwork/DataBase"

    if (!DB.open()){
        qDebug("failed to open database");
        return;
    }

    QSqlQuery read_Qry;
    read_Qry.prepare("SELECT * FROM users");
    if(!read_Qry.exec()){
        qDebug("reading usersData table failed");
        return;
    }

    // temporary variables
    User tmp_user;
    Post tmp_post;

    QDate tmp_date;
    int y,mon,d;

    QTime tmp_time;
    int h,min,s;

    QPixmap tmp_pixmap;
    QByteArray byteArray;
    //-----

    while(read_Qry.next()){

        tmp_user.setUsername(read_Qry.value(0).toString());
        tmp_user.setPassword(read_Qry.value(1).toString());
        tmp_user.setName(read_Qry.value(2).toString());
        tmp_user.setBio(read_Qry.value(3).toString());
        tmp_user.setEmail(read_Qry.value(4).toString());

        byteArray = read_Qry.value(5).toByteArray();
        tmp_pixmap.loadFromData(byteArray);
        tmp_user.setAvatar(tmp_pixmap);

        y=read_Qry.value(6).toInt();
        mon=read_Qry.value(7).toInt();
        d=read_Qry.value(8).toInt();
        tmp_date.setDate(y,mon,d);
        tmp_user.setJoinDate(tmp_date);

        QString friends = read_Qry.value(7).toString();

        int j;

        friends.chop(1);

        while(true){

            j = friends.lastIndexOf('-');

            if (j<0){
                tmp_user.addFriend(friends);
                break;
            }
            tmp_user.addFriend(friends.sliced(j+1));

            friends.chop(friends.size()-j);
        }

        read_Qry.prepare("SELECT * FROM "+tmp_user.getUsername()+"_posts");
        if(!read_Qry.exec()){
            qDebug("reading usersData table failed");
            return;
        }

        while(read_Qry.next()){

            tmp_post.setHashCode(read_Qry.value(0).toString());
            tmp_post.setText(read_Qry.value(1).toString());

            y=read_Qry.value(2).toInt();
            mon=read_Qry.value(3).toInt();
            d=read_Qry.value(4).toInt();

            tmp_date.setDate(y,mon,d);
            tmp_post.setDate(tmp_date);

            h=read_Qry.value(5).toInt();
            min=read_Qry.value(6).toInt();
            s=read_Qry.value(7).toInt();

            tmp_time.setHMS(h,min,s);
            tmp_post.setTime(tmp_time);

            tmp_user.addPost(tmp_post);
        }

        this->users[tmp_user.getUsername()] = tmp_user;
    }

    read_Qry.prepare("SELECT * FROM requests");
    if(!read_Qry.exec()){
        qDebug("reading usersData table failed");
        return;
    }

    while(read_Qry.next()){
        this->requests[read_Qry.value(0).toString()].push_back(read_Qry.value(1).toString());
    }

}

void DataBase::addUser(User &newUser) {
    // Add user to the map
    users[newUser.getUsername()] = newUser;

    // Open Database
    if (!DB.open()) {
        qDebug() << "Failed to open database:" << DB.lastError().text();
        return;
    }

    // Add new user avatar to the database
    QPixmap avatar = newUser.getAvatar();

    // Convert the pixmap into byteArray data to insert it into database
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    avatar.save(&buffer, "PNG");
    buffer.close();

    // insert to data base

    QDate date = newUser.getJoinDate();

    // Make a string of users friends username
    // std::list<QString> * friends = newUser.getFriends_ptr();
    // QString friends_str;
    // for(auto it = friends->begin(); it != friends->end(); ++it) {
    //     friends_str = friends_str  + "/" + *it;
    // }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username,password,name,email,avatar,year,month,day) VALUES (:username,:password,:name,:email,:avatar,:year,:month,:day)");
    query.bindValue(":username", newUser.getUsername());
    query.bindValue(":password", newUser.getPassword());
    query.bindValue(":name", newUser.getName());
    query.bindValue(":email", newUser.getEmail());
    query.bindValue(":year", date.year());
    query.bindValue(":day", date.day());
    query.bindValue(":month", date.month());
    query.bindValue(":avatar", byteArray);
    // query.bindValue(":bio", newUser.getBio());
    // query.bindValue("friends", friends_str);

    query.exec();
    DB.close();
}

void DataBase::editFriends(User *user)
{
    QString friends = "";

    std::list<QString>* friendsList = user->getFriends_ptr();
    for(auto &i : *friendsList){
        friends += i + "-";
    }

    QSqlQuery update_Qry;
    update_Qry.prepare("UPDATE users SET friends='"+friends+"' WHERE username='"+user->getUsername()+"';");
    if(!update_Qry.exec())
        qDebug("userData update failed");
}

void DataBase::editAllRequests()
{
    for (auto &r : this->requests){
        QString senders = "";
        std::list<QString>* requestsList = &r.second;
        for(auto &i : *requestsList){
            senders += i + "-";
        }

        QSqlQuery update_Qry;
        update_Qry.prepare("UPDATE requests SET senders='"+senders+"';");
        if(!update_Qry.exec())
            qDebug("userData update failed");
    }
}

User *DataBase::findUser(QString username)
{
    std::map<QString,User>::iterator itr = this->users.find(username);
    if(itr == this->users.end())
        return nullptr;
    else return &(itr->second);
}

std::list<QString> *DataBase::recived_requests(QString username)
{
    return &(this->requests[username]);
}

bool DataBase::has_requests(QString username)
{
    std::map<QString,std::list<QString>>::iterator itr = requests.find(username);
    if(itr == requests.end())
        return false;
    else return !this->requests[username].empty();
}

void DataBase::cancel_request(QString sender, QString receiver)
{
    std::list<QString>* user_requests = &this->requests[receiver];

    user_requests->remove(sender);
    if(user_requests->empty()){
        this->requests.erase(receiver);

        QSqlQuery delete_Qry;
        delete_Qry.prepare("DELETE FROM requests WHERE receiver='"+receiver+"';");
        if(!delete_Qry.exec())
            qDebug("userData update failed");
    }
    else {

        QString senders = "";
        for (auto &i : *user_requests){
            senders += i + "-";
        }

        QSqlQuery update_Qry;
        update_Qry.prepare("UPDATE requests SET senders='"+senders+"';");
        if(!update_Qry.exec())
            qDebug("userData update failed");
    }
}

void DataBase::editUserData(QString username)
{
    User* user = &this->users[username];

    QSqlQuery update_Qry;
    update_Qry.prepare("UPDATE users SET name = :name, password = :password, email = :email, avatar = :avatar WHERE username = :username;");

    update_Qry.bindValue(":username",user->getUsername());
    update_Qry.bindValue(":password",user->getPassword());
    update_Qry.bindValue(":email",user->getEmail());
    update_Qry.bindValue(":name",user->getName());

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    user->getAvatar().save(&buffer, "PNG");

    update_Qry.bindValue(":avatar",byteArray);

    if(!update_Qry.exec())
        qDebug("userData update failed");



}

void DataBase::makeFriend(QString userA, QString userB)
{
    User* user = &users[userA];
    user->addFriend(userB);
    editFriends(user);

    user = &users[userB];
    user->addFriend(userA);
    editFriends(user);
}

void DataBase::editPost(QString username, QString hashCode,QString newText)
{
    QSqlQuery update_Qry;
    update_Qry.prepare("UPDATE "+username+"_posts SET text='"+newText+"' WHERE hashCode='"+hashCode+"';");
    if(!update_Qry.exec())
        qDebug("userData update failed");
}

void DataBase::deletePost(QString username, QString hashCode)
{
    QSqlQuery delete_Qry;
    delete_Qry.prepare("DELETE FROM "+username+"_posts WHERE hashCode='"+hashCode+"';");
    if(!delete_Qry.exec())
        qDebug("userData update failed");
}

void DataBase::deleteUser(QString username)
{
    User* user = &this->users[username];

    std::list<QString>* userFriends = user->getFriends_ptr();

    // remove friend
    for(auto &f_name : *userFriends){
        User* f = &this->users[f_name];
        f->removeFriend(username);
        editFriends(f);
    }

    // DB
    // remove user
    QSqlQuery delete_Qry;
    delete_Qry.prepare("DELETE FROM users WHERE username='"+username+"';");
    if(!delete_Qry.exec())
        qDebug("userData update failed");

    // remove posts
    delete_Qry.prepare("DROP TABLE "+username+"_posts;");
    if(!delete_Qry.exec())
        qDebug("userData update failed");

    // remove requests
    delete_Qry.prepare("DELETE FROM requests WHERE receiver='"+username+"';");
    if(!delete_Qry.exec())
        qDebug("userData update failed");

    for(auto &r : this->requests){
        r.second.remove(username);
    }
    this->editAllRequests();

}

std::list<suggestWidget *> *DataBase::suggest(QString username)
{
    std::list<suggestWidget*>* suggests = new std::list<suggestWidget*>;
    std::multimap<float,User*> order;

    std::list<QString>* friendsList = users[username].getFriends_ptr();
    for(auto &i : this->users){

        if(i.second.getUsername() == username)
            continue;

        std::list<QString>* i_friendsList = i.second.getFriends_ptr();
        std::map<QString,int> counter;

        for(auto &j : *friendsList){
            counter[j]++;
        }
        for(auto &j : *i_friendsList){
            counter[j]++;
        }

        int common = 0;
        int allFriends = 0;

        for(auto &j :counter){
            if(j.second > 1)
                common++;
            allFriends++;
        }

        if(common == 0){
            float rate;
            QDate joined = i.second.getJoinDate();
            QDate now = QDate::currentDate();

            if(now.year()-joined.year())
                rate = 0;
            else if(now.month() - joined.month() > 1){
                rate = 0;
            }
            else {
                rate = (now.month() - joined.month()) ? 0.25 : 0.5;
                rate -= (now.day()-joined.day()) / 60;
            }

            if(rate)
                order.insert(std::make_pair(rate,&(i.second)));
        }
        else order.insert(std::make_pair((float(common)/ float(allFriends)),&(i.second)));
    }

    int count = 0;
    for(std::multimap<float,User*>::reverse_iterator i = order.rbegin(); i != order.rend() && count < 6;++i){
        suggests->push_back(new suggestWidget(i->second));
    }

    return suggests;
}
