/*******************************************************
 * Author: dks
 * Date: 13 Mar, 2017
 * Desc: file renamming tool using a regular expression
 *******************************************************/

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QtDebug>

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
    old_OK = false;
    new_OK = false;
    dialog = 0;

    init();

    // sync two listview's scrollbars.
    // Although an unnecessay sync occurs, it's just once(think about it!). not infinite loop.
    QObject::connect(ui->listBefore->verticalScrollBar(), SIGNAL(valueChanged(int)), \
                     ui->listAfter->verticalScrollBar(), SLOT(setValue(int)));
    QObject::connect(ui->listAfter->verticalScrollBar(), SIGNAL(valueChanged(int)), \
                     ui->listBefore->verticalScrollBar(), SLOT(setValue(int)));
}

Rename::~Rename()
{
    delete ui;
    delete delegateBefore;
    delete delegateAfter;
    if(dialog){
        delete dialog;
    }
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
    delegateBefore = new RegExDelegate(ui->listBefore, RegExDelegate::Match, Qt::darkRed);
    ui->listBefore->setItemDelegate(delegateBefore);

    ui->listAfter->setModel(&model);
    delegateAfter = new RegExDelegate(ui->listAfter, RegExDelegate::Replace);
    ui->listAfter->setItemDelegate(delegateAfter);    
}

void Rename::updateModel()
{
    model.clear();
    QFileInfoList fileInfoList = getFileInfoList(ui->lineEditDir->text(), \
                                                 ui->chkBoxRecursive->isChecked());

    foreach(QFileInfo fileInfo, fileInfoList){
        // file name at DisplayRole
        QStandardItem *item = new QStandardItem(fileInfo.fileName());
        // file name with full path at ToolTiprole
        item->setData(fileInfo.canonicalFilePath(), Qt::ToolTipRole);
        // file path excluding file name at UserRole. Not ends with '/'
        item->setData(fileInfo.canonicalPath(), Qt::UserRole);

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

// very primitive filename validator
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

void Rename::on_lineEditDir_focusOut()
{
    // prevent showing MessageBox when clicking btnFileBrowse
    if(ui->btnFileBrowse->hasFocus())
        return;

    QString path = QDir::cleanPath(QDir::toNativeSeparators(ui->lineEditDir->text()));
    QFileInfo info = QFileInfo(path);

    if(info.isDir()){
        ui->lineEditDir->setText(path);
        ui->lineEditDir->setIcon(MyLineEdit::OK);
        dir_OK = true;

        updateModel();
    }
    else {
        QMessageBox::critical(this, tr("Error"), tr("Invalid Directory!"));
        model.clear();
        ui->lineEditDir->setIcon(MyLineEdit::ERROR);
        dir_OK = false;
        setBtnRunEnable();
    }
}

void Rename::on_lineEditDir_returnPressed()
{
    // QMessageBox causes focusOut signal
    ui->lineEditDir->blockSignals(true);

    on_lineEditDir_focusOut();
    if(dir_OK){
        this->focusNextChild();
    }
    else {
        ui->lineEditDir->selectAll();
    }

    ui->lineEditDir->blockSignals(false);
}

void Rename::on_btnFileBrowse_clicked()
{
    QString oldDir = ui->lineEditDir->text();
    QString dir = QFileDialog::getExistingDirectory(this, "Choose the directory", ui->lineEditDir->text());
    if(dir.isEmpty())
        dir = oldDir;
    ui->lineEditDir->setIcon(MyLineEdit::OK);
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
void Rename::on_lineEditOld_focusOut()
{
    //QString escapedStr = QRegExp::escape(ui->lineEditOld->text());
    //QRegExp regEx = QRegExp(escapedStr);

    QRegExp regEx = QRegExp(ui->lineEditOld->text());
    regEx.setMinimal(!ui->chkBoxGreedy->isChecked());

    if(regEx.isValid()){
        // empty regEx is valid too.
        if(ui->lineEditOld->text().isEmpty()){
            ui->lineEditOld->setIcon(MyLineEdit::DEFAULT);
            old_OK = false;
        }
        else {
            ui->lineEditOld->setIcon(MyLineEdit::OK);
            old_OK = true;
        }
        setBtnRunEnable();
        delegateBefore->setRegEx(regEx);
        delegateBefore->refresh();        
        delegateAfter->setRegEx(regEx);
        if(!ui->lineEditNew->text().isEmpty())
            delegateAfter->refresh();
    } else{ // invalid regular expression
        QMessageBox::critical(this, tr("Error"), tr("Invalid Regular Expression!"));
        ui->lineEditOld->setIcon(MyLineEdit::ERROR);
        old_OK = false;
        setBtnRunEnable();
    }
}

void Rename::on_lineEditOld_returnPressed()
{
    ui->lineEditOld->blockSignals(true);

    on_lineEditOld_focusOut();
    if(old_OK){
        this->focusNextChild();
    } else{
        ui->lineEditOld->selectAll();
    }

    ui->lineEditOld->blockSignals(false);
}

void Rename::on_lineEditNew_focusOut()
{
    if(checkFilename(ui->lineEditNew->text())){
        if(ui->lineEditNew->text().isEmpty()){
            ui->lineEditNew->setIcon(MyLineEdit::DEFAULT);
            new_OK = false;
        }
        else {
            ui->lineEditNew->setIcon(MyLineEdit::OK);
            new_OK = true;
        }
        setBtnRunEnable();
        delegateAfter->setAfter(ui->lineEditNew->text());
        QRegExp regEx = QRegExp(ui->lineEditOld->text());
        if(regEx.isValid()){
            regEx.setMinimal(!ui->chkBoxGreedy->isChecked());
            delegateAfter->refresh();
        }
    } else { // invalid file name
        ui->lineEditNew->setIcon(MyLineEdit::ERROR);
        new_OK = false;
        setBtnRunEnable();
        QMessageBox::critical(this, tr("Error"), tr("Contains possibly invalid character(s) for a filename!"));
    }
}

void Rename::on_lineEditNew_returnPressed()
{
    ui->lineEditNew->blockSignals(true);

    on_lineEditNew_focusOut();
    if(new_OK){
        this->focusNextChild();
    } else {
        ui->lineEditNew->selectAll();
    }

    ui->lineEditNew->blockSignals(false);
}

void Rename::on_chkBoxGreedy_stateChanged(int /* state */)
{
    on_lineEditOld_focusOut();
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
    if(!dialog)
        dialog = new Progress(this);
    dialog->setModal(true);
    dialog->show();

    int count = model.rowCount();
    dialog->setUpProgressBar(count);
    for(int i=0; i<count; i++){
        QString oldNameWithPath = model.item(i)->data(Qt::ToolTipRole).toString();
        QString oldName = model.item(i)->data(Qt::DisplayRole).toString();
        QString newName = oldName;
        newName.replace(QRegExp(ui->lineEditOld->text()), \
                                          ui->lineEditNew->text());
        QString newNameWithPath = model.item(i)->data(Qt::UserRole).toString() + \
                                  QDir::separator() + newName;
        QString displayStr = oldName + " -> " + newName;

        dialog->addItem(displayStr);
        bool result = true;
        if(oldName != newName){
            QFile f(oldNameWithPath);
            result = f.rename(newNameWithPath);
        }
        dialog->addResult(result);
        dialog->updateProgressBar(i+1);
        qApp->processEvents();
    }
}
