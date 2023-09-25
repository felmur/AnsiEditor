#include "palette.h"
#include "ui_palette.h"
#include <QStyle>
#include <QPainter>

Ui::Palette ui;
QList<QToolButton *> btlst;

Palette::Palette(QWidget *parent)
    : QFrame{parent}
{
    ui.setupUi(this);
    setGeometry(0,0,110,320);

    btlst.append(ui.tbcol0);
    btlst.append(ui.tbcol1);
    btlst.append(ui.tbcol2);
    btlst.append(ui.tbcol3);
    btlst.append(ui.tbcol4);
    btlst.append(ui.tbcol5);
    btlst.append(ui.tbcol6);
    btlst.append(ui.tbcol7);
    btlst.append(ui.tbcol8);
    btlst.append(ui.tbcol9);
    btlst.append(ui.tbcol10);
    btlst.append(ui.tbcol11);
    btlst.append(ui.tbcol12);
    btlst.append(ui.tbcol13);
    btlst.append(ui.tbcol14);
    btlst.append(ui.tbcol15);
}

QList<int> Palette::getColors()
{
    QList<int> ret;
    ret.append(fgcolor);
    ret.append(bgcolor);
    return ret;
}

void Palette::paintEvent(QPaintEvent *e)
{
    (void) e;
    QPainter painter(this);
    if(fgflg) {
        painter.setPen(Qt::yellow);
        if (fgcolor==11) painter.setPen(Qt::cyan);
        painter.drawRect(9,4,34,34);
        painter.drawRect(8,3,36,36);
    }
    if (bgflg) {
        painter.setPen(Qt::yellow);
        painter.drawRect(29,14,34,34);
        painter.drawRect(28,13,36,36);
    }

}

void Palette::attrsPicked(int at)
{
    uint8_t f=(uint8_t)at >> 4;
    uint8_t b=(uint8_t)at & 0x07;
    ui.tbfg->setStyleSheet(btlst[f]->styleSheet());
    ui.tbbg->setStyleSheet(btlst[b]->styleSheet());
    fgcolor = f;
    bgcolor = b;
}

void Palette::setColor(int col)
{
    if (fgflg) {
        ui.tbfg->setStyleSheet(btlst[col]->styleSheet());
        fgcolor = col;
    }
    else if (bgflg and col<8){
        ui.tbbg->setStyleSheet(btlst[col]->styleSheet());
        bgcolor = col;
    }
    repaint();
}

void Palette::tbfgClick()
{
    if (DEBUG) cout << "FG" << endl;
    fgflg = true;
    bgflg = false;
    repaint();
}

void Palette::tbbgClick()
{
    if (DEBUG) cout << "BG" << endl;
    bgflg = true;
    fgflg = false;
    repaint();
}
void Palette::col0Click()
{
    if (DEBUG) cout << "COL0" << endl;
    setColor(0);
}

void Palette::col1Click()
{
    if (DEBUG) cout << "COL1" << endl;
    setColor(1);
}
void Palette::col2Click()
{
    if (DEBUG) cout << "COL2" << endl;
    setColor(2);
}
void Palette::col3Click()
{
    if (DEBUG) cout << "COL3" << endl;
    setColor(3);
}
void Palette::col4Click()
{
    if (DEBUG) cout << "COL4" << endl;
    setColor(4);
}
void Palette::col5Click()
{
    if (DEBUG) cout << "COL5" << endl;
    setColor(5);
}
void Palette::col6Click()
{
    if (DEBUG) cout << "COL6" << endl;
    setColor(6);
}
void Palette::col7Click()
{
    if (DEBUG) cout << "COL7" << endl;
    setColor(7);
}
void Palette::col8Click()
{
    if (DEBUG) cout << "COL8" << endl;
    setColor(8);
}
void Palette::col9Click()
{
    if (DEBUG) cout << "COL9" << endl;
    setColor(9);
}
void Palette::col10Click()
{
    if (DEBUG) cout << "COL10" << endl;
    setColor(10);
}
void Palette::col11Click()
{
    if (DEBUG) cout << "COL11" << endl;
    setColor(11);
}
void Palette::col12Click()
{
    if (DEBUG) cout << "COL12" << endl;
    setColor(12);
}
void Palette::col13Click()
{
    if (DEBUG) cout << "COL13" << endl;
    setColor(13);
}
void Palette::col14Click()
{
    if (DEBUG) cout << "COL14" << endl;
    setColor(14);
}
void Palette::col15Click()
{
    if (DEBUG) cout << "COL15" << endl;
    setColor(15);
}
