#include "user.h"

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    password = newPassword;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}

QString User::getBio() const
{
    return bio;
}

void User::setBio(const QString &newBio)
{
    bio = newBio;
}

QPixmap User::getAvatar() const
{
    return avatar;
}

void User::setAvatar(const QPixmap &newAvatar)
{
    avatar = newAvatar;
}

std::list<QString>* User::getFriends_ptr()
{
    return &friends;
}

void User::setFriends(const std::list<QString> &newFriends)
{
    friends = newFriends;
}

std::list<Post>* User::getPosts_ptr()
{
    return &posts;
}

void User::setPosts(const std::list<Post> &newPosts)
{
    posts = newPosts;
}

User::User() {}

User::User(const QString &username, const QString &password, const QString &name, const QPixmap &avatar) : username(username),
    password(password),
    name(name),
    avatar(avatar)
{
    this->bio = "Recently joined the Graph";
}
