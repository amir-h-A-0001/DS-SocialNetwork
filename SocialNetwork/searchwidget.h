#pragma once

#include <QObject>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <user.h>
#include <QPainter>
#include <QSpacerItem>

class searchWidget : public QFrame {
Q_OBJECT

    QLabel * avatar;
    QLabel * username;
    QPushButton * request;

    User * user;
    QPixmap makeCircleScalePixmap (QPixmap &pixmap, QSize& size);

    void emit_signal ();
public:
    searchWidget(User* user);

signals :
    void requested (QString username);
    void canceledRequest (QString username);


};
