#include "admin.h"
#include "ui_admin.h"
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->widget->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->widget_6->hide();
    ui->tableView_2->hide();

    model = new QStandardItemModel();
    ui->tableView->setModel(model);

    model2 = new QStandardItemModel();
    ui->tableView_2->setModel(model2);

    //加载用户名
    query.exec("select * from user where flag==1");
    if(query.next()){
        NAME = query.value(1).toString();
        ui->pushButton_4->setText(NAME);
    }

}

admin::~admin()
{
    delete ui;
}

//系统退出
void admin::on_pushButton_5_clicked()
{
    QString username = ui->pushButton_4->text();
    query.prepare("update user set flag=0 where username=:username");
    query.bindValue(":username",username);
    query.exec();
    this->close();
}
//菜单栏
void admin::on_listWidget_clicked(const QModelIndex &index)
{
    int num = ui->listWidget->currentRow();

    if(num!=0 && num!=1 && num!=6)
    {
        ui->frame_2->show();
        ui->widget->hide();
        ui->widget_4->hide();
        ui->widget_5->hide();
        ui->widget_6->hide();
        ui->frame_3->hide();
        ui->label->hide();
        ui->tableView_2->hide();
        model->clear();
        //显示脚注
        QString str1 =" >>";
        QString str2 = ui->listWidget->currentItem()->text();
        str2 = str2.remove(0, 10);
        QString str =str1+str2;
        ui->pushButton_3->setText(str);

        if(num>=2 && num<=5){
            if(num==2){
                ui->frame_3->show();

                query.exec("select * from admin");

                if(query.exec()){
                    model->clear();
                    model->setColumnCount(8);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"姓名");
                    model->setHeaderData(2,Qt::Horizontal,"年龄");
                    model->setHeaderData(3,Qt::Horizontal,"性别");
                    model->setHeaderData(4,Qt::Horizontal,"手机号");
                    model->setHeaderData(5,Qt::Horizontal,"身份证号");
                    model->setHeaderData(6,Qt::Horizontal,"工作职位");
                    model->setHeaderData(7,Qt::Horizontal,"月出勤数");
                    ui->tableView->setColumnWidth(0,102);
                    ui->tableView->setColumnWidth(4,200);
                    ui->tableView->setColumnWidth(5,240);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<8;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }
                }else{
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }
            if(num==3){
                ui->widget_4->show();

            }
            if(num==4){
                ui->frame_3->show();
                ui->widget_5->show();
            }
            if(num==5){
                ui->widget->show();
                //数据库查询
                query.exec("select * from leave where state='待批假'");
                if(query.exec())//查询成功
                {

                    model->clear();
                    model->setColumnCount(8);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"工号");
                    model->setHeaderData(2,Qt::Horizontal,"姓名");
                    model->setHeaderData(3,Qt::Horizontal,"请假原因");
                    model->setHeaderData(4,Qt::Horizontal,"离岗时间");
                    model->setHeaderData(5,Qt::Horizontal,"返岗时间");
                    model->setHeaderData(6,Qt::Horizontal,"联系电话");
                    model->setHeaderData(7,Qt::Horizontal,"请假状态");

                    ui->tableView->setColumnWidth(3,185);
                    ui->tableView->setColumnWidth(4,150);
                    ui->tableView->setColumnWidth(5,150);
                    ui->tableView->setColumnWidth(6,150);
                    ui->tableView->setColumnWidth(7,150);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<8;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }

                }else{
                    //查询失败，提示不存在
                    QMessageBox::information(this,tr("错误"),tr("信息导入出现问题，请稍后再试！"),tr("返回"));
                }
            }


        }
        if(num>=7 && num<=8){

            if(num==7){
                ui->widget_6->show();
            }
            if(num==8){
                ui->tableView_2->show();
                ui->tableView_2->horizontalHeader()->hide();


                model2->setItem(0,0,new QStandardItem(QString("操作系统")));
                model2->setItem(0,1,new QStandardItem(QString("Windows")));
                model2->setItem(1,0,new QStandardItem(QString("运行环境")));
                model2->setItem(1,1,new QStandardItem(QString("Qt 5.7")));
                model2->setItem(2,0,new QStandardItem(QString("系统类型")));
                model2->setItem(2,1,new QStandardItem(QString("32位操作系统")));
                model2->setItem(3,0,new QStandardItem(QString("设计版本")));
                model2->setItem(3,1,new QStandardItem(QString("v-2.0")));
                model2->setItem(4,0,new QStandardItem(QString("北京时间")));
                model2->setItem(4,1,new QStandardItem(QString("2020年6月10日 17:30:00")));
                model2->setItem(5,0,new QStandardItem(QString("数据库类型")));
                model2->setItem(5,1,new QStandardItem(QString("SQLite")));
                ui->tableView_2->setColumnWidth(0,150);
                ui->tableView_2->setColumnWidth(1,291);
                ui->tableView_2->setRowHeight(0,60);
                ui->tableView_2->setRowHeight(1,60);
                ui->tableView_2->setRowHeight(2,60);
                ui->tableView_2->setRowHeight(3,60);
                ui->tableView_2->setRowHeight(4,60);
                ui->tableView_2->setRowHeight(5,60);

            }
        }

    }
}
//查询按钮
void admin::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("搜索关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from admin where worker_name=:name");
        query.bindValue(":name",name);
        if(query.exec())//查询成功
        {
            model->clear();
            model->setColumnCount(8);
            model->setHeaderData(0,Qt::Horizontal,"序号");
            model->setHeaderData(1,Qt::Horizontal,"姓名");
            model->setHeaderData(2,Qt::Horizontal,"年龄");
            model->setHeaderData(3,Qt::Horizontal,"性别");
            model->setHeaderData(4,Qt::Horizontal,"手机号");
            model->setHeaderData(5,Qt::Horizontal,"身份证号");
            model->setHeaderData(6,Qt::Horizontal,"工作职位");
            model->setHeaderData(7,Qt::Horizontal,"月出勤数");
            ui->tableView->setColumnWidth(0,102);
            ui->tableView->setColumnWidth(4,200);
            ui->tableView->setColumnWidth(5,240);

            int i=0;
            while(query.next())
            {
                for(int j=0;j<8;j++){
                    model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                }
                i++;
            }
        }else{
            QMessageBox::information(this,tr("失败"),tr("该工作人员信息可能不存在！"),tr("返回"));
        }
    }
}
//准假按钮
void admin::on_pushButton_2_clicked()
{
    int id = ui->lineEdit_2->text().toInt();

    if(id==0){
        QMessageBox::information(this,tr("提示"),tr("序号不能为空！"),tr("返回"));
    }else{
        query.prepare("update leave set state='已准假' where id=:id");
        query.bindValue(":id",id);

        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("您已经成功批假！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("系统繁忙，请稍后再试！"),tr("返回"));
        }
    }
}
//添加工作人员
void admin::on_pushButton_23_clicked()
{
    QString name = ui->lineEdit_36->text();
    QString age = ui->lineEdit_38->text();
    QString sex = ui->lineEdit_33->text();
    QString tel = ui->lineEdit_34->text();
    QString ID = ui->lineEdit_35->text();
    QString job = ui->lineEdit_37->text();

    if(name==""||age==""||sex==""||tel==""||ID==""||job==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("insert into admin values(NULL,:name,:age,:sex,:tel,:ID,:job,0)");
        query.bindValue(":name",name);
        query.bindValue(":age",age);
        query.bindValue(":sex",sex);
        query.bindValue(":tel",tel);
        query.bindValue(":ID",ID);
        query.bindValue(":job",job);

        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("新的员工信息添加成功！"),tr("返回"));
            ui->lineEdit_36->setText("");
            ui->lineEdit_38->setText("");
            ui->lineEdit_33->setText("");
            ui->lineEdit_34->setText("");
            ui->lineEdit_35->setText("");
            ui->lineEdit_37->setText("");
        }else{
            QMessageBox::information(this,tr("失败"),tr("系统繁忙，请稍后再试！"),tr("返回"));
        }
    }
}
//根据工号查询员工信息
void admin::on_pushButton_25_clicked()
{
    //查询
    int id = ui->lineEdit_42->text().toInt();
    if(id==0){
        QMessageBox::information(this,tr("提示"),tr("工号不能为空！"),tr("返回"));
    }else{
        query.prepare("select * from admin where worker_num=:id");
        query.bindValue(":id",id);
        if(query.exec()){
            while(query.next()){
                QString name = query.value(1).toString();

                QString age = query.value(2).toString();

                QString sex = query.value(3).toString();

                QString tel = query.value(4).toString();

                QString ID = query.value(5).toString();

                QString job = query.value(6).toString();
                ui->lineEdit_45->setText(job);
                ui->lineEdit_44->setText(name);
                ui->lineEdit_39->setText(age);
                ui->lineEdit_40->setText(sex);
                ui->lineEdit_41->setText(tel);
                ui->lineEdit_43->setText(ID);
                //修改按钮使能
                ui->pushButton_24->setEnabled(true);
            }
        }else{
            QMessageBox::information(this,tr("失败"),tr("该工作人员不存在！"),tr("返回"));
        }

    }
}
//修改工作人员信息
void admin::on_pushButton_24_clicked()
{
    int id = ui->lineEdit_42->text().toInt();
    QString name = ui->lineEdit_44->text();
    QString age = ui->lineEdit_39->text();
    QString sex = ui->lineEdit_40->text();
    QString tel = ui->lineEdit_41->text();
    QString ID = ui->lineEdit_43->text();
    QString job = ui->lineEdit_45->text();
    if(name==""||age==""||sex==""||tel==""||ID==""||job==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update admin set worker_name=:name,worker_age=:age,worker_sex=:sex,worker_tel=:tel,worker_id=:ID,worker_job=:job where worker_num=:id");
        query.bindValue(":id",id);
        query.bindValue(":name",name);
        query.bindValue(":age",age);
        query.bindValue(":sex",sex);
        query.bindValue(":tel",tel);
        query.bindValue(":ID",ID);
        query.bindValue(":job",job);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("该工作人员信息修改成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("系统繁忙，请稍后再试！"),tr("返回"));
        }
    }
}
//系统初始化
void admin::on_pushButton_26_clicked()
{
    query.exec("delete from admin");
    query.exec("update sqlite_sequence set seq=0 where name='admin'");
    query.exec("delete from car");
    query.exec("update sqlite_sequence set seq=0 where name='car'");
    query.exec("delete from house");
    query.exec("update sqlite_sequence set seq=0 where name='house'");
    query.exec("delete from leave");
    query.exec("update sqlite_sequence set seq=0 where name='leave'");
    query.exec("delete from pay");
    query.exec("update sqlite_sequence set seq=0 where name='pay'");
    query.exec("delete from price");
    query.exec("update sqlite_sequence set seq=0 where name='price'");
    query.exec("delete from repair");
    query.exec("update sqlite_sequence set seq=0 where name='repair'");
    query.exec("delete from user");
    query.exec("update sqlite_sequence set seq=0 where name='user'");
    query.exec("delete from worker");
    query.exec("update sqlite_sequence set seq=0 where name='worker'");

    QMessageBox::information(this,tr("成功"),tr("系统数据已全部被清空！"),tr("返回"));
}
