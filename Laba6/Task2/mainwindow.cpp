#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,500);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << " Hash " << " Key " << " Data ");
    ui->tableWidget->setColumnWidth(0,210);
    ui->tableWidget->setColumnWidth(1,210);
    ui->tableWidget->setColumnWidth(2,210);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int key = ui->spinBox_2->value();
    QString s = ui->lineEdit->text();
    if(s==""){
        QMessageBox m;
        m.warning(this,"Error","Full Fill data line.\nPlease, do it");
        return;
    }
    if(table.contains(key)){
        QMessageBox m;
        m.warning(this,"Error","There is already element with such key.\nPlease, fix it");
        return;
    }

    table.insert(key,s);
    print();
}

void MainWindow::print()
{
    int rows = 0;
    ui->tableWidget->setRowCount(0);
    for(int i=0;i<table.vector.size();i++){
        if(!this->table.vector[i].isEmpty()){
            for(int j=0;j<this->table.vector[i].getSize();j++){
                ui->tableWidget->setRowCount(rows + 1);
                QString t, p;
                qDebug() << "aye";
                ui->tableWidget->setItem(rows,0,new QTableWidgetItem(p.setNum(this->table.hash(this->table.vector[i][j].key))));
                ui->tableWidget->setItem(rows,1, new QTableWidgetItem(t.setNum(this->table.vector[i][j].key)));
                ui->tableWidget->setItem(rows,2,new QTableWidgetItem(this->table.vector[i][j].data));
                rows++;
            }
        }
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    int key = ui->spinBox->value();
    if(!this->table.contains(key)){
        QMessageBox m;
        m.warning(this,"Attention!","There is no element with such key.\nPlease, intput another key");
        return;
    }

    this->table.deleteByKey(key);
    print();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    int key = ui->spinBox->value();
    if(!this->table.contains(key)){
        QMessageBox m;
        m.warning(this,"Attention!","There is no element with such key.\nPlease, intput another key");
        return;
    }
    this->table.search(key);
    ui->textEdit->setText(this->table.s);
}

