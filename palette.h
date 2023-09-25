#ifndef PALETTE_H
#define PALETTE_H

#include "common.h"

#include <QObject>
#include <QFrame>

class Palette : public QFrame
{
    Q_OBJECT
public:
    explicit Palette(QWidget *parent = nullptr);
    int fgcolor = 7;
    int bgcolor = 0;
    QList<int> getColors();

protected:
    void paintEvent(QPaintEvent *e) override;

public slots:
    void attrsPicked(int at);

private:
    bool fgflg=true, bgflg=false;
    void setColor(int);

signals:

private slots:
    void tbfgClick();
    void tbbgClick();
    void col0Click();
    void col1Click();
    void col2Click();
    void col3Click();
    void col4Click();
    void col5Click();
    void col6Click();
    void col7Click();
    void col8Click();
    void col9Click();
    void col10Click();
    void col11Click();
    void col12Click();
    void col13Click();
    void col14Click();
    void col15Click();


};

#endif // PALETTE_H
