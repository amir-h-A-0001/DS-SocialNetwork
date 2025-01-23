#ifndef POST_H
#define POST_H

#include <QDate>
#include <QTime>
class Post
{
private:
    QString hashCode;

    QDate date;
    QTime time;
    QString text;
public:
    Post();

    QDate getDate() const;
    void setDate(const QDate &newDate);
    QTime getTime() const;
    void setTime(const QTime &newTime);
    QString getText() const;
    void setText(const QString &newText);
    QString getHashCode() const;
    void setHashCode(const QString &newHashCode);

    bool operator == (const Post cp){
        if(cp.hashCode == this->hashCode)
            return true;
        return false;
    }
};

#endif // POST_H
