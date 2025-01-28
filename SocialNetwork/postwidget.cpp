#include "postwidget.h"

PostWidget::PostWidget(Post* post) {

    //this->post = post;
    this->text = new QLabel(this);
    this->timeAndDate = new QLabel(this);
    this->editPB = new QPushButton(this);

    this->text->setText(post->getText());
    this->text->setWordWrap(true);

    QString date = post->getDate().toString("yy,MM,dd");
    QString time = post->getTime().toString("HH:mm:ss");

    this->timeAndDate->setText(date + " at " + time);

    this->setStyleSheet(R"(
        QFrame {
            border-radius: 10px;
            background-color: rgb(255, 255, 255);
        }
        QLabel{
            color:rgb(0,0,0);
        }
        QPushButton {
            background-color: rgba(125, 125, 125,20);
        }
    )");

    QSize  size(800, 100);
    this->setBaseSize(size);

    QVBoxLayout * vLayout = new QVBoxLayout(this);
    QHBoxLayout * hLayout2 = new QHBoxLayout(this);
    QHBoxLayout * hLayout1 = new QHBoxLayout(this);
    QSpacerItem * horizentalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hLayout2->addWidget(timeAndDate);
    hLayout2->insertSpacerItem(0, horizentalSpacer);

    hLayout1->addWidget(text);
    hLayout1->addWidget(editPB);
    hLayout1->insertSpacerItem(1, horizentalSpacer);

    vLayout->insertItem(0, hLayout1);
    vLayout->insertItem(1, hLayout2);
}
