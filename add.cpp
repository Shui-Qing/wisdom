#include "add.h"
#include "ui_add.h"

add::add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);

}

add::~add()
{
    delete ui;
}

void add::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString money = ui->lineEdit_2->text();

    if(name=="" || money==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }
    else{
        query.prepare("insert into price(type,money) values(:name,:money)");
        query.bindValue(":name",name);
        query.bindValue(":money",money);

        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("新的缴费项目添加成功！"),tr("返回"));
            this->close();
        }else{
            QMessageBox::information(this,tr("失败"),tr("添加失败，请稍后再试！"),tr("返回"));
        }
    }
}
