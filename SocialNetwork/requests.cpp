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
        User* senderAccout = dataBase->findUser(senderUsername);

        RequestWidget* widget = new RequestWidget(senderAccout);
        connect(widget,&RequestWidget::accepted,[this, &senderUsername, &widget]{
            this->dataBase->makeFriend(senderUsername,this->user->getUsername());
            // delete the request from database
            delete widget;
        });
        connect(widget,&RequestWidget::accepted,[this, &widget]{
            //delete the request from database
            delete widget;
        });

        ui->verticalLayout->insertWidget(0,widget);
    }
}

Requests::~Requests()
{
    delete ui;
}
