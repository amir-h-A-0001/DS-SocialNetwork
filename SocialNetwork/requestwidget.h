#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "user.h"

class RequestWidget : public QFrame
{
    Q_OBJECT

    QLabel* avatar;
    QLabel* username;
    QPushButton* accept;
    QPushButton* ignore;

public:
    RequestWidget();
    RequestWidget(User* sender);
signals:
    void accepted(QString username);
    void ignored(QString username);
};

#endif // REQUESTWIDGET_H
