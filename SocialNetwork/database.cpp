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
        qDebug("reading users table failed");
        return;
    }

    while(read_Qry.next()){
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

        QString friends = read_Qry.value(9).toString();

        int j;

        friends.chop(1);

        while(true){

            j = friends.lastIndexOf('-');

            if (j<0){
                if(friends != "")
                    tmp_user.addFriend(friends);
                break;
            }
            tmp_user.addFriend(friends.sliced(j+1));

            friends.chop(friends.size()-j);
        }

        QSqlQuery post_Query;

        post_Query.prepare("SELECT * FROM "+tmp_user.getUsername()+"_posts");
        if(!post_Query.exec()){
            qDebug("reading user's posts table failed");
            return;
        }

        while(post_Query.next()){

            tmp_post.setHashCode(post_Query.value(0).toString());
            tmp_post.setText(post_Query.value(1).toString());

            y=post_Query.value(2).toInt();
            mon=post_Query.value(3).toInt();
            d=post_Query.value(4).toInt();

            tmp_date.setDate(y,mon,d);
            tmp_post.setDate(tmp_date);

            h=post_Query.value(5).toInt();
            min=post_Query.value(6).toInt();
            s=post_Query.value(7).toInt();

            tmp_time.setHMS(h,min,s);
            tmp_post.setTime(tmp_time);

            tmp_user.addPost(tmp_post);
        }

        this->users[tmp_user.getUsername()] = tmp_user;
    }

    QSqlQuery request_Qry;

    request_Qry.prepare("SELECT * FROM requests");
    if(!request_Qry.exec()){
        qDebug("reading request table failed");
        return;
    }

    while(request_Qry.next()){

        QString receiver = request_Qry.value(0).toString();
        QString senders = request_Qry.value(1).toString();
        std::list<QString>* sendersList = &this->requests[receiver];

        int j;

        senders.chop(1);

        while(true){

            j = senders.lastIndexOf('-');

            if (j<0){
                if(senders != "")
                    sendersList->push_back(senders);
                break;
            }
            sendersList->push_back(senders.sliced(j+1));

            senders.chop(senders.size()-j);
        }
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
    query.exec();

    query.clear();

    query.prepare("CREATE TABLE "+newUser.getUsername()+"_posts (hashCode TEXT,text TEXT,year INTEGER,month  INTEGER,day INTEGER,hour INTEGER,minute INTEGER,second INTEGER);");

    if(!query.exec()){
        qDebug("failed to create the new table");
    }

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
        update_Qry.prepare("UPDATE requests SET senders='"+senders+"' WHERE receiver = "+r.first+";");
        if(!update_Qry.exec())
            qDebug("userData update failed");
    }
}

bool DataBase::haveRequest(QString userA, QString userB)
{
    std::map<QString,std::list<QString>>::iterator itrA = this->requests.find(userA);
    std::map<QString,std::list<QString>>::iterator itrB = this->requests.find(userB);

    if(itrA != this->requests.end()){
        std::list<QString> senders = itrA->second;

        for(auto &user : senders){
            if(user == userB)
                return true;
        }
    }
    if(itrB != this->requests.end()){
        std::list<QString> senders = itrB->second;

        for(auto &user : senders){
            if(user == userA)
                return true;
        }
    }
    return false;
}

bool DataBase::areFriends(User* userA, User* userB)
{
    std::list<QString>* Afriends = userA->getFriends_ptr();
    std::list<QString>* Bfriends = userB->getFriends_ptr();

    QString Ausername = userA->getUsername();
    QString Busername = userB->getUsername();

    if(Afriends->size() < Bfriends->size()){
        for(auto &f : *Afriends){
            if(f == Busername)
                return true;
        }
    }
    else {
        for(auto &f : *Bfriends){
            if(f == Ausername)
                return true;
        }
    }
    return false;
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

void DataBase::cancelRequest(QString sender, QString receiver)
{
    std::list<QString>* user_requests = &this->requests[receiver];

    user_requests->remove(sender);
    if(user_requests->empty()){
        this->requests.erase(receiver);

        QSqlQuery delete_Qry;
        delete_Qry.prepare("DELETE FROM requests WHERE receiver='"+receiver+"';");
        if(!delete_Qry.exec())
            qDebug("delete requests of the user failed");
    }
    else {

        QString senders = "";
        for (auto &i : *user_requests){
            senders += i + "-";
        }

        QSqlQuery update_Qry;
        update_Qry.prepare("UPDATE requests SET senders='"+senders+"' WHERE receiver='"+receiver+";");
        if(!update_Qry.exec())
            qDebug("updating user requests failed");
    }
}

void DataBase::sendRequest(QString sender, QString receiver)
{
    if(haveRequest(sender,receiver) || areFriends(&users[sender],&users[receiver]))
        return;

    std::map<QString,std::list<QString>>::iterator itr = this->requests.find(receiver);

    if(itr == this->requests.end()){
        this->requests[receiver].push_back(sender);

        QSqlQuery add_Qry;
        add_Qry.prepare("INSERT INTO requests (receiver,senders) VALUES (:receiver,:senders)");
        add_Qry.bindValue(":receiver",receiver);
        add_Qry.bindValue(":senders",sender+"-");

        if(!add_Qry.exec())
            qDebug("adding new request list for user failed");
    }
    else {
        itr->second.push_back(sender);

        QString senders = "";
        std::list<QString>* requestsList = &itr->second;
        for(auto &i : *requestsList){
            senders += i + "-";
        }

        QSqlQuery update_Qry;
        update_Qry.prepare("UPDATE requests SET senders='"+senders+"' WHERE receiver='"+receiver+";");
        if(!update_Qry.exec())
            qDebug("updating user requests failed");
    }
}

void DataBase::addPost(Post &post,QString username)
{
    QSqlQuery add_Qry;
    add_Qry.prepare("INSERT INTO "+username+"_posts (hashCode,text,year,month,day,hour,minute,second) VALUES (:hashCode,:text,:year,:month,:day,:hour,:minute,:second)");
    add_Qry.bindValue(":hashCode",post.getHashCode());
    add_Qry.bindValue(":text",post.getText());
    QDate date = post.getDate();
    add_Qry.bindValue(":year",date.year());
    add_Qry.bindValue(":month",date.month());
    add_Qry.bindValue(":day",date.day());
    QTime time = post.getTime();
    add_Qry.bindValue(":hour",time.hour());
    add_Qry.bindValue(":minute",time.minute());
    add_Qry.bindValue(":second",time.second());

    if(!add_Qry.exec())
        qDebug("adding new post failed");
}

void DataBase::editUserData(QString username)
{
    User* user = &this->users[username];

    QSqlQuery update_Qry;
    update_Qry.prepare("UPDATE users SET name = :name, password = :password, bio = :bio, email = :email, avatar = :avatar WHERE username = :username;");

    update_Qry.bindValue(":username",user->getUsername());
    update_Qry.bindValue(":password",user->getPassword());
    update_Qry.bindValue(":bio",user->getBio());
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

void DataBase::editPost(QString username,Post* post)
{
    QSqlQuery update_Qry;
    update_Qry.prepare("UPDATE "+username+"_posts SET text='"+post->getText()+"' WHERE hashCode='"+post->getHashCode()+"';");
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
        qDebug("userData delete failed");

    // remove posts
    delete_Qry.prepare("DROP TABLE "+username+"_posts;");
    if(!delete_Qry.exec())
        qDebug("delete user's posts table failed");

    // remove requests
    delete_Qry.prepare("DELETE FROM requests WHERE receiver='"+username+"';");
    if(!delete_Qry.exec())
        qDebug("delete user's received requests failed");

    for(auto &r : this->requests){
        r.second.remove(username);
    }
    this->editAllRequests();

}

std::list<suggestWidget *> *DataBase::suggest(QString username)
{
    User* user = &users[username];
    std::list<suggestWidget*>* suggests = new std::list<suggestWidget*>;
    std::multimap<float,User*> order;
    std::list<QString>* friendsList = user->getFriends_ptr();

    for(auto &i : this->users){

        if((i.second.getUsername() == username)|| haveRequest(username,i.second.getUsername()) || areFriends(user,&i.second))
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
    for(std::multimap<float,User*>::reverse_iterator i = order.rbegin(); i != order.rend() && (count < 6);++i){
        suggests->push_back(new suggestWidget(i->second));
        count++;
    }

    return suggests;
}
