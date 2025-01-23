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
    if(checkUsernameLoginError() && checkPasswordLoginError())
        return true;
    return false;
}

bool Login_SignUp::checkUsernameLoginError() {

}

bool Login_SignUp::checkPasswordLoginError() {

}

bool Login_SignUp::checkAllSignupErrors() {
    if(checkUsernameSignupError() && checkPasswordSignupError()
        && checkNameSignupError() && checkEmailError())
        return true;
    return false;
}

bool Login_SignUp::checkUsernameSignupError() {
    QLabel  * usernameError = ui->usernameERLB;
    QString const username = ui->usernameLE->text();
    if(username.length() == 0) {
        usernameError->setText(emptyError());
        return false;
    }

    for(auto it : username)
        if(it.isSymbol() || it.isSpace()) {
            usernameError->setText(invalidError());
            return false;
        }

    return true;
}

bool Login_SignUp::checkPasswordSignupError() {
    QLabel  * passwordError = ui->passwordERLB;
    QString const password = ui->passwordLE->text();

    if(password.length() == 0) {
        passwordError->setText(emptyError());
        return false;
    }

    for(auto it : password)
        if(it.isSymbol() || it.isSpace()) {
            passwordError->setText(invalidError());
            return false;
        }

    return true;
}

bool Login_SignUp::checkNameSignupError() {
    QLabel * nameError = ui->nameERLB;
    QString const name = ui->nameLE->text();

    if(name.length() == 0) {
        nameError->setText(emptyError());
        return false;
    }

    for(auto it : name)
        if(it.isSpace() || it.isSymbol()) {
            nameError->setText(invalidError());
            return false;
        }

    return true;
}

bool Login_SignUp::checkEmailError() {
    QLabel * emailError = ui->emailERLB;
    QString const email = ui->emailLE->text();
    QChar const tmp = '@';

    if(email.length() == 0) {
        emailError->setText(emptyError());
        return false;
    }

    for(auto it : email) {
        if(it == tmp)
            continue;
        if(it.isSpace() || it.isSymbol()) {
            emailError->setText(invalidError());
            return false;
        }
    }

    return true;
}

QString Login_SignUp::emptyError() {
    return "This feild is empty !";
}

QString Login_SignUp::invalidError() {
    return "Invalid data !";
}

QString Login_SignUp::notFoundError() {
    return "This data doesn't exists !";
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
