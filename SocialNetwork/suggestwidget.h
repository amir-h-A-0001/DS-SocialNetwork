#ifndef SUGGESTWIDGET_H
#define SUGGESTWIDGET_H

#include <QFrame>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <user.h>

class suggestWidget : public QFrame
{
 Q_OBJECT

    QFrame avatar;
    QLabel username;
    QLabel source;
    QPushButton request;

    User* user;

public:
    suggestWidget(User* user);
};

#endif // SUGGESTWIDGET_H
