#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "common.h"

#include <QFrame>

namespace Ui {
class ToolBox;
}

class ToolBox : public QFrame
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *e) override;

public:
    explicit ToolBox(QWidget *parent = nullptr);
    ~ToolBox();
    Ui::ToolBox *ui;
    enum state { ALL_OFF=0, PICK_ON, SQUARE_ON, SQUAREFILLED_ON, APPLYATTRS_CLK };
    int tbstate=ALL_OFF;


signals:
    void applyAttrsClicked();

private:

private slots:
    void pickClick();
    void squareClick();
    void squarefillClick();
    void applyAttrsClick();
};

#endif // TOOLBOX_H
