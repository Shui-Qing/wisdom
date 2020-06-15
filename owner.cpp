#include "owner.h"
#include "ui_owner.h"
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

owner::owner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::owner)
{
    ui->setupUi(this);
    model = new QStandardItemModel;
    ui->tableView->setModel(model);
    //隐藏控件
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->widget_3->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->widget->hide();

    //加载用户名
    query.exec("select * from user where flag==1");
    if(query.next()){
        NAME = query.value(1).toString();
        ui->pushButton_4->setText(NAME);
    }
}

owner::~owner()
{
    delete ui;
}

void owner::on_listWidget_clicked(const QModelIndex &index)
{
    int num = ui->listWidget->currentRow();

    if(num!=0 && num!=1 && num!=4 && num!=7)
    {
        //隐藏控件
        ui->widget_5->hide();
        ui->widget_4->hide();
        ui->widget_3->hide();
        ui->widget->hide();
        ui->label->hide();
        model->clear();
        //显示控件
        ui->frame_2->show();
        ui->frame_3->show();

        //显示脚注
        QString str1 =" >>";
        QString str2 = ui->listWidget->currentItem()->text();
        str2 = str2.remove(0, 10);
        QString str =str1+str2;
        ui->pushButton_3->setText(str);

        if(num>=2 && num<=3){
            ui->frame_3->hide();
            if(num==2){
                query.prepare("select * from car where car_owner=:name");
                query.bindValue(":name",NAME);
                if(query.exec())//查询成功
                {
                    model->clear();
                    model->setColumnCount(7);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"车位状态");
                    model->setHeaderData(2,Qt::Horizontal,"申请人");
                    model->setHeaderData(3,Qt::Horizontal,"注册车牌号");
                    model->setHeaderData(4,Qt::Horizontal,"手机号");
                    model->setHeaderData(5,Qt::Horizontal,"注册ID");
                    model->setHeaderData(6,Qt::Horizontal,"家庭住址");

                    ui->tableView->setColumnWidth(0,100);
                    ui->tableView->setColumnWidth(1,120);
                    ui->tableView->setColumnWidth(2,120);
                    ui->tableView->setColumnWidth(3,150);
                    ui->tableView->setColumnWidth(4,200);
                    ui->tableView->setColumnWidth(5,230);
                    ui->tableView->setColumnWidth(6,245);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<7;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }

                }else{
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }
            if(num==3){
                ui->widget_3->show();

            }

        }

        if(num>=5 && num<=6){

            ui->frame_3->hide();
            if(num==5){
                ui->frame_3->show();
                ui->label_2->setText("类型：");
                ui->comboBox_5->show();
                ui->lineEdit->hide();
                ui->pushButton->show();
                ui->comboBox_4->hide();
                ui->pushButton_2->hide();

                query.prepare("select * from pay where name=:name");
                query.bindValue(":name",NAME);

                if(query.exec())//查询成功
                {

                    model->clear();
                    model->setColumnCount(9);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"姓名");
                    model->setHeaderData(2,Qt::Horizontal,"缴费类型");
                    model->setHeaderData(3,Qt::Horizontal,"缴费金额");
                    model->setHeaderData(4,Qt::Horizontal,"联系电话");
                    model->setHeaderData(5,Qt::Horizontal,"家庭住址");
                    model->setHeaderData(6,Qt::Horizontal,"支付时间");
                    model->setHeaderData(7,Qt::Horizontal,"支付状态");
                    model->setHeaderData(8,Qt::Horizontal,"支付方式");

                    ui->tableView->setColumnWidth(0,100);
                    ui->tableView->setColumnWidth(1,100);
                    ui->tableView->setColumnWidth(2,100);
                    ui->tableView->setColumnWidth(3,120);
                    ui->tableView->setColumnWidth(4,140);
                    ui->tableView->setColumnWidth(5,150);
                    ui->tableView->setColumnWidth(6,150);
                    ui->tableView->setColumnWidth(7,150);
                    ui->tableView->setColumnWidth(8,150);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<9;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }

                }else{
                    //查询失败，提示不存在
                    QMessageBox::information(this,tr("错误"),tr("系统信息出错！"),tr("返回"));
                }
            }
            if(num==6){
                ui->widget_4->show();
                ui->pushButton_22->setEnabled(false);
            }

        }

        if(num>=8 && num<=10){
            ui->frame_3->hide();
            if(num==8){
                ui->widget_5->show();
            }
            if(num==9){
                ui->frame_3->show();
                ui->label_2->setText("进度：");
                ui->comboBox_4->show();
                ui->pushButton_2->show();

                ui->comboBox_5->hide();
                ui->pushButton->hide();

                //数据库查询
                query.prepare("select * from repair where name=:name");
                query.bindValue(":name",NAME);
                if(query.exec())//查询成功
                {
                    model->clear();
                    model->setColumnCount(7);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"姓名");
                    model->setHeaderData(2,Qt::Horizontal,"维修问题");
                    model->setHeaderData(3,Qt::Horizontal,"联系电话");
                    model->setHeaderData(4,Qt::Horizontal,"家庭住址");
                    model->setHeaderData(5,Qt::Horizontal,"报修时间");
                    model->setHeaderData(6,Qt::Horizontal,"修理状态");

                    ui->tableView->setColumnWidth(0,100);
                    ui->tableView->setColumnWidth(1,100);
                    ui->tableView->setColumnWidth(2,150);
                    ui->tableView->setColumnWidth(3,150);
                    ui->tableView->setColumnWidth(4,240);
                    ui->tableView->setColumnWidth(5,200);
                    ui->tableView->setColumnWidth(6,220);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<7;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }
                }else{
                    QMessageBox::information(this,tr("失败"),tr("未找到该类型信息！"),tr("返回"));
                }
            }
            if(num==10){
                ui->widget->show();

            }

        }
    }
}

//退出按钮
void owner::on_pushButton_5_clicked()
{
    QString username = ui->pushButton_4->text();
    query.prepare("update user set flag=0 where username=:username");
    query.bindValue(":username",username);
    query.exec();
    this->close();
}

//车位申请按钮
void owner::on_pushButton_18_clicked()
{
    int id = ui->lineEdit_24->text().toInt();
    QString name = ui->lineEdit_20->text();
    QString reg = ui->lineEdit_21->text();
    QString tel = ui->lineEdit_22->text();
    QString ID = ui->lineEdit_23->text();
    QString addr = ui->lineEdit_25->text();

    if(id==0||name=="" || reg=="" || tel=="" || ID=="" || addr==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update car set car_owner=:name,car_state='已出售',car_regnum=:reg,tel_num=:tel,ID=:ID,addr=:addr where car_num=:id");
        query.bindValue(":id",id);
        query.bindValue(":name",name);
        query.bindValue(":reg",reg);
        query.bindValue(":tel",tel);
        query.bindValue(":ID",ID);
        query.bindValue(":addr",addr);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("车位申请成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("车位申请失败！"),tr("返回"));
        }
    }
}
//缴费类型查询按钮
void owner::on_pushButton_clicked()
{
    QString type = ui->comboBox_5->currentText();
    query.prepare("select * from pay where name=:name and type=:type");
    query.bindValue(":name",NAME);
    query.bindValue(":type",type);
    if(query.exec())//查询成功
    {

        model->clear();
        model->setColumnCount(9);
        model->setHeaderData(0,Qt::Horizontal,"序号");
        model->setHeaderData(1,Qt::Horizontal,"姓名");
        model->setHeaderData(2,Qt::Horizontal,"缴费类型");
        model->setHeaderData(3,Qt::Horizontal,"缴费金额");
        model->setHeaderData(4,Qt::Horizontal,"联系电话");
        model->setHeaderData(5,Qt::Horizontal,"家庭住址");
        model->setHeaderData(6,Qt::Horizontal,"支付时间");
        model->setHeaderData(7,Qt::Horizontal,"支付状态");
        model->setHeaderData(8,Qt::Horizontal,"支付方式");

        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,100);
        ui->tableView->setColumnWidth(2,100);
        ui->tableView->setColumnWidth(3,120);
        ui->tableView->setColumnWidth(4,140);
        ui->tableView->setColumnWidth(5,150);
        ui->tableView->setColumnWidth(6,150);
        ui->tableView->setColumnWidth(7,150);
        ui->tableView->setColumnWidth(8,150);

        int i=0;
        while(query.next())
        {
            for(int j=0;j<9;j++){
                model->setItem(i,j,new QStandardItem(query.value(j).toString()));
            }
            i++;
        }

    }else{
        //查询失败，提示不存在
        QMessageBox::information(this,tr("错误"),tr("该类型缴费信息不存在！"),tr("返回"));
    }
}
//应缴费按钮
void owner::on_pushButton_23_clicked()
{
    QString type = ui->comboBox_6->currentText();

    query.prepare("select * from price where type=:type");
    query.bindValue(":type",type);
    if(query.exec()){
        while(query.next()){
            QString money = query.value(2).toString();
            ui->lineEdit_33->setText(money);
        }
        ui->pushButton_22->setEnabled(true);
    }
}
//缴费按钮
void owner::on_pushButton_22_clicked()
{
    QString name = ui->lineEdit_36->text();
    QString type = ui->comboBox_6->currentText();;
    QString money = ui->lineEdit_33->text();
    QString tel = ui->lineEdit_34->text();
    QString addr = ui->lineEdit_35->text();
    QString time = ui->lineEdit_37->text();

    if(name==""||money==""||tel==""||addr==""||time==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("insert into pay(name,type,money,tel_num,addr,time,state) values(:name,:type,:money,:tel,:addr,:time,'已支付')");
        query.bindValue(":name",name);
        query.bindValue(":type",type);
        query.bindValue(":money",money);
        query.bindValue(":tel",tel);
        query.bindValue(":addr",addr);
        query.bindValue(":time",time);

        if(query.exec()){
            ui->lineEdit_36->setText("");
            ui->lineEdit_33->setText("");
            ui->lineEdit_34->setText("");
            ui->lineEdit_35->setText("");
            ui->lineEdit_37->setText("");
            QMessageBox::information(this,tr("成功"),tr("缴费成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("缴费失败！"),tr("返回"));
        }
    }
}
//报修按钮
void owner::on_pushButton_20_clicked()
{
    QString name = ui->lineEdit_30->text();
    QString type = ui->lineEdit_26->text();
    QString tel = ui->lineEdit_27->text();
    QString addr = ui->lineEdit_28->text();
    QString time = ui->lineEdit_29->text();

    if(name==""||type==""||tel==""||addr==""||time==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("insert into repair(name,type,tel_num,addr,time) values(:name,:type,:tel,:addr,:time)");
        query.bindValue(":name",name);
        query.bindValue(":tel",tel);
        query.bindValue(":time",time);
        query.bindValue(":addr",addr);
        query.bindValue(":type",type);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("登记成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("登记失败！"),tr("返回"));
        }
    }
}
//维修进度信息查询
void owner::on_pushButton_2_clicked()
{
    QString state = ui->comboBox_4->currentText();
    //数据库查询
    query.prepare("select * from repair where state=:state and name=:name");
    query.bindValue(":state",state);
    query.bindValue(":name",NAME);


    if(query.exec())//查询成功
    {
        model->clear();
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal,"序号");
        model->setHeaderData(1,Qt::Horizontal,"姓名");
        model->setHeaderData(2,Qt::Horizontal,"维修问题");
        model->setHeaderData(3,Qt::Horizontal,"联系电话");
        model->setHeaderData(4,Qt::Horizontal,"家庭住址");
        model->setHeaderData(5,Qt::Horizontal,"报修时间");
        model->setHeaderData(6,Qt::Horizontal,"修理状态");

        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,100);
        ui->tableView->setColumnWidth(2,150);
        ui->tableView->setColumnWidth(3,150);
        ui->tableView->setColumnWidth(4,240);
        ui->tableView->setColumnWidth(5,200);
        ui->tableView->setColumnWidth(6,220);

        int i=0;
        while(query.next())
        {
            for(int j=0;j<7;j++){
                model->setItem(i,j,new QStandardItem(query.value(j).toString()));
            }
            i++;
        }
    }else{
        QMessageBox::information(this,tr("失败"),tr("未找到该类型信息！"),tr("返回"));
    }
}
//评论功能
void owner::on_pushButton_21_clicked()
{
    int id = ui->lineEdit_31->text().toInt();
    QString comment = ui->textEdit->toPlainText();

    if(id==0||comment==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update repair set comment=:comment where id=:id");
        query.bindValue(":id",id);
        query.bindValue(":comment",comment);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("评论成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("评论失败！"),tr("返回"));
        }
    }
}
