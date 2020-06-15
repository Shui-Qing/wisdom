#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class add;
}

class add : public QWidget
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = 0);
    ~add();

private slots:
    void on_pushButton_clicked();

private:
    Ui::add *ui;
    QSqlQuery query;
};

#endif // ADD_H
