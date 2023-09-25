#ifndef SAUCEFORM_H
#define SAUCEFORM_H

#include "common.h"

#include <QWidget>

namespace Ui {
class SauceForm;
}

class SauceForm : public QWidget
{
    Q_OBJECT

public:
    explicit SauceForm(QWidget *parent = nullptr);
    ~SauceForm();

private slots:
    void pbokClick();
    void pbcancelClick();


private:
    Ui::SauceForm *ui;
    void showEvent(QShowEvent *e);
};

#endif // SAUCEFORM_H
