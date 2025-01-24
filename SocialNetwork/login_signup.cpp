#include "login_signup.h"
#include "ui_login_signup.h"
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QFileDialog>
#include <QFrame>

Login_SignUp::Login_SignUp(DataBase *database, QWidget *parent)
    : QMainWindow(parent)
    , database(database)
    , ui(new Ui::Login_SignUp)
{
    ui->setupUi(this);

    setFramesShadow();
    connect(ui->openLoginSignupPB, SIGNAL(toggled(bool)), this, SLOT(animation()));
    connect(ui->loginPB, SIGNAL(clicked(bool)), this, SLOT(loginPBClicked()));
    connect(ui->signupPB, SIGNAL(clicked(bool)), this, SLOT(signupPBClicked()));

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
    bool error1, error2;
    error1 = checkUsernameLoginError();
    error2 = checkPasswordLoginError();

    return error1 && error2;
}

bool Login_SignUp::checkUsernameLoginError() {
    QString const username = ui->usernameLE->text();
    QLabel * usernameError = ui->usernameLoginERLB;

    if(username.length() == 0) {
        usernameError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : username)
        if(it.isSpace() || it.isSymbol()) {
            usernameError->setText(allErrorTexts(2));
            return false;
        }

    if(database->findUser(username) == nullptr) {
        usernameError->setText(allErrorTexts(1));
        return false;
    }

    return true;
}

bool Login_SignUp::checkPasswordLoginError() {
    QString const password = ui->passwordLoginLE->text();
    QLabel *passwordError = ui->passwordLoginERLB;

    if(password.length() == 0) {
        passwordError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : password)
        if(it.isSpace() || it.isSymbol()) {
            passwordError->setText(allErrorTexts(2));
            return false;
        }

    if(checkUsernameLoginError()) {
        User * user = database->findUser(ui->usernameLoginLE->text());
        if(user->getPassword() != password) {
            passwordError->setText(allErrorTexts(1));
            return false;
        }
    }
    return true;
}

bool Login_SignUp::checkAllSignupErrors() {
    bool error1, error2, error3, error4;
    error1 = checkUsernameSignupError();
    error2 = checkPasswordSignupError();
    error3 = checkNameSignupError();
    error4 = checkEmailError();

    return error1 && error2 && error3 && error4;
}

bool Login_SignUp::checkUsernameSignupError() {
    QLabel  * usernameError = ui->usernameERLB;
    QString const username = ui->usernameLE->text();
    if(username.length() == 0) {
        usernameError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : username)
        if(it.isSymbol() || it.isSpace()) {
            usernameError->setText(allErrorTexts(2));
            return false;
        }

    if(database->findUser(username) != nullptr) {
        usernameError->setText(allErrorTexts(3));
        return false;
    }

    return true;
}

bool Login_SignUp::checkPasswordSignupError() {
    QLabel  * passwordError = ui->passwordERLB;
    QString const password = ui->passwordLE->text();

    if(password.length() == 0) {
        passwordError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : password)
        if(it.isSymbol() || it.isSpace()) {
            passwordError->setText(allErrorTexts(2));
            return false;
        }

    if(password.length() < 8) {
        passwordError->setText(allErrorTexts(4));
        return false;
    }

    return true;
}

bool Login_SignUp::checkNameSignupError() {
    QLabel * nameError = ui->nameERLB;
    QString const name = ui->nameLE->text();

    if(name.length() == 0) {
        nameError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : name)
        if(it.isSpace() || it.isSymbol()) {
            nameError->setText(allErrorTexts(2));
            return false;
        }

    return true;
}

bool Login_SignUp::checkEmailError() {
    QLabel * emailError = ui->emailERLB;
    QString const email = ui->emailLE->text();
    QChar const tmp = '@';

    if(email.length() == 0) {
        emailError->setText(allErrorTexts(0));
        return false;
    }

    for(auto it : email) {
        if(it == tmp)
            continue;
        if(it.isSpace() || it.isSymbol()) {
            emailError->setText(allErrorTexts(2));
            return false;
        }
    }

    return true;
}

QString Login_SignUp::allErrorTexts(const int i) {
    QString emptyError ("This feild is empty !");
    QString notFoundError ("This data doesn't exists !");
    QString invalidError ("Invalid data !");
    QString repeatedUsername ("This username is already taken !");
    QString shortPassword ("Password is too short");

    switch (i) {
    case 0:
        return emptyError;
    case 1:
        return notFoundError;
    case 2:
        return invalidError;
    case 3:
        return repeatedUsername;
    case 4:
        return shortPassword;
    default:
        return "What ?";
    }

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
        button->setText("Sign up");

    } else {
        button->hide();
        frameAnimationSignup->start();
        button->setText("Login");

    }
    resetAll();
    connect(frameAnimationLogin, SIGNAL(finished()), button, SLOT(show()));
    connect(frameAnimationSignup, SIGNAL(finished()), button, SLOT(show()));


}

void Login_SignUp::signupPBClicked() {
    resetSignupERLB();
    if(!checkAllSignupErrors()) return;
    // Make new User
    User newUser;
    newUser.setUsername(ui->usernameLE->text());
    newUser.setPassword(ui->passwordLE->text());
    newUser.setName(ui->nameLE->text());
    newUser.setEmail(ui->emailLE->text());

    // Select an avatar
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select an avatar for your account :", "", "*.jpg *.jpeg *.png");

    if(!filePath.isEmpty()) {
        QPixmap avatar;
        avatar.load(filePath);
        newUser.setAvatar(avatar);
    }

    database->addUser(newUser);

    resetAll();
    MainWindow mainWin(database);
    this->close();
    mainWin.show();
}

void Login_SignUp::loginPBClicked() {
    resetLoginERL();
    if(!checkAllLoginErrors()) return;
    resetAll();
    MainWindow mainWin(database);
    this->close();
    mainWin.show();
}

void Login_SignUp::resetAll() {
    // Login Widgets
    ui->usernameLoginLE->setText("");
    ui->passwordLoginLE->setText("");
    resetLoginERL();
    // Signup Widgets
    ui->usernameLE->setText("");
    ui->passwordLE->setText("");
    ui->emailLE->setText("");
    ui->nameLE->setText("");
    resetSignupERLB();
}

void Login_SignUp::resetLoginERL() {
    ui->usernameLoginERLB->setText("");
    ui->passwordLoginERLB->setText("");
}

void Login_SignUp::resetSignupERLB() {
    ui->emailERLB->setText("");
    ui->usernameERLB->setText("");
    ui->nameERLB->setText("");
    ui->passwordERLB->setText("");
}
