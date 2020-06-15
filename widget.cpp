#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("wisdom.db");

    //打开数据库
    if(!db.open())
    {
        QMessageBox::warning(this,"错误:",db.lastError().text());
        return;
    }


//    admin *ad = new admin();
//    ad->show();
//    Form *form = new Form();
//    form->show();
//    owner *own = new owner();
//    own->show();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int root = ui->comboBox->currentIndex ();
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    QSqlQuery query;

    query.prepare("select * from user where username=:username and password=:password and root=:root");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":root",root);
    query.exec();
    if(query.next())
    {
        if(root==0){
            query.prepare("update user set flag=1 where username=:username");
            query.bindValue(":username",username);
            query.exec();
//            qDebug()<<"管理员登录：ad";
            this->close();
            admin *ad = new admin();
            ad->show();
        }
        if(root==1){
            query.prepare("update user set flag=1 where username=:username");
            query.bindValue(":username",username);
            query.exec();
//            qDebug()<<"工作人员登录：form";
            this->close();
            Form *form = new Form();
            form->show();
        }
        if(root==2){
            query.prepare("update user set flag=1 where username=:username");
            query.bindValue(":username",username);
            query.exec();
//            qDebug()<<"业主登录：own";
            this->close();
            owner *own = new owner();
            own->show();
        }
//        NAME = query.value(1).toString();
    }else{
        QMessageBox::information(this,tr("错误"),tr("账号或密码错误！"),tr("返回"));
    }

}
