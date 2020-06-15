#ifndef MODIFY_H
#define MODIFY_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class modify;
}

class modify : public QWidget
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = 0);
    ~modify();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::modify *ui;
    QSqlQuery query;
};

#endif // MODIFY_H
