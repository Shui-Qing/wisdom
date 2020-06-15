#ifndef OWNER_H
#define OWNER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class owner;
}

class owner : public QWidget
{
    Q_OBJECT

public:
    explicit owner(QWidget *parent = 0);
    ~owner();
public:
    QString NAME=NULL;
    QStandardItemModel *model;
private slots:


    void on_pushButton_5_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_18_clicked();

    void on_pushButton_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_21_clicked();

private:
    Ui::owner *ui;
    QSqlQuery query;
};

#endif // OWNER_H
