#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    input_lineEdit = new QLineEdit(this);
    input_lineEdit->setPlaceholderText("Enter Your Command Here...");
    input_lineEdit->move(25,20);
    input_lineEdit->setFixedHeight(30);
    input_lineEdit->setFixedWidth(450);

    enter_button = new QPushButton(this);
    enter_button->setText("Enter");
    enter_button->setFixedHeight(50);
    enter_button->move(200,60);
    connect(enter_button,SIGNAL(clicked()),this,SLOT(on_button_clicked()));
}

Widget::~Widget()
{

}

void Widget::on_button_clicked()
{

}
