#ifndef RENAME_H
#define RENAME_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFileInfoList>

#include "ui_rename.h"
#include "regexdelegate.h"

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

    void init();
    void updateModel();
    QFileInfoList getFileInfoList(const QString &path, bool recursive);

private slots:
    void on_btnFileBrowse_clicked();
    void on_lineEditDir_editingFinished();
    void on_comboBox_currentIndexChanged(int /* index */);
    void on_lineEditOld_editingFinished();
    void on_lineEditNew_editingFinished();
    void on_chkBoxGreedy_stateChanged(int state);
    void on_chkBoxRecursive_stateChanged(int state);
};

#endif // RENAME_H
