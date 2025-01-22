#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDialog>

namespace Ui {
class Requests;
}

class Requests : public QDialog
{
    Q_OBJECT

public:
    explicit Requests(QWidget *parent = nullptr);
    ~Requests();

private:
    Ui::Requests *ui;
};

#endif // REQUESTS_H
