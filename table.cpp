#include "table.h"
#include <QLineEdit>
#include <QPushButton>
int Table::getX() const{
    return x;
}
int Table::getY() const{
    return y;
}
int Table::getT() const{
    return t_val;
}
bool Table::isOK() const{
    return t;
}

Table::Table(QWidget *parent) : QWidget(parent),t(false),x(0),y(0),t_val(0){
    this->resize(200, 200);
    this->setWindowTitle("Set Canvas Size");
    QLineEdit *xInput = new QLineEdit(this);
    QLineEdit *yInput = new QLineEdit(this);
    QLineEdit *tInput = new QLineEdit(this);
    xInput->setPlaceholderText("Width (e.g., 40)");
    yInput->setPlaceholderText("Height (e.g., 30)");
    tInput->setPlaceholderText("Number of Mines");
    xInput->move(10, 10);
    yInput->move(10, 50);
    tInput->move(10, 90);
    QPushButton *okButton = new QPushButton("OK", this);
    okButton->move(10, 130);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose); 
    connect(okButton, &QPushButton::clicked, [this, xInput, yInput, tInput]() {
        bool xOk = false, yOk = false, tOk = false;
        x = xInput->text().toInt(&xOk);
        y = yInput->text().toInt(&yOk);
        t_val = tInput->text().toInt(&tOk);
        if (!xOk || !yOk || !tOk || x <= 0 || y <= 0 || t_val < 0 || t_val >= x * y-8) {
            qDebug() << "Invalid input. Please enter valid integers for all fields.";
            return;
        }
        t=true;
    });
}