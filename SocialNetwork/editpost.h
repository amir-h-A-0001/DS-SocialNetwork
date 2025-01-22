#ifndef EDITPOST_H
#define EDITPOST_H

#include <QMainWindow>

namespace Ui {
class EditPost;
}

class EditPost : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditPost(QWidget *parent = nullptr);
    ~EditPost();

private:
    Ui::EditPost *ui;
};

#endif // EDITPOST_H
