#include "form.h"
#include "ui_form.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "widget.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    //所有tableview下的子窗口
    ui->tableView->setModel(model);
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->widget->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->widget_6->hide();
    ui->tabWidget->hide();

    //加载登陆者的用户名
    query.exec("select * from user where flag==1");
    if(query.next()){
        NAME = query.value(1).toString();
        ui->pushButton_4->setText(NAME);
    }
}

Form::~Form()
{
    delete ui;
}
//退出系统
void Form::on_pushButton_2_clicked()
{
    QString username = ui->pushButton_4->text();
    query.prepare("update user set flag=0 where username=:username");
    query.bindValue(":username",username);
    query.exec();
    this->close();
}

//菜单栏
void Form::on_listWidget_clicked(const QModelIndex &index)
{
    int num = ui->listWidget->currentRow();

    if(num!=0 && num!=1 && num!=5 && num!=8 && num!=12 && num!=16 && num!=20)
    {
        //关闭tableview中的一级子控件
        ui->label->close();//关闭欢迎label
        model->clear();     //清空数据表格
        ui->lineEdit->clear();
        ui->label_2->show();
        ui->frame_2->show();
        ui->widget->hide(); //关闭1号
        ui->tabWidget->hide();
        ui->widget_2->hide();//关闭5号
        ui->widget_3->hide();//关闭8号
        ui->widget_4->hide();//关闭12号
        ui->widget_5->hide();//关闭16号
        ui->widget_6->hide();//关闭20号

        ui->comboBox->hide();
        ui->comboBox_2->hide();
        ui->comboBox_3->hide();
        ui->comboBox_4->hide();
        ui->lineEdit->show();

        ui->pushButton_24->hide();
        ui->pushButton_25->hide();

        //显示脚注
        QString str1 =" >>";
        QString str2 = ui->listWidget->currentItem()->text();
        str2 = str2.remove(0, 10);
        QString str =str1+str2;
        ui->pushButton_3->setText(str);
        if(num>=2 && num<=4){
            //显示frame3
            ui->frame_3->show();
            //label文本
            ui->label_2->setText("姓名：");
            //显示一个，隐藏5个
            ui->pushButton->show();
            ui->pushButton_9->hide();
            ui->pushButton_10->hide();
            ui->pushButton_11->hide();
            ui->pushButton_12->hide();
            ui->pushButton_13->hide();
            //显示业主信息2
            if(num==2){

                query.exec("select * from worker");

                if(query.exec())//查询成功
                {
                    model->clear();
                    model->setColumnCount(6);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"姓名");
                    model->setHeaderData(2,Qt::Horizontal,"年龄");
                    model->setHeaderData(3,Qt::Horizontal,"性别");
                    model->setHeaderData(4,Qt::Horizontal,"手机号");
                    model->setHeaderData(5,Qt::Horizontal,"家庭住址");

                    ui->tableView->setColumnWidth(0,150);
                    ui->tableView->setColumnWidth(1,150);
                    ui->tableView->setColumnWidth(2,150);
                    ui->tableView->setColumnWidth(3,150);
                    ui->tableView->setColumnWidth(4,240);
                    ui->tableView->setColumnWidth(5,320);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<6;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }
                }else{
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }
            //修改业主信息3
            if(num==3){
                ui->widget->show();
                ui->label_3->show();
                ui->lineEdit_2->show();
                ui->pushButton_7->show();
                ui->pushButton_8->hide();
                ui->pushButton_8->setEnabled(false);
                ui->pushButton_5->show();
                ui->pushButton_5->setEnabled(true);
                ui->lineEdit_2->setText("");
                ui->lineEdit_3->setText("");
                ui->lineEdit_4->setText("");
                ui->lineEdit_5->setText("");
                ui->lineEdit_6->setText("");
                ui->lineEdit_7->setText("");
            }
            //添加业主信息4
            if(num==4){
                ui->widget->show();
                ui->label_3->hide();
                ui->lineEdit_2->hide();
                ui->pushButton_7->hide();

                ui->pushButton_5->hide();
                ui->pushButton_5->setEnabled(false);
                ui->pushButton_8->show();
                ui->pushButton_8->setEnabled(true);

                ui->lineEdit_2->setText("");
                ui->lineEdit_3->setText("");
                ui->lineEdit_4->setText("");
                ui->lineEdit_5->setText("");
                ui->lineEdit_6->setText("");
                ui->lineEdit_7->setText("");
            }
        }
        if(num>=6 && num<=7){

            //房屋查询6
            if(num==6){
                //显示frame3
                ui->frame_3->show();
                ui->comboBox_2->show();
                ui->lineEdit->hide();
                //label文本
                ui->label_2->setText("状态：");
                //显示一个，隐藏5个
                ui->pushButton->hide();
                ui->pushButton_9->show();
                ui->pushButton_10->hide();
                ui->pushButton_11->hide();
                ui->pushButton_12->hide();
                ui->pushButton_13->hide();

                query.exec("select * from house");

                if(query.exec())//查询成功
                {
                    model->clear();
                    model->setColumnCount(6);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"位置");
                    model->setHeaderData(2,Qt::Horizontal,"类型");
                    model->setHeaderData(3,Qt::Horizontal,"出租状态");
                    model->setHeaderData(4,Qt::Horizontal,"房东");
                    model->setHeaderData(5,Qt::Horizontal,"房东联系电话");

                    ui->tableView->setColumnWidth(0,150);
                    ui->tableView->setColumnWidth(1,150);
                    ui->tableView->setColumnWidth(2,150);
                    ui->tableView->setColumnWidth(3,150);
                    ui->tableView->setColumnWidth(4,240);
                    ui->tableView->setColumnWidth(5,320);

                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<6;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }
                }else{
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }

            //入住登记7
            if(num==7){
                ui->frame_3->hide();
                ui->widget_2->show();
            }
        }
        if(num>=9 && num<=11){
            ui->lineEdit->hide();
            //显示frame3
            ui->frame_3->show();
            //label文本
            ui->label_2->setText("类型：");
            //显示一个，隐藏5个
            ui->pushButton->hide();
            ui->pushButton_9->hide();
            ui->pushButton_10->show();
            ui->pushButton_11->hide();
            ui->pushButton_12->hide();
            ui->pushButton_13->hide();
            ui->comboBox_3->show();
            ui->widget_3->show();
            //车位信息维护9
            if(num==9){
                ui->widget_3->hide();
                query.prepare("select * from car");
                query.exec();
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
                    ui->tableView->setColumnWidth(6,240);

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
            //车位申请10
            if(num==10){
                ui->frame_3->hide();
                ui->pushButton_18->show();
                ui->pushButton_19->hide();
            }
            //车位出租11
            if(num==11){
                ui->frame_3->hide();
                ui->pushButton_18->hide();
                ui->pushButton_19->show();
            }
        }
        if(num>=13 && num<=15){
            //显示frame3
            ui->frame_3->hide();
            //label文本
            ui->label_2->setText("姓名：");
            //显示一个，隐藏5个
            ui->pushButton->hide();
            ui->pushButton_9->hide();
            ui->pushButton_10->hide();
            ui->pushButton_11->show();
            ui->pushButton_12->hide();
            ui->pushButton_13->hide();


            //缴费价格维护13
            if(num==13){
                ui->frame_3->show();
                ui->label_2->hide();
                ui->lineEdit->hide();
                ui->pushButton_11->hide();
                ui->pushButton_24->show();
                ui->pushButton_25->show();

                query.exec("select * from price");

                if(query.exec())//查询成功
                {
                    model->clear();
                    model->setColumnCount(3);
                    model->setHeaderData(0,Qt::Horizontal,"序号");
                    model->setHeaderData(1,Qt::Horizontal,"缴费项目");
                    model->setHeaderData(2,Qt::Horizontal,"价格");


                    ui->tableView->setColumnWidth(0,350);
                    ui->tableView->setColumnWidth(1,460);
                    ui->tableView->setColumnWidth(2,350);


                    int i=0;
                    while(query.next())
                    {
                        for(int j=0;j<3;j++){
                            model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                        }
                        i++;
                    }
                }else{
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }
            //线下收费14
            if(num==14){
                ui->widget_4->show();
                ui->pushButton_22->setEnabled(false);
            }
            //缴费查询15
            if(num==15){
                ui->frame_3->show();

                query.exec("select * from pay");

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
        }
        if(num>=17 && num<=19){
            ui->lineEdit->hide();
            //显示frame3
            ui->frame_3->show();
            ui->comboBox_4->show();
            //label文本
            ui->label_2->setText("状态：");
            //显示一个，隐藏5个
            ui->pushButton->hide();
            ui->pushButton_9->hide();
            ui->pushButton_10->hide();
            ui->pushButton_11->hide();
            ui->pushButton_12->show();
            ui->pushButton_13->hide();

            ui->widget_5->show();
            //业主报修17
            if(num==17){
                //隐藏
                ui->frame_3->hide();
                ui->label_34->hide();
                ui->lineEdit_31->hide();
                ui->pushButton_21->hide();
                //显示
                ui->label_29->show();
                ui->label_30->show();
                ui->label_31->show();
                ui->label_32->show();
                ui->label_33->show();
                ui->lineEdit_26->show();
                ui->lineEdit_27->show();
                ui->lineEdit_28->show();
                ui->lineEdit_29->show();
                ui->lineEdit_30->show();
                ui->pushButton_20->show();
            }
            //报修信息18
            if(num==18){

                ui->widget_5->hide();

                query.exec("select * from repair");

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
                    QMessageBox::information(this,tr("错误"),tr("信息查询故障！"),tr("返回"));
                }
            }
            //维修进度19
            if(num==19){
                //隐藏
                ui->label_29->hide();
                ui->label_30->hide();
                ui->label_31->hide();
                ui->label_32->hide();
                ui->label_33->hide();
                ui->lineEdit_26->hide();
                ui->lineEdit_27->hide();
                ui->lineEdit_28->hide();
                ui->lineEdit_29->hide();
                ui->lineEdit_30->hide();
                ui->pushButton_20->hide();
                //显示
                ui->label_34->show();
                ui->lineEdit_31->show();
                ui->pushButton_21->show();
            }
        }
        if(num>=21 && num<=22){

            //显示一个，隐藏5个
            ui->pushButton->hide();
            ui->pushButton_9->hide();
            ui->pushButton_10->hide();
            ui->pushButton_11->hide();
            ui->pushButton_12->hide();
            ui->pushButton_13->show();


            //请销假21
            if(num==21){
                //显示frame3
                ui->frame_3->show();
                ui->comboBox->show();
                //label文本
                ui->label_2->setText("假状：");
                ui->tabWidget->show();
                ui->widget_6->hide();
                ui->lineEdit->hide();
            }
            //出勤登记22
            if(num==22){
                //显示操作窗口
                ui->widget_6->show();
                //显示控件
                ui->label_9->show();
                ui->pushButton_14->show();
                //隐藏控件
                ui->label_10->hide();
                ui->tabWidget->hide();
                ui->frame_3->hide();
            }
        }
    }
}
//一搜索功能
void Form::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from worker where name=:name");
        query.bindValue(":name",name);
        query.exec();
        if(query.exec())//查询成功
        {

            model->clear();
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal,"序号");
            model->setHeaderData(1,Qt::Horizontal,"姓名");
            model->setHeaderData(2,Qt::Horizontal,"年龄");
            model->setHeaderData(3,Qt::Horizontal,"性别");
            model->setHeaderData(4,Qt::Horizontal,"手机号");
            model->setHeaderData(5,Qt::Horizontal,"家庭住址");

            ui->tableView->setColumnWidth(0,150);
            ui->tableView->setColumnWidth(1,150);
            ui->tableView->setColumnWidth(2,150);
            ui->tableView->setColumnWidth(3,150);
            ui->tableView->setColumnWidth(4,240);
            ui->tableView->setColumnWidth(5,320);

            int i=0;
            while(query.next())
            {
                for(int j=0;j<6;j++){
                    model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                }
                i++;
            }

        }else{
            //查询失败，提示不存在
            QMessageBox::information(this,tr("错误"),tr("该业主信息不存在！"),tr("返回"));
        }
    }
}
//“清空”控件的功能
void Form::on_pushButton_6_clicked()
{
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
}
//“修改”控件的功能
void Form::on_pushButton_5_clicked()
{
    //id、姓名、年龄、性别、电话、地址
    int id = ui->lineEdit_2->text().toInt();
    QString name = ui->lineEdit_3->text();
    int age = ui->lineEdit_4->text().toInt();
    QString sex = ui->lineEdit_5->text();
    QString tel_num = ui->lineEdit_6->text();
    QString addr = ui->lineEdit_7->text();

    if(id==0||name==""||age==0||sex==""||tel_num==""||addr==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update worker set name=:name,age=:age,sex=:sex,tel_num=:tel_num,addr=:addr where id=:id");
        query.bindValue(":id",id);
        query.bindValue(":name",name);
        query.bindValue(":age", age);
        query.bindValue(":sex", sex);
        query.bindValue(":tel_num", tel_num);
        query.bindValue(":addr", addr);
        query.exec();
        if(!query.exec())
        {
            QMessageBox::information(this,tr("错误"),tr("请输入序号载入信息！"),tr("返回"));
        }
        else
        {
            QMessageBox::information(this,tr("成功"),tr("数据提交成功！"),tr("返回"));
        }
    }
}
//“载入”控件的功能
void Form::on_pushButton_7_clicked()
{
    int id = ui->lineEdit_2->text().toInt();
    //数据库查询
    if(id==0){
        QMessageBox::information(this,tr("提示"),tr("序号不能为空！"),tr("返回"));
    }else{
        query.prepare("select * from worker where id=:id");
        query.bindValue(":id",id);
        query.exec();
        if(query.next())//查询成功
        {
            ui->lineEdit_3->setText(query.value(1).toString());
            //        qDebug()<<query.value(1).toString();
            ui->lineEdit_4->setText(query.value(2).toString());
            ui->lineEdit_5->setText(query.value(3).toString());
            ui->lineEdit_6->setText(query.value(4).toString());
            ui->lineEdit_7->setText(query.value(5).toString());


        }else{
            //查询失败，提示不存在
            QMessageBox::information(this,tr("错误"),tr("该数据不存在！"),tr("返回"));
        }
    }
}
//“添加”控件的功能
void Form::on_pushButton_8_clicked()
{
    QString name = ui->lineEdit_3->text();
    int age = ui->lineEdit_4->text().toInt();
    QString sex = ui->lineEdit_5->text();
    QString tel_num = ui->lineEdit_6->text();
    QString addr = ui->lineEdit_7->text();

    if(name==""||age==0||sex==""||tel_num==""||addr==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("insert into worker(id,name,age,sex,tel_num,addr) values(null,:name,:age,:sex,:tel_num,:addr)");

        query.bindValue(":name",name);
        query.bindValue(":age", age);
        query.bindValue(":sex", sex);
        query.bindValue(":tel_num", tel_num);
        query.bindValue(":addr", addr);
        //    query.exec();
        if(!query.exec())
        {
            QMessageBox::information(this,tr("错误"),tr("业主信息添加失败！"),tr("返回"));
        }
        else
        {
            QMessageBox::information(this,tr("成功"),tr("业主信息添加成功！"),tr("返回"));
        }
    }
}
//二搜索功能
void Form::on_pushButton_9_clicked()
{
    QString name = ui->comboBox_2->currentText();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from house where state=:name");
        query.bindValue(":name",name);
        //    query.exec();
        if(query.exec())//查询成功
        {

            model->clear();
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal,"序号");
            model->setHeaderData(1,Qt::Horizontal,"位置");
            model->setHeaderData(2,Qt::Horizontal,"类型");
            model->setHeaderData(3,Qt::Horizontal,"出租状态");
            model->setHeaderData(4,Qt::Horizontal,"房东");
            model->setHeaderData(5,Qt::Horizontal,"房东联系电话");

            ui->tableView->setColumnWidth(0,150);
            ui->tableView->setColumnWidth(1,150);
            ui->tableView->setColumnWidth(2,150);
            ui->tableView->setColumnWidth(3,150);
            ui->tableView->setColumnWidth(4,240);
            ui->tableView->setColumnWidth(5,320);

            int i=0;
            while(query.next())
            {
                for(int j=0;j<6;j++){
                    model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                }
                i++;
            }

        }else{
            //查询失败，提示不存在
            QMessageBox::information(this,tr("错误"),tr("该业主信息不存在！"),tr("返回"));
        }
    }
}
//登记button功能
void Form::on_pushButton_17_clicked()
{
    int id = ui->lineEdit_19->text().toInt();
    QString name = ui->lineEdit_15->text();
    QString tel = ui->lineEdit_16->text();
    QString time = ui->lineEdit_17->text();
    QString limit = ui->lineEdit_18->text();

    if(id==0||name==""||tel==""||time==""||limit==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update house set tenant=:name,tenant_tel=:tel,time=:time,time_limit=:limit where id=:id");
        query.bindValue(":name",name);
        query.bindValue(":tel",tel);
        query.bindValue(":time",time);
        query.bindValue(":limit",limit);
        query.bindValue(":id",id);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("登记成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("登记失败！"),tr("返回"));
        }
    }
}
//三搜索功能
void Form::on_pushButton_10_clicked()
{
    QString name = ui->comboBox_3->currentText();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from car where car_state=:name");
        query.bindValue(":name",name);
        query.exec();
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
            ui->tableView->setColumnWidth(6,240);

            int i=0;
            while(query.next())
            {
                for(int j=0;j<7;j++){
                    model->setItem(i,j,new QStandardItem(query.value(j).toString()));
                }
                i++;
            }

        }else{
            //查询失败，提示不存在
            QMessageBox::information(this,tr("错误"),tr("该业主信息不存在！"),tr("返回"));
        }
    }
}
//申请功能
void Form::on_pushButton_18_clicked()
{
    int id = ui->lineEdit_24->text().toInt();
    QString name = ui->lineEdit_20->text();
    QString reg = ui->lineEdit_21->text();
    QString tel = ui->lineEdit_22->text();
    QString ID = ui->lineEdit_23->text();
    QString addr = ui->lineEdit_25->text();

    if(id==0||name==""||reg==""||tel==""||ID==""||addr==""){
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
//出租车位功能
void Form::on_pushButton_19_clicked()
{
    int id = ui->lineEdit_24->text().toInt();
    QString name = ui->lineEdit_20->text();
    QString reg = ui->lineEdit_21->text();
    QString tel = ui->lineEdit_22->text();
    QString ID = ui->lineEdit_23->text();
    QString addr = ui->lineEdit_25->text();
    if(id==0||name==""||reg==""||tel==""||ID==""||addr==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update car set car_owner=:name,car_state='已出租',car_regnum=:reg,tel_num=:tel,ID=:ID,addr=:addr where car_num=:id");
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
//四搜索功能
void Form::on_pushButton_11_clicked()
{
    QString name = ui->lineEdit->text();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from pay where name=:name");
        query.bindValue(":name",name);
        //    query.exec();
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
            QMessageBox::information(this,tr("错误"),tr("该业主信息不存在！"),tr("返回"));
        }
    }
}
//添加缴费项目
void Form::on_pushButton_24_clicked()
{
    add *Add = new add();
    Add->show();
}
//修改缴费项目
void Form::on_pushButton_25_clicked()
{
    modify *Modify = new modify();
    Modify->show();
}
//应缴费用
void Form::on_pushButton_23_clicked()
{
    QString type = ui->comboBox_5->currentText();

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
//线下缴费
void Form::on_pushButton_22_clicked()
{
    QString name = ui->lineEdit_36->text();
    QString type = ui->comboBox_5->currentText();;
    QString money = ui->lineEdit_33->text();
    QString tel = ui->lineEdit_34->text();
    QString addr = ui->lineEdit_35->text();
    QString time = ui->lineEdit_37->text();

    if(name==""||money==""||tel==""||addr==""||time==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("insert into pay(name,type,money,tel_num,addr,time,state,method) values(:name,:type,:money,:tel,:addr,:time,'已支付','线下')");
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
//五搜索功能
void Form::on_pushButton_12_clicked()
{
    QString name = ui->comboBox_4->currentText();
    if(name==""){
        QMessageBox::information(this,tr("提示"),tr("关键字不能为空！"),tr("返回"));
    }else{
        //数据库查询
        query.prepare("select * from repair where state=:name");
        query.bindValue(":name",name);

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
}
//业主报修
void Form::on_pushButton_20_clicked()
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
//保修进度
void Form::on_pushButton_21_clicked()
{
    int id = ui->lineEdit_31->text().toInt();
    if(id==0){
        QMessageBox::information(this,tr("提示"),tr("序号不能为空！"),tr("返回"));
    }else{
        query.prepare("update repair set state='已完成' where id=:id");
        query.bindValue(":id",id);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("维修进度修改成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("成功"),tr("维修进度修改失败！"),tr("返回"));
        }
    }

}
//六搜索功能
void Form::on_pushButton_13_clicked()
{
    QString name = ui->pushButton_4->text();
    QString state = ui->comboBox->currentText();
    //数据库查询
    query.prepare("select * from leave where worker_name=:name and state=:state");
    query.bindValue(":name",name);
    query.bindValue(":state",state);
    query.exec();
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
        QMessageBox::information(this,tr("错误"),tr("该状态信息不存在！"),tr("返回"));
    }
}
//出勤登记button
void Form::on_pushButton_14_clicked()
{
    //通过登陆者的id，修改数据库中出勤数+1
    QString username = ui->pushButton_4->text();
    query.prepare("update admin set worker_attendance=worker_attendance+1 where worker_name=:username");
    query.bindValue(":username",username);
    //    query.exec();
    //成功//显示出勤数//登记成功//button使能false
    if(query.exec()){
        ui->label_10->show();
        ui->label_9->setText("今日您已登记！");
        ui->pushButton_14->setEnabled(false);
    }else{//失败提示，登记失败，请稍后再试！
        QMessageBox::information(this,tr("错误"),tr("登记失败，请稍后再试！"),tr("返回"));
    }

    query.prepare("select * from admin where worker_name=:username");
    query.bindValue(":username",username);
    query.exec();
    while(query.next()){
        QString str1=ui->label_10->text();
        QString str2 = query.value(7).toString();
        QString str=str1+str2;
        ui->label_10->setText(str);
    }
}
//请假（insert）
void Form::on_pushButton_15_clicked()
{
    QString worker_num = ui->lineEdit_9->text();
    QString name = ui->lineEdit_10->text();
    QString reason = ui->lineEdit_11->text();
    QString leavetime = ui->lineEdit_12->text();
    QString returntime = ui->lineEdit_13->text();
    QString tel_num = ui->lineEdit_14->text();
    if(worker_num==""||name==""||reason==""||leavetime==""||returntime==""||tel_num==""){
        QMessageBox::information(this,tr("提醒"),tr("先把假条填完整吧！"),tr("返回"));
    }else{
        query.prepare("insert into leave(worker_num,worker_name,reason,leavetime,returntime,tel_num) values(:worker_num,:worker_name,:reason,:leavetime,:returntime,:tel_num)");
        query.bindValue(":worker_num",worker_num);
        query.bindValue(":worker_name",name);
        query.bindValue(":reason",reason);
        query.bindValue(":leavetime",leavetime);
        query.bindValue(":returntime",returntime);
        query.bindValue(":tel_num",tel_num);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("请假信息提交成功！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("请假信息提交失败！"),tr("返回"));
        }
    }

}
//销假（update）
void Form::on_pushButton_16_clicked()
{
    int id = ui->lineEdit_8->text().toInt();
    QString name = ui->pushButton_4->text();
    if(id==0||name==""){
        QMessageBox::information(this,tr("提示"),tr("内容不能为空！"),tr("返回"));
    }else{
        query.prepare("update leave set state='已销假' where id=:id and worker_name=:name");
        query.bindValue(":id",id);
        query.bindValue(":name",name);
        if(query.exec()){
            QMessageBox::information(this,tr("成功"),tr("该假信息已销！"),tr("返回"));
        }else{
            QMessageBox::information(this,tr("失败"),tr("销假失败！"),tr("返回"));
        }
    }
}

