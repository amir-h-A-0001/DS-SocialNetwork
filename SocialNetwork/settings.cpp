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
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_avatarPB_clicked()
{

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

    if(changed){
        dataBase->editUserData(user->getUsername());
    }
}

