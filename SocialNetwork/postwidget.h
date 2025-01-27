#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include "post.h"

class PostWidget : public QFrame
{
    //Post* post;
    QLabel* text;
    QLabel* timeAndDate;
public:
    PostWidget(Post* post);


};

#endif // POSTWIDGET_H
