#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include "post.h"

class PostWidget : public QFrame {
    Q_OBJECT
    Post* post;
    QLabel* text;
    QLabel* timeAndDate;
    QPushButton* editPB;
public:
    PostWidget(Post* post);



    QString getText() const;
    void setText(QString newText);

    void hideEditPB ();
    void showEditPB ();
    Post * getPost ();

signals :
    void editPBClicked (PostWidget * postWidget, Post * post);
};

#endif // POSTWIDGET_H
