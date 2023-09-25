#include "toolbox.h"
#include "ui_toolbox.h"
#include <QPainter>

ToolBox::ToolBox(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ToolBox)
{
    ui->setupUi(this);
}

ToolBox::~ToolBox()
{
    delete ui;
}

void ToolBox::pickClick()
{
    ui->tbsquare->setChecked(false);
    ui->tbsquarefill->setChecked(false);
    if (ui->tbpick->isChecked()) tbstate=PICK_ON;
    else tbstate=ALL_OFF;
    if (DEBUG) cout << tbstate << endl;
    repaint();
}

void ToolBox::squareClick()
{
    ui->tbpick->setChecked(false);
    ui->tbsquarefill->setChecked(false);
    if (ui->tbsquare->isChecked()) tbstate=SQUARE_ON;
    else tbstate=ALL_OFF;
    if (DEBUG) cout << tbstate << endl;
    repaint();
}

void ToolBox::squarefillClick()
{
    ui->tbpick->setChecked(false);
    ui->tbsquare->setChecked(false);
    if (ui->tbsquarefill->isChecked()) tbstate=SQUAREFILLED_ON;
    else tbstate=ALL_OFF;
    if (DEBUG) cout << tbstate << endl;
    repaint();
}

void ToolBox::applyAttrsClick()
{
    ui->tbpick->setChecked(false);
    ui->tbsquare->setChecked(false);
    ui->tbsquarefill->setChecked(false);
    tbstate=APPLYATTRS_CLK;
    if (DEBUG) cout << tbstate << endl;
    repaint();
}

void ToolBox::paintEvent(QPaintEvent *e)
{
    int x,y;
    (void) e;
    QPainter painter(this);

    painter.setPen(Qt::yellow);
    switch(tbstate){
    case PICK_ON:
        x=ui->tbpick->x();
        y=ui->tbpick->y();
        painter.drawRect(x-2,y-2,52,52);
        painter.drawRect(x-3,y-3,54,54);
        break;
    case SQUARE_ON:
        x=ui->tbsquare->x();
        y=ui->tbsquare->y();
        painter.drawRect(x-2,y-2,52,52);
        painter.drawRect(x-3,y-3,54,54);
        break;
    case SQUAREFILLED_ON:
        x=ui->tbsquarefill->x();
        y=ui->tbsquarefill->y();
        painter.drawRect(x-2,y-2,52,52);
        painter.drawRect(x-3,y-3,54,54);
        break;
    case APPLYATTRS_CLK:
        tbstate = ALL_OFF;
        emit applyAttrsClicked();
        break;
    }
}

