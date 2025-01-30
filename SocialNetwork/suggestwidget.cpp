#include "suggestwidget.h"



QPixmap suggestWidget::makeCircleScalePixmap(QPixmap & pixmap, QSize & size) {

    QPixmap scaledPixmap = pixmap.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QBitmap mask(size);
    // for background
    mask.fill(Qt::color0);

    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::color1);
    painter.drawEllipse(0, 0, size.width(), size.height());
    painter.end();

    QPixmap circularPixmap(size);
    circularPixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&circularPixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing, true);
    pixmapPainter.setClipRegion(QRegion(mask));
    pixmapPainter.drawPixmap(0, 0, scaledPixmap);
    pixmapPainter.end();

    return circularPixmap;
}

void suggestWidget::emit_signal() {
    if(this->request->isChecked()) {
        this->request->setText("Requested");
        emit requested(this->user->getUsername());
    } else {
        this->request->setText("Request");
        emit canceledRequest(this->user->getUsername());
    }
}

suggestWidget::suggestWidget(User* user) : user(user){



    QVBoxLayout * vLayout = new QVBoxLayout(this);

    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->setSpacing(2);

    this->request = new QPushButton(this);
    this->username = new QLabel(this);
    this->avatar = new QLabel(this);
    this->source = new QLabel(this);

    username->setText(user->getUsername());

    vLayout->addWidget(avatar, 0, Qt::AlignCenter);
    vLayout->addWidget(username, 0, Qt::AlignCenter);
    vLayout->addWidget(source, 0, Qt::AlignCenter);
    vLayout->addWidget(request);
    this->request->setStyleSheet(R"(
    QPushButton {
        background-color : rgb(176, 188, 157);
        color : rgb(0, 0, 0);
        border-radius:3px;
    }
        )");

    avatar->setFixedSize(80, 80);
    avatar->setStyleSheet(R"(
        QLabel {
            border-radius: 40px;
        }
    )");

    QPixmap pic = user->getAvatar();
    QSize size (80, 80);
    QPixmap circlePixmap = makeCircleScalePixmap(pic, size);
    avatar->setPixmap(circlePixmap);


    this->setStyleSheet(R"(
    QFrame {
        border-radius : 10px;
        color : rgb(0, 0, 0);
        background-color : rgb(250, 250, 250);
    }
    )");

    request->setFixedHeight(20);
    request->setStyleSheet(R"(
    QPushButton {
        background-color : rgb(176, 188, 157);
        color : rgb(0, 0, 0);
        border-radius:5px;
    }
        )");

    this->setFixedSize(150, 200);

    request->setText("Request");
    request->setCheckable(true);
    connect(request, &QPushButton::toggled, [this]{emit_signal();});
}
void suggestWidget::setSource(QLabel *newSource)
{
    source = newSource;
}
