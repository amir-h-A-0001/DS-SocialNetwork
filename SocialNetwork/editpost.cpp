#include "editpost.h"
#include "ui_editpost.h"

EditPost::EditPost(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditPost)
{
    ui->setupUi(this);
}

EditPost::~EditPost()
{
    delete ui;
}
