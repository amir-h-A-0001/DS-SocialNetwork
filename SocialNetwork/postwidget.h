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
    PostWidget(Post* post,QWidget* parent);
    ~PostWidget();

    QString getText() const;
    void setText(QString newText);

    void updatePost (QString newPost);

    void hideEditPB ();
    void showEditPB ();
    Post * getPost ();
signals:
    void editPBClicked(Post* post, PostWidget * postWidget);
};

#endif // POSTWIDGET_H
