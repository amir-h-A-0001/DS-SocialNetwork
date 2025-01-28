#ifndef SUGGESTWIDGET_H
#define SUGGESTWIDGET_H

#include <QFrame>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <user.h>
#include <QPainter>

class suggestWidget : public QFrame {
    Q_OBJECT

    QLabel * avatar;
    QLabel * username;
    QLabel * source;
    QPushButton * request;

    User * user;

    QPixmap makeCircleScalePixmap (QPixmap &pixmap, QSize& size);

    void emit_signal ();
public:
    suggestWidget(User* user);
    void setSource(QLabel *newSource);

signals :
    void requested (QString username);
    void canceledRequest (QString username);
};

#endif // SUGGESTWIDGET_H
