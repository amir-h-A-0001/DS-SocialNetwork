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
    QPixmap tmp = sender->getAvatar();

    avatar->setPixmap(makeCircleScalePixmap(tmp,* new QSize(avatar->size())));

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

    layout->addWidget(avatar, 20);
    layout->addWidget(username,50);
    layout->addWidget(accept,20);
    layout->addWidget(ignore,20);

    connect(accept,&QPushButton::pressed,[this]{emit RequestWidget::accepted(username->text(),this);});
    connect(ignore,&QPushButton::pressed,[this]{emit RequestWidget::ignored(username->text(),this);});
}

QPixmap RequestWidget::makeCircleScalePixmap(QPixmap & pixmap, QSize & size) {

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

