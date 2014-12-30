#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QLineEdit *input_lineEdit;
    QPushButton *enter_button;


private slots:
    void on_button_clicked();
};

#endif // WIDGET_H
