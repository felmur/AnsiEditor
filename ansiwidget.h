#ifndef ANSIWIDGET_H
#define ANSIWIDGET_H

#include "common.h"

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QRubberBand>

class AnsiWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnsiWidget(QWidget *parent = nullptr);
    ~AnsiWidget();
    void parseTxt(char *str);
    void clear();
    uint getRows() const;
    uint getCols() const;
    uint getHa() const;
    uint getPadding() const;
    uint getFontsize() const;
    uint getInterline() const;
    bool saveFile(QString filename);
    bool applicateUnDo();
    QString getSelection(bool cut=false);
    void ansiPaste();
    bool getShw2J() const;
    void setShw2J(bool newShw2J);
    bool removeLine();

    int getCsrow() const;
    int getCscol() const;

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;


private:
    int rows = 80;
    int cols = 80;
    int ha = 9;
    int padding = 4;
    QString fontname = "Hack";
    int fontsize = 12;
    int interline = (fontsize/3) < 4 ? 4 : fontsize/3;
    char *buf=nullptr;
    char *attrs=nullptr;
    QColor colors[17] = {
        // 8 normal Colors
        QColor(0, 0, 0),          // Black
        QColor(170, 0, 0),      // Red
        QColor(0, 170, 0),      // Green
        QColor(170, 85, 0),     // Yellow
        QColor(0, 0, 170),     // Blue
        QColor(170, 0, 170),    // Magenta
        QColor(0, 170, 170),      // Cyan
        QColor(178, 178, 178),    // light gray
        // 8 bright colors
        QColor(85, 85, 85),       // Dark Gray
        QColor(255, 85, 85),      // Bright Red
        QColor(85, 255, 85),      // Bright Green
        QColor(255, 255, 85),      // Bright Yellow
        QColor(85, 85, 255),     // Bright Blue
        QColor(255, 85, 255),    // Bright Magenta
        QColor(85, 255, 255),     // Bright Cyan
        QColor(255, 255, 255),    // white
        QColor(255, 255, 255,150) // cursor
    };
    QString lastclip="";

    QString esc = QChar(27);
    QString csi = esc + "[";
    QStringList cmds={"H", "A", "B", "C", "D", "E", "F", "G", "J", "K", "f", "m", "s", "u"};
    int riga=0, sriga=0;
    int colo=0, scolo=0;
    uint fg=7, bg=0;
    bool bright=false, blink=false, blinkst=false, blinkwrt=false;
    QTimer *timer1=nullptr;
    QByteArray StoQ(QString txt);
    int csrow=0, cscol=0;
    bool eventFilter(QObject *obj, QEvent *event) override;
    struct _unDo{
        int offs;
        uint8_t txtval;
        uint8_t attrsval;
        uint16_t op;
    };
    QList<_unDo> unDo;
    int unDoPtr = 0;
    QRubberBand *rubber=nullptr;
    int cfin=0, rfin=0;
    struct _paste {
        QByteArray pastetxt;
        QByteArray pasteattrs;
    };
    struct _paste paste;
    bool shw2J=true;


public slots:
    void charClick(int val);

private slots:
    void timer1timeout();
    void cbBlinkChanged(int state);
    void applyAttrs();

signals:
    void csrRowChanged(int csrow);
    void documentModified();
    void attrsPicked(int at);
    void repaintDone();
};

#endif // ANSIWIDGET_H
