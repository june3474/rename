#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "rename.h"
#include "progress.h"
#include "ui_rename.h"
#include "ui_progress.h"

Rename::Rename(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Rename)
{
    ui->setupUi(this);

    dir_OK = true;
    old_OK = true;
    new_OK = true;

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

    setBtnRunEnable();
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

/*
 * very primitive filename validator
 */
bool Rename::checkFilename(QString fileName)
{
    bool check = true;
    QRegExp filter;

#ifdef Q_WS_WIN // Windows
    // check invalid character
    filter = QRegExp("[/:*?\"<>|\\\\]");
    if(fileName.contains(filter))
        check = false;
    if(fileName.startsWith('.'))
        check = false;
#else // POSIX
    filter = QRegExp("[^0-9a-zA-Z._-]");
    if(fileName.contains(filter))
        check = false;
#endif

    return check;
}

void Rename::setBtnRunEnable()
{
    ui->btnRun->setEnabled(model.rowCount() && dir_OK && old_OK && new_OK);
}

void Rename::on_lineEditDir_returnPressed()
{
    QString path = QDir::cleanPath(QDir::toNativeSeparators(ui->lineEditDir->text()));
    QFileInfo info = QFileInfo(path);
    if(info.isDir()){
        ui->lineEditDir->setText(path);
        dir_OK = true;
        this->focusNextChild();

        updateModel();
    }
    else {
        model.clear();
        dir_OK = false;
        setBtnRunEnable();
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
    dir_OK = true;
    ui->lineEditDir->setText(dir);
    this->focusNextChild();

    updateModel();
}


void Rename::on_comboBox_currentIndexChanged(int /* index */)
{
    updateModel();
}

/*
 * Qt's regular expression. i.e. QRegExp is quite limited and a little bit
 * different from that of perl or python.
 * The same goes for the way of expressing newly replaced phrase.
 * So, this function and on_lineEditNew_returnPressed() function below in particular
 * would be ideal if written in python or using embedded perl.
 */
void Rename::on_lineEditOld_returnPressed()
{
    //QString escapedStr = QRegExp::escape(ui->lineEditOld->text());
    //QRegExp regEx = QRegExp(escapedStr);

    QRegExp regEx = QRegExp(ui->lineEditOld->text());
    if(regEx.isValid()){
        regEx.setMinimal(ui->chkBoxGreedy->isChecked());

        if(delegateBefore)
            delete delegateBefore;
        delegateBefore = new RegExDelegate(this, RegExDelegate::Match, regEx,  \
                                           ui->lineEditNew->text(), Qt::darkRed, Qt::white);
        ui->listBefore->setItemDelegate(delegateBefore);
        old_OK = true;
        setBtnRunEnable();

        if(!ui->lineEditNew->text().isEmpty())
            on_lineEditNew_returnPressed();

        this->focusNextChild();
    }
    else {
        QMessageBox::critical(this, tr("Error"), tr("Invalid Regular Expression!"));
        old_OK = false;
        setBtnRunEnable();
        ui->lineEditOld->selectAll();
    }
}

void Rename::on_lineEditNew_returnPressed()
{
    if(!checkFilename(ui->lineEditNew->text())){
        QMessageBox::critical(this, tr("Error"), tr("Contains possibly invalid character(s) for filename!"));
        new_OK = false;
        setBtnRunEnable();
        ui->lineEditNew->selectAll();
        return;
    }

    QRegExp regEx = QRegExp(ui->lineEditOld->text());
    if(regEx.isValid()){
        if(delegateAfter)
            delete delegateAfter;
        delegateAfter = new RegExDelegate(this, RegExDelegate::Replace, regEx,  \
                                           ui->lineEditNew->text(), Qt::darkGreen, Qt::white);
        ui->listAfter->setItemDelegate(delegateAfter);
        new_OK = true;
        setBtnRunEnable();
        this->focusNextChild();
    }
}

void Rename::on_chkBoxGreedy_stateChanged(int /* state */)
{
    on_lineEditOld_returnPressed();
}

void Rename::on_chkBoxRecursive_stateChanged(int /* state */)
{
    updateModel();
}

void Rename::on_btnFileBrowse_pressed()
{
    on_btnFileBrowse_clicked();
}

void Rename::on_btnRun_clicked()
{
    Progress dialog(this);

    int row = model.rowCount();
    for(int i=0; i<row; i++){
        QString str = model.item(i)->data(Qt::DisplayRole).toString();
        QTableWidgetItem item(str);

    }

    dialog.exec();

}
