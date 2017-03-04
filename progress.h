#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QCloseEvent>

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
    void addItem(QString &fileName);
    void addResult(bool result);

private slots:
    void on_btnOK_clicked();

private:
    Ui::Progress *ui;

protected:
    // overload QWidget::closeEvent(QCloseEvent *)
    void closeEvent(QCloseEvent *event);
};

#endif // PROGRESS_H
