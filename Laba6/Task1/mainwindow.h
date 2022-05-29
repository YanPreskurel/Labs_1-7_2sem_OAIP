#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
#include "tree.h"
#include <regex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_AddCell_clicked();

    void on_Clear_clicked();

    void on_AddToTree_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void getNodes();
    void printTree();
    void GetInOrder();
    void GetPreOrder();
    void GetPostOrder();
    void GetBFS();
    bool checkKey(QString s);

private:
    Ui::MainWindow *ui;
    int i = 0;
    QVector<std::pair<int,QString>> vector;
    AVLTree<QString> tree;
    QString G;
};
#endif // MAINWINDOW_H
