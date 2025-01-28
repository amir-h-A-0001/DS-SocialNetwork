#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(DataBase *database, User * user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(database)
    , user(user) {
    ui->setupUi(this);
    ui->postsSA->setLayout(ui->verticalLayout_2);

    setFramesShadow();
    fillTheLabels();
    setUsersFriend();





    // ke ke kari

    Post postt;
    QDate date(::QDate::currentDate());
    postt.setDate(date);
    postt.setText("amiramiramir");
    QTime time(::QTime::currentTime());
    postt.setTime(time);
    PostWidget * post = new PostWidget(&postt);

    QVBoxLayout * layout = qobject_cast<QVBoxLayout *>(ui->postsSA->layout());
    layout->insertWidget(layout->count() - 2, post);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFramesShadow() {
    QGraphicsDropShadowEffect *coverShadow = new QGraphicsDropShadowEffect(ui->userInformationF);
    coverShadow->setBlurRadius(40.0);
    coverShadow->setColor(palette().color(QPalette::Shadow));
    coverShadow->setOffset(0.0);
    ui->userInformationF->setGraphicsEffect(coverShadow);

}

void MainWindow::fillTheLabels() {
    ui->usernameLB->setText(user->getUsername());
    if(!user->getAvatar().isNull())
        ui->userProfileLB->setPixmap(user->getAvatar());
        // for home pb icon ------------------------------------------------------------------------------
    else {

    }
    ui->nameLB->setText(user->getName());
    ui->userBioLB->setText(user->getBio());
}

void MainWindow::setUsersFriend() {
    const std::list<QString> *userFreinds = user->getFriends_ptr();
    const int userFriends = user->getFriends_ptr()->size();

    int userRequests = 0;
    if(database->has_requests(user->getUsername()))
        userRequests = database->recived_requests(user->getUsername())->size();

    friends = new User * [userFriends + userRequests];

    int idx = 0;
    for(auto it : *userFreinds) {
        friends[idx++] = database->findUser(it);
    }
}
