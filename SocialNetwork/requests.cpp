#include "requests.h"
#include "ui_requests.h"

Requests::Requests(User* user,DataBase* dataBase, QWidget *parent)
    : QDialog(parent)
    ,dataBase(dataBase)
    ,user(user)
    , ui(new Ui::Requests)
{
    ui->setupUi(this);

    std::list<QString> *senders = dataBase->recived_requests(user->getUsername());

    for(auto &senderUsername :  *senders){
        User* senderAccount = dataBase->findUser(senderUsername);

        RequestWidget* widget = new RequestWidget(senderAccount,this);
        connect(widget,&RequestWidget::accepted,this,&Requests::accept);
        connect(widget,&RequestWidget::ignored,this,&Requests::reject);

        ui->verticalLayout->insertWidget(0,widget);
    }
}

Requests::~Requests()
{
    delete ui;
}

void Requests::accept(QString username, RequestWidget *widget)
{
    this->dataBase->makeFriend(username,this->user->getUsername());
    this->dataBase->cancelRequest(username,this->user->getUsername());
    delete widget;
}

void Requests::reject(QString username, RequestWidget *widget)
{
    this->dataBase->cancelRequest(username,this->user->getUsername());
    delete widget;
}

void Requests::on_pushButton_clicked()
{
    this->close();
    this->parentWidget()->show();
    this->deleteLater();
}

