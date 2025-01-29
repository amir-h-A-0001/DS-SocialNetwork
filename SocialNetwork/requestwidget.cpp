#include "requestwidget.h"

RequestWidget::RequestWidget() {}

RequestWidget::RequestWidget(User *sender)
{
    this->setStyleSheet(R"(
        QFrame{
            background-color = rgb(255,255,255);
            border-radius:10px;
        }
    )");

    username = new QLabel(this);
    username->setText(sender->getUsername());

    username->setStyleSheet(R"(
        QLabel{
            font: 10pt "Dosis";
            background = transparent;
        }
    )");

    avatar = new QLabel(this);
    avatar->setPixmap(sender->getAvatar());

    accept = new QPushButton(this);
    ignore = new QPushButton(this);

    accept->setStyleSheet(R"(
        QPushButton{
            background-color:rgb(50,94,58);
        }
    )");
    // add icon to css

    ignore->setStyleSheet(R"(
        QPushButton{
            background-color:rgb(94,50,58);
        }
    )");
    // add icon to css


    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(avatar,20);
    layout->addWidget(username,50);
    layout->addWidget(accept,20);
    layout->addWidget(ignore,20);

    connect(accept,&QPushButton::pressed,[this]{emit RequestWidget::accepted(username->text(),this);});
    connect(ignore,&QPushButton::pressed,[this]{emit RequestWidget::ignored(username->text(),this);});
}
