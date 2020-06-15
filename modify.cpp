#include "modify.h"
#include "ui_modify.h"

modify::modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);

    ui->pushButton_2->setEnabled(false);

}

modify::~modify()
{
    delete ui;
}

void modify::on_pushButton_clicked()
{
    int id = ui->lineEdit->text().toInt();

    if(id==0){
        QMessageBox::information(this,tr("提示"),tr("序号不能为空！"),tr("返回"));
    }else{


    query.prepare("select * from price where id=:id");
    query.bindValue(":id",id);

    if(query.exec()){

        while(query.next()){
            QString type = query.value(1).toString();
            QString money = query.value(2).toString();
            ui->lineEdit_2->setText(type);
            ui->lineEdit_3->setText(money);
        }

        ui->pushButton_2->setEnabled(true);
    }else{
        QMessageBox::information(this,tr("失败"),tr("查询失败！"),tr("返回"));
    }

}
}

void modify::on_pushButton_2_clicked()
{
    int id = ui->lineEdit->text().toInt();
    QString type = ui->lineEdit_2->text();
    QString money = ui->lineEdit_3->text();

    if(id==0||type=="" ||money==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{

    query.prepare("update price set type=:type,money=:money where id=:id");
    query.bindValue(":type",type);
    query.bindValue(":money",money);
    query.bindValue(":id",id);

    if(query.exec()){
        QMessageBox::information(this,tr("成功"),tr("缴费项目修改成功！"),tr("返回"));
        this->close();
    }else{
        QMessageBox::information(this,tr("失败"),tr("修改失败，请稍后再试！"),tr("返回"));
    }
    }
}
