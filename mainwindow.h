#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"

#include <QMainWindow>

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
    void actionClick(QAction *a);
    void avCsrRowChanged(int csrow);
    void charClick(int val);
    void tbCharClick();
    void documentModified();
    void attrsPicked(int at);
    void avRepaint();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::MainWindow *ui;
    bool loadFile(QString filename);
    int currChar=0;
    QString document = "";
    void showStatus();
    bool modified=false;
    int artLostMsg();
    QString lastpath="";


};
#endif // MAINWINDOW_H
