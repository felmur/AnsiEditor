#include "gliphform.h"
#include "ui_gliphform.h"
#include "qcodepage437codec.h"
#include <QPainter>
#include <QMouseEvent>

GliphForm::GliphForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GliphForm)
{
    ui->setupUi(this);
    QFont font = QFont(fontname,fontsize,500);
    QFontMetrics fm(font);
    ha = fm.horizontalAdvance(QString(" ")) + 4;
    setFont(font);

    installEventFilter(this);
}

GliphForm::~GliphForm()
{
    delete ui;
}

void GliphForm::paintEvent(QPaintEvent *e)
{
    (void) e;
    int v;
    uint8_t col=0, row=0;
    int x,y;
    char b[2];

    QCodePage437Codec *qp = new QCodePage437Codec();
    QPainter painter(this);
    painter.setPen(Qt::black);
    b[1]=0;
    for (v=0; v<256; v++) {
        b[0]=v;
        x = padding + col*ha;
        y = padding + row*(fontsize+interline)+fontsize;
        painter.drawText(x,y,qp->toUnicode(b));
        col++;
        if (col>23) {
            row++;
            col=0;
        }
    }
    if (mousepress) {
        x = padding+colo*ha-2;
        y = padding+riga*(fontsize+interline)-9;
        painter.setPen(Qt::blue);
        painter.drawRect(x,y,ha,fontsize+interline);
    }

}

bool GliphForm::eventFilter(QObject *obj, QEvent *event)
{
    (void) obj;
    int v;
    if (event->type() == QEvent::MouseButtonPress) {
        mousepress=true;
        QMouseEvent *mouseEvent = (QMouseEvent*)(event);
        colo = (mouseEvent->pos().x()-padding)/ha;
        riga = (mouseEvent->pos().y()-padding)/(fontsize+interline);
        v = (riga * 24)+colo;
        if (v>0 && v<255) {
            emit charClick(v);
        }
        repaint();
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        mousepress=false;
        repaint();
        return true;
    }

    else {
        return false;
    }
}
