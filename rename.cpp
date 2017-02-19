#include "rename.h"
#include "ui_rename.h"

rename::rename(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Rename)
{
    ui->setupUi(this);
}

rename::~rename()
{
    delete ui;
}
