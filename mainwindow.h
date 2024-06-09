#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    List lst;
    Student pen;
    Student man1;
    Student man2;
    Node* py;
    List Memlst;
    List Memlst1;
    enum Status {
        Edit, Other
    };
    Status status;

private slots:
    void on_pbAdd_clicked();
    void updateList();
    void setMemory();
    void on_lwScore_itemSelectionChanged();

    void on_lwStudents_itemSelectionChanged();

    void on_pbAddAfter_clicked();

    void on_pbClear_clicked();

    void on_pbEdit_clicked();

    void on_pbSort_clicked();

    void on_pbCancel_clicked();

    void on_pbDelete_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
