/*****************************************************************************
 * ANSIEDITOR
 * (c) 2023 by Felice Murolo, Salerno - Italia
 * All rights reserved, released under GPL3 license
 *
 ****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ansiwidget.h"
#include "palette.h"
#include "qcodepage437codec.h"
#include "gliphform.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "toolbox.h"
#include <QCloseEvent>
#include <QClipboard>
#include "sauceform.h"
#include "libgen.h"

QString prgname = "AnsiEditor";
QString copyright = "(c) 2023 by Felice Murolo, Salerno - Italia";
QString license = "All rights reserved, released under GPL3 license";
QString version = "1.5.1a";

extern QString fileToLoad;

AnsiWidget *av=nullptr;
Palette *pal=nullptr;
GliphForm *gl=nullptr;
ToolBox *tb=nullptr;
SauceForm *sf=nullptr;

#include "sauce.h"
QString eof= QChar(26);
struct _sauce sauce;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(prgname+" v"+version+" - "+copyright);
    setWindowIcon(QPixmap(":/image/icon"));

    pal = new Palette(this);
    pal->show();
    ui->paletteLayout->addWidget(pal);

    av = new AnsiWidget(ui->scrollArea);
    ui->scrollArea->setWidget(av);
    av->setFocus();
    connect(ui->cbBlink,SIGNAL(stateChanged(int)),av,SLOT(cbBlinkChanged(int)));
    connect(av,SIGNAL(csrRowChanged(int)), this, SLOT(avCsrRowChanged(int)));
    connect(av,SIGNAL(documentModified()),this,SLOT(documentModified()));
    connect(av,SIGNAL(attrsPicked(int)),this,SLOT(attrsPicked(int)));
    connect(av,SIGNAL(attrsPicked(int)),pal,SLOT(attrsPicked(int)));
    connect(av,SIGNAL(repaintDone()),this, SLOT(avRepaint()));

    gl = new GliphForm();
    gl->setWindowTitle(prgname+" v"+version+" - "+copyright);
    gl->setWindowIcon(QPixmap(":/image/icon"));
    connect(gl,SIGNAL(charClick(int)),av,SLOT(charClick(int)));
    connect(gl,SIGNAL(charClick(int)),this,SLOT(charClick(int)));

    tb = new ToolBox(this);
    ui->paletteLayout->addWidget(tb);
    connect(tb,SIGNAL(applyAttrsClicked()),av,SLOT(applyAttrs()));
    tb->show();

    sf = new SauceForm();
    sf->setWindowTitle(prgname+" v"+version+" - "+copyright);
    sf->setWindowIcon(QPixmap(":/image/icon"));

    if (fileToLoad != "") {
        loadFile(fileToLoad);
    }
    else {
        loadFile(":/ansi/test");
    }
    showStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionClick(QAction *a)
{
    QString fileName="";

    QString n = a->objectName();
    if (DEBUG) cout << n.toLatin1().data() << endl;
    if (n == "actionLoad") {
        if (modified){
            int ret = artLostMsg();
            if (ret == QMessageBox::Cancel) {
                return;
            }
        }
        fileName = QFileDialog::getOpenFileName(this, tr("Open ANSI FILE"), (lastpath != "" ? lastpath : QDir::homePath()), tr("Image Files (*.ans *.ANS *.ansi)"));
        lastpath = dirname(TC(fileName));
        loadFile(fileName);
        modified = false;
    }
    else if (n == "actionNew_Ansi_Art"){
        int ret = artLostMsg();
        if (ret == QMessageBox::Ok) av->clear();
        modified = false;
        showStatus();
    }
    else if (n == "actionGliph_Window"){
        gl->show();
    }
    else if (n == "actionSave"){
        if (document == "") {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save ANSI FILE"), QDir::homePath(), tr("Image Files (*.ans *.ANS *.ansi)"));
            if (fileName != "") {
                if (!fileName.endsWith(".ans") && !fileName.endsWith(".ansi") && !fileName.endsWith(".ANS")) fileName+=".ans";
                document=fileName;
            }
        }
        if (document != "") {
            av->saveFile(document);
            modified = false;
            showStatus();
        }
    }
    else if (n == "actionSave_As"){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save ANSI FILE"), QDir::homePath(), tr("Image Files (*.ans *.ANS *.ansi)"));
        if (fileName != "") {
            if (!fileName.endsWith(".ans") && !fileName.endsWith(".ansi") && !fileName.endsWith(".ANS")) fileName+=".ans";
            document=fileName;
            if (document != "") {
                av->saveFile(document);
                modified = false;
                showStatus();
            }
        }
    }
    else if (n == "actionUndo"){
        av->applicateUnDo();
    }
    else if (n == "actionCopy"){
        QClipboard *cb = QGuiApplication::clipboard();
        cb->setText(av->getSelection());
    }
    else if (n == "actionPaste"){
        av->ansiPaste();
    }
    else if (n == "actionCut"){
        av->getSelection(true);
    }
    else if (n == "actionEdit_Sauce_infos"){
        sf->show();
    }
    else if (n == "actionRemove_Line"){
        QMessageBox msgBox;
        msgBox.setText("Current line of your Ansi Art will be lost (UNDO will be not possible).\n\nAre yoy sure?\n");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if (msgBox.exec() ==  QMessageBox::Ok) av->removeLine();
    }
    else if (n == "actionDisable_2J") {
        if (a->isChecked()) {
            av->setShw2J(false);
        }
        else {
            av->setShw2J(true);
        }
        loadFile(document);
    }
    else if (n == "actionAbout"){
        QMessageBox msgBox;
        msgBox.setText(prgname+" v"+version+"\n"+copyright+"\n"+license+"\n\n");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if (msgBox.exec() ==  QMessageBox::Ok) av->removeLine();

    }
    else if (n == "actionExit"){
        if (modified) {
            int ret = artLostMsg();
            if (ret == QMessageBox::Ok) QApplication::exit(0);
        }
        else QApplication::exit(0);
    }
    showStatus();
}

bool MainWindow::loadFile(QString filename)
{
    bool ret=false;
    QString eof= QChar(26);
    char sc[128];

    QFile f(filename);
    if ((f.open(QFile::ReadOnly))){
        av->clear();
        if (DEBUG) cout << "==================================================================================" << endl;
        if (!filename.startsWith(":")) document = filename;
        QByteArray contents = f.readAll();
        f.close();
        QString s = contents.right(129);
        memcpy(sc,contents.right(128).data(),128);
        if (s.startsWith(eof+"SAUCE00")) {
            contents = contents.left(contents.length()-129);
            memcpy((void *)&sauce, sc,128);
            char ss[36];
            cout << "Sauce infos:" << endl;
            memcpy(ss,sauce.title,35);
            ss[35]=0;
            cout << "Title: " << ss << endl;
            memcpy(ss,sauce.author,20);
            ss[20]=0;
            cout << "Author: " << ss << endl;
            memcpy(ss,sauce.group,20);
            ss[20]=0;
            cout << "Group: " << ss << endl;
            memcpy(ss,sauce.date,8);
            ss[8]=0;
            cout << "Date: " << ss << endl;
        }
        QList<QByteArray> lines = contents.split('\n');
        foreach(QByteArray l, lines) {
            av->parseTxt(l.data());
        }
        ret = true;
        av->repaint();
        modified = false;
        showStatus();
    }
    return ret;
}

void MainWindow::showStatus()
{
    ui->lbdocname->setText(document+(modified ? " *" : ""));
}

int MainWindow::artLostMsg()
{
    QMessageBox msgBox;
    msgBox.setText("Current Ansi Art will be lost.\n\nAre yoy sure?\n");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    return msgBox.exec();
}

void MainWindow::avCsrRowChanged(int csrow)
{
    int y = csrow*(av->getFontsize()+av->getInterline())+av->getPadding();
    ui->scrollArea->ensureVisible(0,y,0,av->getFontsize()+av->getInterline()+av->getPadding());
}

void MainWindow::charClick(int val)
{
    QCodePage437Codec *qp = new QCodePage437Codec();
    char s[2];
    s[0]=val;
    s[1]=0;
    ui->tbChar->setText(qp->toUnicode(s));
    currChar=val;
}

void MainWindow::tbCharClick()
{
    if (currChar) {
        av->charClick(currChar);
    }
    else {
        gl->show();
    }
}

void MainWindow::documentModified()
{
    modified=true;
    showStatus();
}

void MainWindow::attrsPicked(int at)
{
    if (at & 8) ui->cbBlink->setChecked(true);
    else ui->cbBlink->setChecked(false);
}

void MainWindow::avRepaint()
{
    ui->lbrowscols->setText("Row,Col: "+QString::number(av->getCsrow())+","+QString::number(av->getCscol()));
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (modified) {
        int ret = artLostMsg();
        if (ret == QMessageBox::Cancel) {
            e->ignore();
            return;
        }
    }
    if (gl) gl->close();
    if (sf) sf->close();
    QWidget::closeEvent(e);
}


