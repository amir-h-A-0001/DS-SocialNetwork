#include "postwidget.h"

PostWidget::PostWidget(Post* post) {

    //this->post = post;
    this->text = new QLabel(this);
    this->timeAndDate = new QLabel(this);


    this->text->setText(post->getText());
    this->text->setWordWrap(true);

    QString date = post->getDate().toString("Y,M,D");
    QString time = post->getTime().toString("H,M,S");

    this->timeAndDate->setText(date + " at " + time);
    this->timeAndDate->setStyleSheet(R"(
        QLabel{
            color:rgb(200,200,200);
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(text);
    layout->addWidget(timeAndDate);
}
