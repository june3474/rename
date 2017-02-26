#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "rename.h"
#include "ui_rename.h"

Rename::Rename(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Rename)
{
    ui->setupUi(this);
    init();
}

Rename::~Rename()
{
    delete ui;
    delete delegateBefore;
    delete delegateAfter;
}

void Rename::init()
{
    // lineEditDir
    ui->lineEditDir->setText(QDir::currentPath());

    // Make sure that btnFileBrowse has not autoDefault property.
    ui->btnFileBrowse->setAutoDefault(false);

    //comboBox
    ui->comboBox->addItem("All (*)", \
                          (QStringList() << "*"));
    ui->comboBox->addItem("Image (*.jpg,*.png,*.bmp)", \
                          (QStringList() << "*.jpg" << "*.png" << "*.bmp"));
    ui->comboBox->addItem("Multimedia (*.mp4,*.avi)", \
                          (QStringList() << "*.mp4" << "*.avi"));
    //model
    updateModel();

    //view
    ui->listBefore->setModel(&model);
    delegateBefore = new RegExDelegate(this);
    ui->listBefore->setItemDelegate(delegateBefore);

    ui->listAfter->setModel(&model);
    delegateAfter = new RegExDelegate(this);
    ui->listAfter->setItemDelegate(delegateAfter);
}

void Rename::updateModel()
{
    model.clear();
    QFileInfoList fileInfoList = getFileInfoList(ui->lineEditDir->text(), \
                                                 ui->chkBoxRecursive->isChecked());

    foreach(QFileInfo fileInfo, fileInfoList){
        QStandardItem *item = new QStandardItem(fileInfo.fileName());
        item->setData(fileInfo.absoluteFilePath(), Qt::ToolTipRole);
        item->setEditable(false);
        model.appendRow(item);
    }
}

QFileInfoList Rename::getFileInfoList(const QString &path, bool recursive)
{
    QDir dir = QDir(path);
    QFileInfoList fileInfoList;
    QStringList nameFilters = ui->comboBox->itemData(ui->comboBox->currentIndex()).toStringList();

    foreach (QFileInfo fileInfo, dir.entryInfoList(nameFilters, QDir::Files|QDir::NoDotAndDotDot))
        fileInfoList.append(fileInfo);

    if(recursive){
        foreach (QString subDir, dir.entryList(nameFilters, QDir::Dirs|QDir::NoDotAndDotDot))
            fileInfoList += getFileInfoList(path + QDir::separator() + subDir, true);
    }

    return fileInfoList;
}

void Rename::on_lineEditDir_editingFinished()
{
    QString path = QDir::cleanPath(QDir::toNativeSeparators(ui->lineEditDir->text()));
    QFileInfo info = QFileInfo(path);
    if(info.isDir()){
        ui->lineEditDir->setText(path);
        updateModel();
    }
    else {
        model.clear();

        // If we don't block sigals, we have two editignFinished() signals emitted
        // first, when the return key is entered, and the second, when the msgBox takes the focus.
        // So, msgBox is shown twice.
        ui->lineEditDir->blockSignals(true);
        ui->btnRun->setDisabled(true);
        QMessageBox::critical(this, tr("Error"), tr("Invalid Directory!"));
        ui->lineEditDir->selectAll();
        ui->lineEditDir->blockSignals(false);
    }
}

void Rename::on_btnFileBrowse_clicked()
{
    // prevent wrong-dir-msgBox when clicked even with a wrong dir in lineEditDir.
    ui->lineEditDir->blockSignals(true);
    QString oldDir = ui->lineEditDir->text();
    QString dir = QFileDialog::getExistingDirectory(this, "Choose the directory", ui->lineEditDir->text());
    if(dir.isEmpty())
        dir = oldDir;

    ui->lineEditDir->setText(dir);
    ui->lineEditDir->selectAll();
    ui->lineEditDir->blockSignals(false);

    updateModel();
}


void Rename::on_comboBox_currentIndexChanged(int /* index */)
{
    updateModel();
}

void Rename::on_lineEditOld_editingFinished()
{
    //QString escapedStr = QRegExp::escape(ui->lineEditOld->text());
    //QRegExp *regEx = new QRegExp(escapedStr);
    QRegExp *regEx = new QRegExp(ui->lineEditOld->text());
    if(regEx->isValid()){
        delete delegateBefore;
        delegateBefore = new RegExDelegate(this, regEx, Qt::red, Qt::white);
        ui->listBefore->setItemDelegate(delegateBefore);
        this->focusNextChild();
    }
    else {
        ui->lineEditOld->blockSignals(true);
        ui->btnRun->setDisabled(true);
        QMessageBox::critical(this, tr("Error"), tr("Invalid Regular Expression!"));
        ui->lineEditOld->selectAll();
        ui->lineEditOld->blockSignals(false);
    }
}

void Rename::on_lineEditNew_editingFinished()
{

}

void Rename::on_chkBoxGreedy_stateChanged(int state)
{

}

void Rename::on_chkBoxRecursive_stateChanged(int state)
{
    updateModel();
}
