#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,500);

    ui->Vector->setRowCount(2);
    ui->Vector->setRowHeight(0,60);
    ui->Vector->setRowHeight(1,60);
    ui->Vector->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Vector->setVerticalHeaderLabels(QStringList() << " Key " << " Data ");


    ui->Tree->setColumnCount(2);
    ui->Tree->setColumnWidth(0,130);
    ui->Tree->setColumnWidth(1,130);
    ui->Tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Tree->setHorizontalHeaderLabels(QStringList() << " Key " << " Data ");

    ui->spinBox->setRange(INT_MIN,INT_MAX);

    ui->comboBox->addItems(QStringList() << "Pre-order" << "In-order" << "Post-order" << "breadth-first search");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddCell_clicked()
{
    ui->Vector->setColumnCount(i + 1);
    ui->Vector->setItem(0,i,new QTableWidgetItem());
    ui->Vector->setItem(1,i,new QTableWidgetItem());
    i++;
}


void MainWindow::on_Clear_clicked()
{
    i = 0;
    ui->Vector->setColumnCount(0);
    vector.clear();
}


void MainWindow::on_AddToTree_clicked()
{
    bool status = true;
    for(int i=0;i<ui->Vector->columnCount();++i){
        std::pair<int,QString> tmp;
        if(!checkKey(ui->Vector->item(0,i)->text()) ||ui->Vector->item(0,i)->text() == "" || ui->Vector->item(1,i)->text() == ""){
            status = false;
            vector.clear();
            QMessageBox m;
            m.warning(this,"Error","Wront Key input or cells are empty.\nPlease, fix it");
            return;
        }
        tmp.first = ui->Vector->item(0,i)->text().toInt();
        tmp.second = ui->Vector->item(1,i)->text();
        vector.push_back(tmp);
        qDebug()<< vector[i].second;
        qDebug()<<vector[i].first;
    }

    if(status){
        i = 0;
        ui->Vector->setColumnCount(0);
        getNodes();
        vector.clear();
        printTree();
        GetInOrder();
    }
}

void MainWindow::getNodes()
{
    for(int i=0;i<vector.size();i++){
        tree.push(vector[i].first,vector[i].second);
    }
}

void MainWindow::printTree()
{
    this->tree.printTree(this->tree.root);
    ui->textEdit->setText(this->tree.G);
    this->tree.G = "";
}

void MainWindow::GetInOrder()
{
    this->tree.k = 0;
    this->tree.inOrder(this->tree.root);
    ui->Tree->setRowCount(0);
    for(int i = 0;i<this->tree.V.size();i++){
        QString tmp;
        ui->Tree->setRowCount(i+1);
        ui->Tree->setItem(i,0,new QTableWidgetItem(tmp.setNum(this->tree.V[i].first)));
        ui->Tree->setItem(i,1,new QTableWidgetItem(this->tree.V[i].second));
    }
    QString s;
    ui->Counter->setText(s.setNum(this->tree.k));
    this->tree.k = 0;
    this->tree.V.clear();
}

void MainWindow::GetPreOrder()
{
    this->tree.preOrder(this->tree.root);
    ui->Tree->setRowCount(0);
    for(int i = 0;i<this->tree.V.size();i++){
        QString tmp;
        ui->Tree->setRowCount(i+1);
        ui->Tree->setItem(i,0,new QTableWidgetItem(tmp.setNum(this->tree.V[i].first)));
        ui->Tree->setItem(i,1,new QTableWidgetItem(this->tree.V[i].second));
    }
    this->tree.V.clear();
}

void MainWindow::GetPostOrder()
{
    this->tree.postOrder(this->tree.root);
    ui->Tree->setRowCount(0);
    for(int i = 0;i<this->tree.V.size();i++){
        QString tmp;
        ui->Tree->setRowCount(i+1);
        ui->Tree->setItem(i,0,new QTableWidgetItem(tmp.setNum(this->tree.V[i].first)));
        ui->Tree->setItem(i,1,new QTableWidgetItem(this->tree.V[i].second));
    }
    this->tree.V.clear();
}

void MainWindow::GetBFS()
{
    this->tree.wideOrder(this->tree.root);
    ui->Tree->setRowCount(0);
    for(int i = 0;i<this->tree.V.size();i++){
        QString tmp;
        ui->Tree->setRowCount(i+1);
        ui->Tree->setItem(i,0,new QTableWidgetItem(tmp.setNum(this->tree.V[i].first)));
        ui->Tree->setItem(i,1,new QTableWidgetItem(this->tree.V[i].second));
    }
    this->tree.V.clear();
}

bool MainWindow::checkKey(QString str)
{
    std::string s = str.toStdString();
    std::string ex = "-0123456789";
    if(s.find_first_not_of(ex) < s.size()){
        return false;
    }
    int k = 0;
    for(int i= 0;i<s.size();i++){
        if(s[i] == '-'){
            k++;
        }
    }
    if(k>1){
        return false;
    }
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    int i = ui->comboBox->currentIndex();

    switch(i){
    case 0:
        GetPreOrder();
        break;
    case 1:
        GetInOrder();
        break;
    case 2:
        GetPostOrder();
        break;
    case 3:
        GetBFS();
    default:
        break;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    int key = ui->spinBox->value();
    this->tree.pop(key);
    //this->tree.root = this->tree.deleteNode(this->tree.root,key);
    printTree();
    GetInOrder();
}


void MainWindow::on_pushButton_3_clicked()
{
    int key = ui->spinBox->value();
    auto element = this->tree.findElement(this->tree.root, key);
    if (element != nullptr)
    {
        ui->textEdit->setText("Data with such key is " + element->data);
    }
    else
    {
        ui->textEdit->setText("There is no element with such key");
    }
}

