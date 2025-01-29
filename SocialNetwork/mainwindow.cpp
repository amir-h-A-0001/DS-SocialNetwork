#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(DataBase *database, User * user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(database)
    , user(user) {
    ui->setupUi(this);


    setFramesShadow();
    fillTheLabels();
    setUsersFriend();

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

void MainWindow::setSqrollAreasLayout() {
     ui->postsSA->setLayout(ui->verticalLayout_2);
}

void MainWindow::on_newPostPB_clicked()
{
    Post* newPost = new Post;
    PostWidget* newWidget;
    newPost->setHashCode("");

    EditPost* newPostPage = new EditPost(false,user,newPost,&newWidget,database,this);
    this->hide();
    newPostPage->show();

    connect(newPostPage,&EditPost::destroyed,[this, &newPost]{
        if(! newPost->getHashCode().isEmpty()){
            // insert newWidget into the posts
        }
        else delete newPost;
    });
}

