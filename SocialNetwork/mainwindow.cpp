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

    // user
    setUsersFriend();
    setUsersInformation(user);
    addUsersFriend();
    ui->searchErrorLB->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    this->deleteLater();
}

void MainWindow::setFramesShadow() {
    QGraphicsDropShadowEffect *coverShadow = new QGraphicsDropShadowEffect(ui->userInformationF);
    coverShadow->setBlurRadius(40.0);
    coverShadow->setColor(palette().color(QPalette::Shadow));
    coverShadow->setOffset(0.0);
    ui->userInformationF->setGraphicsEffect(coverShadow);

    QGraphicsDropShadowEffect *buttonCoverShadow = new QGraphicsDropShadowEffect(ui->homePB);
    buttonCoverShadow->setBlurRadius(40.0);
    buttonCoverShadow->setColor(palette().color(QPalette::Shadow));
    buttonCoverShadow->setOffset(0.0);
    ui->homePB->setGraphicsEffect(coverShadow);

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
    this->friendsSize = idx;
}

void MainWindow::setUsersInformation(User * userPage) {
    cleanUsersPostsSA();
    ui->usernameLB->setText(userPage->getUsername());
    ui->nameLB->setText(userPage->getName());
    ui->userBioLB->setText(userPage->getBio());

    if(user->getUsername() == userPage->getUsername()) {
        ui->settingPB->show();
    }

    if(!user->getAvatar().isNull()) {
        QPixmap avatar = userPage->getAvatar();
        QSize size = ui->userProfileLB->size();
        QPixmap newAvatar = makeCircleScalePixmap(avatar, size);
        ui->userProfileLB->setPixmap(newAvatar);
        ui->userProfileLB->setAlignment(Qt::AlignCenter);

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
    connect(userPB, SIGNAL(clicked(bool)), this, SLOT(friendsPBCliced()));
}

void MainWindow::addUsersPosts(User *userPage) {
    std::list<Post> * usersPosts = userPage->getPosts_ptr();

    if(usersPosts->empty()) return;

    for(auto &it : *usersPosts) {
        PostWidget *postWidget = new PostWidget(&it,this);
        addUsersPostsWidgetToSA(postWidget);
        if(user->getUsername() == userPage->getUsername()) {
            connect(postWidget, &PostWidget::editPBClicked, this, [this, &it, postWidget]() {
                openEditPost(&it, postWidget);
            });
        }
        else {
            postWidget->hideEditPB();
        }
    }
}

void MainWindow::addUsersPostsWidgetToSA(PostWidget *post) {
    QVBoxLayout * layout = qobject_cast<QVBoxLayout*> (ui->widget->layout());
    layout->insertWidget(layout->count() - 2, post);
}

void MainWindow::cleanUsersPostsSA() {
    QVBoxLayout * layout = qobject_cast<QVBoxLayout*> (ui->widget->layout());
    while(layout->count() > 2) {
        QLayoutItem * item = layout->takeAt(0);
        PostWidget * postWidget = qobject_cast<PostWidget *> (item->widget());
        layout->removeItem(item);
        postWidget->setParent(nullptr);
        postWidget = nullptr;
        item = nullptr;
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
    setFramesShadow();
    ui->mainSV->setCurrentIndex(0);
    ui->widget->setLayout(ui->verticalLayout_2);
    ui->searchResultSA->setLayout(ui->verticalLayout_3);
    ui->sideUserSA->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(Qt::AlignHCenter);
    ui->suggestSA->widget()->setLayout(ui->horizontalLayout_2);
    ui->suggestSA->widget()->setMinimumHeight(220);
    ui->suggestSA->widget()->setFixedHeight(220);
    ui->suggestSA->setAlignment(Qt::AlignTop);
    ui->suggestSA->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    EditPost* newPostPage = new EditPost(false,user,newPost,nullptr,database,this);
    this->hide();
    newPostPage->show();

    connect(newPostPage, &EditPost::newPost, this, &MainWindow::newPost);
}

void MainWindow::newPost(Post *newPost) {
    if(!newPost->getHashCode().isEmpty()) {
        PostWidget * postWidget = new PostWidget(newPost, nullptr);
        this->addUsersPostsWidgetToSA(postWidget);
        connect(postWidget, &PostWidget::editPBClicked, this, [this, newPost, postWidget]() {
            openEditPost(newPost, postWidget);
        });

    }
}

void MainWindow::on_settingPB_clicked() {
    this->hide();
    Settings * settingWindow = new Settings(user, database, this);
    settingWindow->show();
    connect(settingWindow, &QMainWindow::destroyed, [this]{
        setUsersInformation(user);
        disconnect();
    });

}

void MainWindow::openEditPost(Post *post, PostWidget *widget) {

    EditPost* editWindow = new EditPost(true, user, post, widget, database, this);

    connect(editWindow, &EditPost::postDeleted, this, &MainWindow::deletePostWidget);

    connect(editWindow, &EditPost::postUpdated, this, [widget](QString newText) {
            widget->updatePost(newText);
        });
        editWindow->show();

}

void MainWindow::on_searchPB_clicked()
{
    ui->searchErrorLB->hide();

    QString enteredUsername = ui->searchBoxLE->text();
    User* user = database->findUser(enteredUsername);

    if(user == nullptr){
        ui->searchErrorLB->setText("user was not found");
        ui->searchErrorLB->show();
        return;
    }

    searchWidget* foundUser = new searchWidget(user);
    connect(foundUser,&searchWidget::requested,this,&MainWindow::sentRequest);
    connect(foundUser,&searchWidget::canceledRequest,this,&MainWindow::canceledRequest);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->verticalLayout_3);
    layout->insertWidget(0,foundUser);


}

void MainWindow::on_sideSearchPB_clicked()
{
    if(ui->mainSV->currentIndex() == 1)
        return;

    ui->mainSV->setCurrentIndex(1);

    std::list<suggestWidget*>* suggestions = this->database->suggest(this->user->getUsername());
    for(auto &suggestion : *suggestions){
        ui->horizontalLayout_2->insertWidget(0,suggestion);

        connect(suggestion,&suggestWidget::requested,this,&MainWindow::sentRequest);
        connect(suggestion,&suggestWidget::canceledRequest,this,&MainWindow::canceledRequest);
    }
}

void MainWindow::sentRequest(QString receiver) {
    this->database->sendRequest(this->user->getUsername(),receiver);
}

void MainWindow::canceledRequest(QString receiver)
{
    this->database->cancelRequest(this->user->getUsername(),receiver);
}


void MainWindow::on_homePB_clicked()
{
    ui->mainSV->setCurrentIndex(0);
    setUsersInformation(this->user);
}


void MainWindow::on_sideRequestPB_clicked()
{
    Requests *reqPage = new Requests(this->user,this->database,this);
    reqPage->show();
    this->hide();

    connect(reqPage, &Requests::destroyed, [this]{
        setUsersFriend();
    });
}


void MainWindow::on_sideLogoutPB_clicked()
{
    this->parentWidget()->show();
    this->close();
    this->setParent(nullptr);
}

void MainWindow::deletePostWidget(PostWidget *widget) {
    QVBoxLayout * layout = qobject_cast<QVBoxLayout *>(ui->widget->layout());

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem * item = layout->itemAt(i);
        if(widget == qobject_cast<PostWidget*>(item->widget())) {
            PostWidget * tmp = qobject_cast<PostWidget*>(item->widget());
            layout->removeItem(item);
            tmp->setParent(nullptr);
            tmp = nullptr;
        }
    }
    widget = nullptr;
}

void MainWindow::on_mainSV_currentChanged(int arg1)
{
    QHBoxLayout * layout = qobject_cast<QHBoxLayout *>(ui->horizontalLayout_2);


    while(layout->count() > 1) {
        QLayoutItem * item = layout->itemAt(0);

        suggestWidget* tmp = qobject_cast<suggestWidget*>(item->widget());
        layout->removeItem(item);
        tmp->setParent(nullptr);
        tmp = nullptr;

    }
}

