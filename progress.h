#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>

namespace Ui {
class Progress;
}

class Progress : public QDialog
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();



private slots:
    void on_btnOK_clicked();

private:
    Ui::Progress *ui;
};

#endif // PROGRESS_H
