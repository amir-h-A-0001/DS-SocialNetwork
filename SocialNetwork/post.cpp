#include "post.h"

QDate Post::getDate() const
{
    return date;
}

void Post::setDate(const QDate &newDate)
{
    date = newDate;
}

QTime Post::getTime() const
{
    return time;
}

void Post::setTime(const QTime &newTime)
{
    time = newTime;
}

QString Post::getText() const
{
    return text;
}

void Post::setText(const QString &newText)
{
    text = newText;
}

QString Post::getHashCode() const
{
    return hashCode;
}

void Post::setHashCode(const QString &newHashCode)
{
    hashCode = newHashCode;
}

Post::Post() {}
