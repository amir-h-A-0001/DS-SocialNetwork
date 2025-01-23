#ifndef USER_H
#define USER_H

#include <QString>
#include <QPixmap>
#include <list>
#include <post.h>

class User
{
private:
    QString username;
    QString password;
    QString name;
    QString bio;
    QString email;
    QPixmap avatar;
    QDate joinDate;

    std::list<QString> friends;
    std::list<Post> posts;
public:
    User();
    User(const QString &username, const QString &password, const QString &name, const QPixmap &avatar);

    QString getUsername() const;
    void setUsername(const QString &newUsername);
    QString getPassword() const;
    void setPassword(const QString &newPassword);
    QString getName() const;
    void setName(const QString &newName);
    QString getBio() const;
    void setBio(const QString &newBio);
    QPixmap getAvatar() const;
    void setAvatar(const QPixmap &newAvatar);
    std::list<QString>* getFriends_ptr();
    void setFriends(const std::list<QString> &newFriends);
    std::list<Post>* getPosts_ptr();
    void setPosts(const std::list<Post> &newPosts);
    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QDate getJoinDate() const;
    void setJoinDate(const QDate &newJoinDate);

    void addFriend(QString username);
    void removeFriend(QString username);
    void addPost(Post& post);
    void removePost(Post& post);
};

#endif // USER_H
