#ifndef RENAME_H
#define RENAME_H

#include <QDialog>
#include "ui_rename.h"

namespace Ui {
class Rename;
}

class rename : public QDialog
{
    Q_OBJECT

public:
    explicit rename(QDialog *parent = 0);
    ~rename();

private:
    Ui::Rename *ui;
};

#endif // RENAME_H
