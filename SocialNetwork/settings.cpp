#include "settings.h"
#include "ui_settings.h"

Settings::Settings(User* user,DataBase* dataBase,QWidget *parent)
    : QMainWindow(parent)
    , user(user)
    , dataBase(dataBase)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *publicDataFrame_coverShadow = new QGraphicsDropShadowEffect(ui->profileF);
    publicDataFrame_coverShadow->setBlurRadius(40.0);
    publicDataFrame_coverShadow->setColor(palette().color(QPalette::Shadow));
    publicDataFrame_coverShadow->setOffset(0.0);
    ui->profileF->setGraphicsEffect(publicDataFrame_coverShadow);

    QGraphicsDropShadowEffect *privateDataFrame_coverShadow = new QGraphicsDropShadowEffect(ui->privateDataF);
    privateDataFrame_coverShadow->setBlurRadius(40.0);
    privateDataFrame_coverShadow->setColor(palette().color(QPalette::Shadow));
    privateDataFrame_coverShadow->setOffset(0.0);
    ui->privateDataF->setGraphicsEffect(privateDataFrame_coverShadow);

    ui->avatarL->setPixmap(user->getAvatar());
    ui->nameLE->setPlaceholderText(user->getName());
    ui->infoTE->setPlaceholderText(user->getBio());
    ui->emailLE->setPlaceholderText(user->getEmail());

    ui->passwordErrorL->hide();
    ui->repaetErrorL->hide();

    int size = ui->avatarL->size().height();
    QPixmap userPixmap = user->getAvatar();
    QPixmap circularAvatar = makeCircleScalePixmap(userPixmap, *new QSize(size, size));

    ui->avatarL->setPixmap(circularAvatar);

    this->changedAvatar = false;
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_avatarPB_clicked()
{
    QString filter = "Image Files (*.png *.jpg *.jpeg *.bmp);;All Files (*)";
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Choose an Image",
                                                    "",
                                                    filter);

    if(filePath.length() != 0 && newAvatar.load(filePath)){
        changedAvatar = true;

        int size = ui->avatarL->height()-1;

        QPixmap circularAvatar(size, size);
        circularAvatar.fill(Qt::transparent);

        QPainter painter(&circularAvatar);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        // Draw a circle
        QPainterPath path;
        path.addEllipse(0, 0, size, size);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, size, size, newAvatar.scaled(size, size, Qt::KeepAspectRatioByExpanding));

        ui->avatarL->setPixmap(circularAvatar);
    }
}


void Settings::on_savePB_clicked()
{
    QString newName = ui->nameLE->text();
    QString newEmail = ui->emailLE->text();
    QString newBio = ui->infoTE->toPlainText();
    QString newPassword = ui->passwordLE->text();
    QString newPasswordRepeat = ui->password_repeatLE->text();

    ui->passwordErrorL->hide();
    ui->repaetErrorL->hide();

    bool changed = false;


    if(!newPassword.isEmpty()){
        if(newPassword.length() < 5){
            ui->passwordErrorL->setText("must be at least 5 characters");
            ui->passwordErrorL->show();
            return;
        }
        else {
            if(newPassword != newPasswordRepeat){
                ui->repaetErrorL->show();
                return;
            }
            else {
                user->setPassword(newPassword);
                changed = true;
            }
        }
    }

    if(!newName.isEmpty()){
        if(newName != user->getName()){
            user->setName(newName);
            changed = true;
        }
    }
    if(!newBio.isEmpty()){
        if(newBio != user->getBio()){
            user->setBio(newBio);
            changed = true;
        }
    }
    if(!newEmail.isEmpty()){
        if(newEmail != user->getEmail()){
            user->setEmail(newEmail);
        }
    }
    if(changedAvatar){
        user->setAvatar(newAvatar);
        changed = true;
    }

    if(changed){
        dataBase->editUserData(user->getUsername());

        this->close();
        this->parentWidget()->show();
        this->deleteLater();
    }
}


void Settings::on_DeleteAccountPB_clicked() {

    dataBase->deleteUser(user->getUsername());
    this->close();
    this->parentWidget()->parentWidget()->show();
    this->deleteLater();

}

void Settings::on_cancelPB_clicked()
{
    this->close();
    this->parentWidget()->show();
    this->deleteLater();
}

QPixmap Settings::makeCircleScalePixmap(QPixmap & pixmap, QSize & size) {

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


