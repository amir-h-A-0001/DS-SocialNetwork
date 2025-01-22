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
};

#endif // POST_H
