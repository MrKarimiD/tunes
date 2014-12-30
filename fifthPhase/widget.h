#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QInputDialog>
#include "album_db.h"
#include "person_db.h"

using namespace std;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    bool isCharacter(const char Character);
    bool isNumber(const char Character);
    bool isValidEmailAddress(string EmailAddress);

private:
    QLineEdit *input_lineEdit;
    QPushButton *enter_button;
    QLabel *output_label;
    QTextEdit *output_text;
    album_db albums;
    person_db persons;
    int login_person_id;
    string login_person_name;
    string role;
    string purchase_status;

private slots:
    void on_button_clicked();
};

#endif // WIDGET_H
