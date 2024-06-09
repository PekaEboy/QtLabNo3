#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "list.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lwStudents->addItem("Иван Иванович Иванов");
    pen.name = "Иван Иванович Иванов";
    ui->lwScore->addItem("50 60 70");
    pen.score[0] = 50;
    pen.score[1] = 60;
    pen.score[2] = 70;
    lst.push_back(pen);
    ui->lwStudents->addItem("Петр Петрович Петров");
    ui->lwScore->addItem("80 90 70");
    pen.score[0] = 80;
    pen.score[1] = 90;
    pen.score[2] = 70;
    pen.name = "Петр Петрович Петров";
    lst.push_back(pen);
    ui->lwStudents->addItem("Алексей Александрович Боков");
    ui->lwScore->addItem("50 66 69");
    pen.score[0] = 50;
    pen.score[1] = 66;
    pen.score[2] = 69;
    pen.name = "Алексей Александрович Боков";
    lst.push_back(pen);
    ui->lwStudents->addItem("Денис Антонович Богданов");
    ui->lwScore->addItem("100 100 100");
    pen.score[0] = 100;
    pen.score[1] = 100;
    pen.score[2] = 100;
    pen.name = "Денис Антонович Богданов";
    lst.push_back(pen);
    ui->lwStudents->addItem("Алексей Антонович Антонов");
    ui->lwScore->addItem("50 50 50");
    pen.score[0] = 50;
    pen.score[1] = 50;
    pen.score[2] = 50;
    pen.name = "Алексей Антонович Антонов";
    lst.push_back(pen);
    ui->lwStudents->addItem("Чун Зы");
    ui->lwScore->addItem("90 100 100");
    pen.score[0] = 90;
    pen.score[1] = 100;
    pen.score[2] = 100;
    pen.name = "Чун Зы";
    lst.push_back(pen);
    ui->lwStudents->addItem("Мария Дмитриевна Ахматова");
    ui->lwScore->addItem("30 30 40");
    pen.score[0] = 30;
    pen.score[1] = 30;
    pen.score[2] = 40;
    pen.name = "Мария Дмитриевна Ахматова";
    lst.push_back(pen);
    connect(ui->pbAdd, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbAddAfter, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbClear, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbSort, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbDelete, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbEdit, &QPushButton::clicked, this, &MainWindow::updateList);
    connect(ui->pbCancel, &QPushButton::clicked, this, &MainWindow::updateList);
    status = Status::Other;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showMessage(QString str) {
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}

int SumArr(int x[]) {
    int len = sizeof(x)/sizeof(int);
    int s = 0;
    for(int i = 0; i<len; i++) s+=x[i];
    return s;
}

void MainWindow::setMemory() {
    Node* p = lst.first;
    Memlst.first = nullptr;
    Memlst.last = nullptr;
    while(p) {
        Memlst.push_back(p->val);
        p=p->next;
    }
}
void MainWindow::on_pbAdd_clicked()
{
    if(status != Status::Edit) {
    setMemory();
    bool flag = true;
    for(int i = 0; i < ui->leStudent->text().split(" ").length(); i++){
        flag = ui->leStudent->text().split(" ")[i].isEmpty();
        if(!flag) break;
    }
    if(!flag && (ui->leScore->text().split(" ").length() == 3) && (ui->leScore->text().split(" ")[2] != "")) {
        pen.name=ui->leStudent->text();
        for(int i = 0; i < 3; i++) pen.score[i] = ui->leScore->text().split(" ")[i].toInt();
        lst.push_back(pen);
    } else {
        showMessage("Неверно заполнено данные");
    }
    }
}

void MainWindow::updateList() {

    ui->lwStudents->clear();
    ui->lwScore->clear();
    Node* p = lst.first;
    while(p) {
        ui->lwStudents->addItem(p->val.name);
        ui->lwScore->addItem(QString::number(p->val.score[0])+" "+QString::number(p->val.score[1])+" "+QString::number(p->val.score[2]));
        p=p->next;
    }
}

void MainWindow::on_lwScore_itemSelectionChanged()
{
    ui->lwStudents->setCurrentRow(ui->lwScore->currentRow());
}


void MainWindow::on_lwStudents_itemSelectionChanged()
{
    ui->lwScore->setCurrentRow(ui->lwStudents->currentRow());
}


void MainWindow::on_pbAddAfter_clicked()
{
    if(status != Status::Edit) {
    setMemory();
    if(ui->lwStudents->selectionModel()->hasSelection()) {
        //pen.name = ui->lwStudents->item(ui->lwStudents->currentRow())->text();
        Node* p = lst.find(ui->lwStudents->currentRow());
        if(p) {
            bool flag = true;
            for(int i = 0; i < ui->leStudent->text().split(" ").length(); i++){
                flag = ui->leStudent->text().split(" ")[i].isEmpty();
                if(!flag) break;
            }
            if(!flag && (ui->leScore->text().split(" ").length() == 3) && (ui->leScore->text().split(" ")[2] != "")) {
                pen.name=ui->leStudent->text();
                for(int i = 0; i < 3; i++) pen.score[i] = ui->leScore->text().split(" ")[i].toInt();
                p=p->next;
                while(p){
                    if(p->next!=nullptr){
                        man2.name=p->next->val.name;
                        for(int i = 0; i<3; i++) man2.score[i]=p->next->val.score[i];
                        man1.name=p->val.name;
                        for(int i = 0; i<3; i++) man1.score[i]=p->val.score[i];
                        p->val.name=pen.name;
                        for(int i = 0; i<3; i++) p->val.score[i]=pen.score[i];
                        p->next->val.name=man1.name;
                        for(int i = 0; i<3; i++) p->next->val.score[i]=man1.score[i];
                        pen.name=man2.name;
                        for(int i = 0; i<3; i++) pen.score[i]=man2.score[i];
                    } else {
                        man1=p->val;
                        p->val=pen;
                        pen=man1;
                    }
                    p=p->next;

                }
                lst.push_back(pen);
                p = lst.first;
                for(int i = 0; p; i++) {
                    p->number=i;
                    p=p->next;
                }
            } else {
                showMessage("Неверно заполнено данные");
            }
        }
    } else {
        showMessage("Выберите студента");
    }
    }
}

void MainWindow::on_pbClear_clicked()
{
    if(status != Status::Edit) {
        setMemory();
        Node* p = lst.first;
        while(!lst.is_empty()) {
            lst.remove(0);
        }
    }
}


void MainWindow::on_pbEdit_clicked()
{
    /*setMemory();
    bool flag = true;
    for(int i = 0; i < ui->leStudent->text().split(" ").length(); i++){
        flag = ui->leStudent->text().split(" ")[i].isEmpty();
        if(!flag) break;
    }
    if(!flag && (ui->leScore->text().split(" ").length() == 3) && (ui->leScore->text().split(" ")[2] != "") && (ui->lwStudents->selectionModel()->hasSelection())) {
        pen.name=ui->lwStudents->item(ui->lwStudents->currentRow())->text();
        for(int i = 0; i < 3; i++) pen.score[i] = ui->lwScore->item(ui->lwScore->currentRow())->text().split(" ")[i].toInt();
        Node* p=lst.find(ui->lwStudents->currentRow());
        p->val.name=ui->leStudent->text();
        for(int i = 0; i < 3; i++) p->val.score[i] = ui->leScore->text().split(" ")[i].toInt();
    } else {
        showMessage("Неверно заполнено данные");
    }*/
    if(ui->lwStudents->selectionModel()->hasSelection() && status!=Status::Edit) {
        status = Status::Edit;
        py=lst.find(ui->lwStudents->currentRow());
        ui->leStudent->setText(ui->lwStudents->item(ui->lwStudents->currentRow())->text());
        ui->leScore->setText(ui->lwScore->item(ui->lwScore->currentRow())->text());
    } else if(status==Status::Edit) {
        bool flag = true;
        for(int i = 0; i < ui->leStudent->text().split(" ").length(); i++){
            flag = ui->leStudent->text().split(" ")[i].isEmpty();
            if(!flag) break;
        }
        if(!flag && (ui->leScore->text().split(" ").length() == 3) && (ui->leScore->text().split(" ")[2] != "")) {
            pen.name=ui->leStudent->text();
            for(int i = 0; i < 3; i++) pen.score[i] = ui->leScore->text().split(" ")[i].toInt();
            py->val=pen;
            status=Status::Other;
            ui->leStudent->clear();
            ui->leScore->clear();
        } else {
            showMessage("Неверно заполнено данные");
        }
    }
}


void MainWindow::on_pbSort_clicked()
{
    if(status != Status::Edit) {
        setMemory();
        if (!lst.is_empty()) {
            for (Node* q = lst.first; q; q = q->next) {
                for (Node* r = q->next; r; r = r->next) {
                    if (SumArr(q->val.score)/3.f > SumArr(r->val.score)/3.f) {
                        pen = r->val;
                        r->val = q->val;
                        q->val = pen;
                    }
                }
            }
        }
    }
}


void MainWindow::on_pbCancel_clicked()
{
    /*
    Node* p = lst.first;
    Memlst1.first = nullptr;
    Memlst1.last = nullptr;
    while(p) {
        Memlst1.push_back(p->val);
        p=p->next;
    }
    lst.first=nullptr;
    lst.last=nullptr;
    p = Memlst.first;
    while(p) {
        lst.push_back(p->val);
        p=p->next;
    }
    Memlst.first=nullptr;
    Memlst.last=nullptr;
    p = Memlst1.first;
    while(p) {
        Memlst.push_back(p->val);
        p=p->next;
    }*/
    if(status==Status::Edit) {
        status = Status::Other;
        ui->leStudent->clear();
        ui->leScore->clear();
    }
}


void MainWindow::on_pbDelete_clicked()
{
    if(status != Status::Edit) {
        if(ui->lwStudents->selectionModel()->hasSelection()) {
            setMemory();
            pen.name=ui->lwStudents->item(ui->lwStudents->currentRow())->text();
            for(int i = 0; i < 3; i++) pen.score[i] = ui->lwScore->item(ui->lwScore->currentRow())->text().split(" ")[i].toInt();
            Node* p=lst.find(ui->lwStudents->currentRow());
            lst.remove(ui->lwStudents->currentRow());
        }
    }
}

