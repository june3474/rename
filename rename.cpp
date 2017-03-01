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

bool Rename::checkFilename(QString fileName)
{
//#ifdef Q_WS_WIN
    QRegExp filter = QRegExp("[/:*?\"<>|\\\\]");
    if(filter.indexIn(fileName) == -1)
        return true;
    else
        return false;
//#endif

}

void Rename::on_lineEditDir_returnPressed()
{
    QString path = QDir::cleanPath(QDir::toNativeSeparators(ui->lineEditDir->text()));
    QFileInfo info = QFileInfo(path);
    if(info.isDir()){
        ui->lineEditDir->setText(path);
        this->focusNextChild();

        updateModel();
    }
    else {
        model.clear();
        QMessageBox::critical(this, tr("Error"), tr("Invalid Directory!"));
        ui->lineEditDir->selectAll();
    }
}

void Rename::on_btnFileBrowse_clicked()
{
    QString oldDir = ui->lineEditDir->text();
    QString dir = QFileDialog::getExistingDirectory(this, "Choose the directory", ui->lineEditDir->text());
    if(dir.isEmpty())
        dir = oldDir;
    ui->lineEditDir->setText(dir);
    this->focusNextChild();

    updateModel();
}


void Rename::on_comboBox_currentIndexChanged(int /* index */)
{
    updateModel();
}

void Rename::on_lineEditOld_returnPressed()
{
    //QString escapedStr = QRegExp::escape(ui->lineEditOld->text());
    //QRegExp regEx = QRegExp(escapedStr);

    QRegExp regEx = QRegExp(ui->lineEditOld->text());
    if(regEx.isValid()){
        if(delegateBefore)
            delete delegateBefore;
        delegateBefore = new RegExDelegate(this, RegExDelegateType::Match, regEx,  \
                                           ui->lineEditNew->text(), Qt::darkRed, Qt::white);
        ui->listBefore->setItemDelegate(delegateBefore);
        this->focusNextChild();
    }
    else {
        ui->btnRun->setDisabled(true);
        QMessageBox::critical(this, tr("Error"), tr("Invalid Regular Expression!"));
        ui->lineEditOld->selectAll();
    }
}

void Rename::on_lineEditNew_returnPressed()
{
    if(checkFilename(ui->lineEditNew->text()))
        qDebug() << "OK";
    else
        qDebug() << "Nope";

    QRegExp regEx = QRegExp(ui->lineEditOld->text());
    if(regEx.isValid()){
        if(delegateAfter)
            delete delegateAfter;
        delegateAfter = new RegExDelegate(this, RegExDelegateType::Replace, regEx,  \
                                           ui->lineEditNew->text(), Qt::darkGreen, Qt::white);
        ui->listAfter->setItemDelegate(delegateAfter);
        this->focusNextChild();
    }
}

void Rename::on_chkBoxGreedy_stateChanged(int /* state */)
{

}

void Rename::on_chkBoxRecursive_stateChanged(int /* state */)
{
    updateModel();
}

void Rename::on_btnFileBrowse_pressed()
{
    on_btnFileBrowse_clicked();
}
