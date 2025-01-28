#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include "post.h"

class PostWidget : public QFrame
{
    //Post* post;
    QLabel* text;
    QLabel* timeAndDate;
    QPushButton* editPB;
public:
    PostWidget(Post* post);



    QString getText() const;
    void setText(QString newText);
};

#endif // POSTWIDGET_H
