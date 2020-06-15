#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QSqlQuery>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItemModel>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();
public:
    QString NAME=NULL;
    QStandardItemModel *model;
    QStandardItemModel *model2;

private slots:

    void on_pushButton_5_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_26_clicked();

private:
    Ui::admin *ui;
    QSqlQuery query;
};

#endif // ADMIN_H
