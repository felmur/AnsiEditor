#include "sauceform.h"
#include "ui_sauceform.h"
#include "sauce.h"
#include <QDate>

extern struct _sauce sauce;

SauceForm::SauceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SauceForm)
{
    ui->setupUi(this);
    ui->letitle->setFocus();
}

SauceForm::~SauceForm()
{
    delete ui;
}

void SauceForm::pbokClick()
{
    QString s;

    hide();

    memcpy(sauce.ID,"SAUCE",5);
    memcpy(sauce.version,"00",2);
    sauce.datatype=1;
    sauce.filetype=1;

    s = ui->letitle->text();
    memset(sauce.title,32,35);
    if (!s.length()) s="Generated by AnsiEditor";
    memcpy(sauce.title,TC(s), s.length());

    s = ui->leauthor->text();
    memset(sauce.author,32,20);
    memcpy(sauce.author,TC(s), s.length());

    s = ui->legroup->text();
    memset(sauce.group,32,20);
    memcpy(sauce.group,TC(s), s.length());

    s = ui->ledate->text();
    memset(sauce.date,32,8);
    memcpy(sauce.date,TC(s), s.length());

}

void SauceForm::pbcancelClick()
{
    hide();
}

void SauceForm::showEvent(QShowEvent *e)
{
    QString s;
    (void) e;
    char ss[36];
    memcpy(ss,sauce.title,35);
    ss[35]=0;
    s = ss;
    ui->letitle->setText(s.trimmed());
    memcpy(ss,sauce.author,20);
    ss[20]=0;
    s=ss;
    ui->leauthor->setText(s.trimmed());
    memcpy(ss,sauce.group,20);
    ss[20]=0;
    s=ss;
    ui->legroup->setText(s.trimmed());
    memcpy(ss,sauce.date,8);
    ss[8]=0;
    s=ss;
    ui->ledate->setText(s.trimmed());
    if (ui->ledate->text().length()==0) {
        s = QDate::currentDate().toString("yyyyMMdd");
        ui->ledate->setText(s);
    }
}
