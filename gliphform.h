#ifndef GLIPHFORM_H
#define GLIPHFORM_H

#include "common.h"

#include <QWidget>

namespace Ui {
class GliphForm;
}

class GliphForm : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *e) override;

public:
    explicit GliphForm(QWidget *parent = nullptr);
    ~GliphForm();

private:
    Ui::GliphForm *ui;
    int ha=20;
    QString fontname = "Hack";
    int fontsize=24;
    int interline = 18;
    int padding=4;
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool mousepress=false;
    int colo=0, riga=0;


signals:
    void charClick(int val);
};

#endif // GLIPHFORM_H
