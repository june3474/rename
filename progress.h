#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class Progress;
}

class Progress : public QDialog
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

    void initTableWidget();
    void setUpProgressBar(int maxStep);
    void updateProgressBar(int currentStep);
    void addItem(QTableWidgetItem *item);

private slots:
    void on_btnOK_clicked();

private:
    Ui::Progress *ui;
};

#endif // PROGRESS_H
