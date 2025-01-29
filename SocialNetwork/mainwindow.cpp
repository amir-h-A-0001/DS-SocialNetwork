#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(DataBase *database, User * user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(database)
    , user(user) {
    ui->setupUi(this);

    // ui
    setFirstUiSettings();
    setFramesShadow();

    // user
    setUsersFriend();
    setUsersInformation(user);

    // connectes for buttons
    // connect(ui->settingPB, &QPushButton::clicked, [this]{;});
    // connect(ui->searchBoxLE, &QLineEdit::focusIn, )
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

void MainWindow::setUsersInformation(User * userPage) {
    ui->usernameLB->setText(userPage->getUsername());
    ui->nameLB->setText(userPage->getName());
    ui->userBioLB->setText(userPage->getBio());

    if(!user->getAvatar().isNull()) {
        QPixmap avatar = userPage->getAvatar();
        QSize size = ui->userProfileLB->size();
        QPixmap newAvatar = makeCircleScalePixmap(avatar, size);
        ui->userProfileLB->setPixmap(newAvatar);

        if(user->getUsername() == userPage->getUsername()) {
            QIcon icon(newAvatar);
            size.setHeight(70);
            size.setWidth(70);
            ui->homePB->setIcon(icon);
            ui->homePB->setIconSize(size);
        }
    }
    addUsersPosts(userPage);

}

void MainWindow::addUsersFriend() {
    if(friendsSize == 0) return;
    for(int i = 0; i < friendsSize; ++i) {
        addUsersFriendPB(friends[i]);
    }
}

void MainWindow::addUsersFriendPB(User *user) {
    QPushButton * userPB = new QPushButton;
    QVBoxLayout * layout = qobject_cast<QVBoxLayout *>(ui->sideUserSA->layout());

    // set Buttons styleSheet
    userPB->setStyleSheet(R"(
    QPushButton {
        border-radius : 35px;
    }
    )");

    // setButtons Icon and size
    QSize size (70, 70);
    QPixmap pixmap = user->getAvatar();
    QPixmap newPixmap = makeCircleScalePixmap(pixmap, size);

    QIcon icon(newPixmap);

    userPB->setIcon(icon);
    userPB->setIconSize(size);

    layout->insertWidget(0, userPB);

    friendsPB.insert(userPB, user);
    connect(userPB, &QPushButton::clicked, [this]{friendsPBCliced();});
}

void MainWindow::addUsersPosts(User *userPage) {
    std::list<Post> * usersPosts = userPage->getPosts_ptr();

    if(usersPosts->empty()) return;

    for(auto it : *usersPosts) {
        PostWidget *postWidget = new PostWidget(&it);
        addUsersPostsWidgetToSA(postWidget);
        if(user->getUsername() == userPage->getUsername()) {
        // connect its push button -----------------------------------------------------------------
        }
        else {
            // disable its pushbutton --------------------------------------------------------------
        }
    }
}

void MainWindow::addUsersPostsWidgetToSA(PostWidget *post) {
    QVBoxLayout * layout = qobject_cast<QVBoxLayout*> (ui->postsSA->layout());
    layout->insertWidget(layout->count() - 2, post);
}

void MainWindow::cleanUsersPostsSA() {
    QVBoxLayout * layout = qobject_cast<QVBoxLayout*> (ui->postsSA->layout());
    while(layout->count() > 2) {
        QLayoutItem * item = layout->takeAt(0);
        PostWidget * postWidget = qobject_cast<PostWidget *> (item->widget());
        postWidget->deleteLater();
        delete item;
    }
}

void MainWindow::friendsPBCliced() {
    QPushButton * userPB = qobject_cast<QPushButton*>(sender());
    User *user = friendsPB[userPB];

    cleanUsersPostsSA();
    setUsersInformation(user);
    ui->settingPB->hide();
}

void MainWindow::setFirstUiSettings() {
    ui->settingPB->show();
    ui->mainSV->setCurrentIndex(0);
    ui->postsSA->setLayout(ui->verticalLayout_2);
    ui->searchResultSA->setLayout(ui->verticalLayout_3);
    ui->sideUserSA->setLayout(ui->verticalLayout);
    ui->suggestionSA->setLayout(ui->horizontalLayout_2);

}

QPixmap MainWindow::makeCircleScalePixmap(QPixmap & pixmap, QSize & size) {

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

