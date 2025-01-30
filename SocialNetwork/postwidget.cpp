#include "postwidget.h"

QString PostWidget::getText() const
{
    return text->text();
}

void PostWidget::setText(QString newText)
{
    text->setText(newText);
}

void PostWidget::updatePost(QString newPost) {
    this->post->setText(newPost);
    this->setText(newPost);
}

void PostWidget::showEditPB() {
    this->setEnabled(true);
    this->editPB->show();
}

Post *PostWidget::getPost() {
    return post;
}

void PostWidget::hideEditPB() {
    this->editPB->setEnabled(false);
    this->editPB->hide();
}

PostWidget::PostWidget(Post* post, QWidget* parent) : QFrame(parent), post(post) {
    // Create widgets with `this` as the parent
    this->text = new QLabel(this);
    this->timeAndDate = new QLabel(this);
    this->editPB = new QPushButton(this);

    // Set up widgets
    this->editPB->setStyleSheet(R"(
        QPushButton{
            border : none;
            background : transparent;
        }
    )");

    QIcon icon (":/icons/edit_12108481.png");
    this->editPB->setIcon(icon);
    this->editPB->setIconSize(QSize(15, 15));

    this->text->setText(post->getText());
    this->text->setWordWrap(true);

    QString date = post->getDate().toString("yy/MM/dd");
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

    QSize size(700, 100);
    this->setBaseSize(size);

    // Create layouts with `this` as the parent
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    QSpacerItem *horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hLayout2->addWidget(timeAndDate);
    hLayout2->insertSpacerItem(0, horizontalSpacer);

    hLayout1->addWidget(text);
    hLayout1->addWidget(editPB);
    hLayout1->insertSpacerItem(1, horizontalSpacer);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    connect(editPB, &QPushButton::clicked, this, [this]() {
        emit editPBClicked(this->post, this);
    });
}

PostWidget::~PostWidget(){
    this->text = nullptr;
    this->post = nullptr;
    this->timeAndDate = nullptr;
    this->editPB = nullptr;
    this->deleteLater();
}
