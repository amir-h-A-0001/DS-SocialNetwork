#include "login_signup.h"
#include "ui_login_signup.h"
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QFrame>

Login_SignUp::Login_SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login_SignUp)
{
    ui->setupUi(this);

    setFramesShadow();
    connect(ui->openLoginSignupPB, SIGNAL(toggled(bool)), this, SLOT(animation()));



}

Login_SignUp::~Login_SignUp()
{
    delete ui;
}

void Login_SignUp::setFramesShadow() {
    QGraphicsDropShadowEffect *coverShadow = new QGraphicsDropShadowEffect(ui->mainFrame);
    coverShadow->setBlurRadius(40.0);
    coverShadow->setColor(palette().color(QPalette::Shadow));
    coverShadow->setOffset(0.0);
    ui->mainFrame->setGraphicsEffect(coverShadow);
}

bool Login_SignUp::checkAllLoginErrors() {

}

bool Login_SignUp::checkUsernameLoginError() {

}

bool Login_SignUp::checkPasswordLoginError() {

}

bool Login_SignUp::checkAllSignupErrors() {

}

bool Login_SignUp::checkUsernameSignupError() {

}

bool Login_SignUp::checkPasswordSignupError() {

}


void Login_SignUp::animation() {
    QFrame *frame = ui->picture;
    QPushButton *button = ui->openLoginSignupPB;

    QPropertyAnimation *frameAnimationLogin = new QPropertyAnimation(frame, "geometry", this);
    frameAnimationLogin->setDuration(225);
    frameAnimationLogin->setStartValue(frame->geometry());
    frameAnimationLogin->setEndValue(QRect(frame->x() + 350, frame->y(), frame->width(), frame->height()));

    QPropertyAnimation *frameAnimationSignup = new QPropertyAnimation(frame, "geometry", this);
    frameAnimationSignup ->setDuration(225);
    frameAnimationSignup ->setStartValue(frame->geometry());
    frameAnimationSignup ->setEndValue(QRect(frame->x() - 350, frame->y(), frame->width(), frame->height()));

    if(button->isChecked()) {
        button->hide();
        frameAnimationLogin->start();
        button->setText("Signup");

    } else {
        button->hide();
        frameAnimationSignup->start();
        button->setText("Login");
    }

    connect(frameAnimationLogin, SIGNAL(finished()), button, SLOT(show()));
    connect(frameAnimationSignup, SIGNAL(finished()), button, SLOT(show()));


}
