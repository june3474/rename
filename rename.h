#ifndef RENAME_H
#define RENAME_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFileInfoList>

#include "ui_rename.h"
#include "regexdelegate.h"
#include "progress.h"

namespace Ui {
class Rename;
}

class Rename : public QDialog
{
    Q_OBJECT

public:
    explicit Rename(QDialog *parent = 0);
    ~Rename();

public slots:

private:
    Ui::Rename *ui;
    QStandardItemModel model;
    RegExDelegate *delegateBefore;
    RegExDelegate *delegateAfter;
    Progress *dialog;

    bool dir_OK;
    bool old_OK;
    bool new_OK;

    void init();
    void updateModel();
    QFileInfoList getFileInfoList(const QString &path, bool recursive);
    bool checkFilename(QString fileName);
    void setBtnRunEnable();

private slots:
    void on_btnFileBrowse_clicked();
    void on_lineEditDir_returnPressed();
    void on_comboBox_currentIndexChanged(int /* index */);
    void on_lineEditOld_returnPressed();
    void on_lineEditNew_returnPressed();
    void on_chkBoxGreedy_stateChanged(int /* state */);
    void on_chkBoxRecursive_stateChanged(int /* state */);

    void on_btnFileBrowse_pressed();
    void on_btnRun_clicked();
};
#endif // RENAME_H
