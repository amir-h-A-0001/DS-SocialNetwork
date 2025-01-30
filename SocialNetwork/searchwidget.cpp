#include "searchwidget.h"

searchWidget::searchWidget(User * user) : user(user) {
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    QSpacerItem * spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hLayout->setContentsMargins(10, 10, 10, 10);
    hLayout->setSpacing(2);

    this->request = new QPushButton(this);
    this->username = new QLabel(this);
    this->avatar = new QLabel(this);

    username->setText(user->getUsername());

    hLayout->addWidget(avatar, 0, Qt::AlignHCenter);
    hLayout->addWidget(username, 0, Qt::AlignHCenter);
    hLayout->addWidget(request, 0, Qt::AlignHCenter);

    hLayout->insertSpacerItem(2, spacer);
    hLayout->insertSpacerItem(1, spacer);


    avatar->setFixedSize(70, 70);
    avatar->setStyleSheet(R"(
        QLabel {
            border-radius: 40px;
        }
    )");

    QPixmap pic = user->getAvatar();
    QSize size (60, 60);
    QPixmap circlePixmap = makeCircleScalePixmap(pic, size);
    avatar->setPixmap(circlePixmap);


    this->setStyleSheet(R"(
    QFrame {
        border-radius : 10px;
        color : rgb(0, 0, 0);
        background-color : rgb(250, 250, 250);
    }
    )");

    request->setStyleSheet(R"(
    QPushButton {
        background-color : rgb(176, 188, 157);
        color : rgb(0, 0, 0);
        border-radius:3px;
    }
        )");

    this->setFixedSize(760, 80);

    request->setFixedSize(80,55);
    request->setText("Request");
    request->setCheckable(true);
    connect(request, &QPushButton::toggled, [this]{emit_signal();});

}

void searchWidget::emit_signal() {
    if(this->request->isChecked()) {
        this->request->setText("Requested");
        emit requested(this->user->getUsername());
    } else {
        this->request->setText("Request");
        emit canceledRequest(this->user->getUsername());
    }
}

QPixmap searchWidget::makeCircleScalePixmap(QPixmap & pixmap, QSize & size) {

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
