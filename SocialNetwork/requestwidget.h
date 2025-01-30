#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <suggestwidget.h>
#include "user.h"

class RequestWidget : public QFrame
{
    Q_OBJECT

    QLabel* avatar;
    QLabel* username;
    QPushButton* accept;
    QPushButton* ignore;

    QPixmap makeCircleScalePixmap (QPixmap &pixmap, QSize& size);

public:
    RequestWidget();
    RequestWidget(User* sender,QWidget* parent = nullptr);
signals:
    void accepted(QString username,RequestWidget* widget);
    void ignored(QString username,RequestWidget* widget);
};

#endif // REQUESTWIDGET_H
