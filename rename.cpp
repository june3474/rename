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

    Dir_OK = true;
    RegEx_OK = false;
    NewPhrase_OK = false;
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
    ui->btnRun->setEnabled(model.rowCount() && Dir_OK && RegEx_OK && NewPhrase_OK);
}

void Rename::on_lineEditDir_focusOut()
{
    if(ui->lineEditDir->text() == oldDir)
        return;

    QString path = QDir::cleanPath(QDir::toNativeSeparators(ui->lineEditDir->text()));
    oldDir = path;
    QFileInfo info = QFileInfo(path);

    if(info.isDir()){
        ui->lineEditDir->setText(path);
        ui->lineEditDir->setIcon(MyLineEdit::OK);
        Dir_OK = true;

        updateModel();
    }
    else {
        QMessageBox::critical(this, tr("Error"), tr("Invalid Directory!"));
        model.clear();
        ui->lineEditDir->setIcon(MyLineEdit::ERROR);
        Dir_OK = false;
    }
    setBtnRunEnable();
}

void Rename::on_lineEditDir_returnPressed()
{
    // QMessageBox causes focusOut signal
    ui->lineEditDir->blockSignals(true);

    on_lineEditDir_focusOut();
    if(Dir_OK){
        this->focusNextChild();
    }
    else {
        ui->lineEditDir->selectAll();
    }

    ui->lineEditDir->blockSignals(false);
}

void Rename::on_btnFileBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose the directory", ui->lineEditDir->text());
    if(dir.isEmpty())
        dir = oldDir;
    ui->lineEditDir->setText(dir);
    on_lineEditDir_focusOut();
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

    if(ui->lineEditOld->text() == oldRegEx)
        return;

    oldRegEx = ui->lineEditOld->text();
    QRegExp regEx = QRegExp(oldRegEx);
    regEx.setMinimal(!ui->chkBoxGreedy->isChecked());

    if(regEx.isValid()){
        delegateBefore->setRegEx(regEx);
        delegateAfter->setRegEx(regEx);

        // empty regEx is valid too.
        if(ui->lineEditOld->text().isEmpty()){
            ui->lineEditOld->setIcon(MyLineEdit::DEFAULT);
            RegEx_OK = false;
        }
        else {
            ui->lineEditOld->setIcon(MyLineEdit::OK);
            RegEx_OK = true;
        }
    } else{ // invalid regular expression
        delegateBefore->setRegEx(QRegExp());
        delegateAfter->setRegEx(QRegExp());
        QMessageBox::critical(this, tr("Error"), tr("Invalid Regular Expression!"));
        ui->lineEditOld->setIcon(MyLineEdit::ERROR);
        RegEx_OK = false;
    }
    setBtnRunEnable();
}

void Rename::on_lineEditOld_returnPressed()
{
    ui->lineEditOld->blockSignals(true);

    on_lineEditOld_focusOut();
    if(RegEx_OK){
        this->focusNextChild();
    } else{
        ui->lineEditOld->selectAll();
    }

    ui->lineEditOld->blockSignals(false);
}

void Rename::on_lineEditNew_focusOut()
{
    if(ui->lineEditNew->text() == oldNewPhrase)
        return;

    oldNewPhrase = ui->lineEditNew->text();

    if(checkFilename(ui->lineEditNew->text())){
        delegateAfter->setAfter(ui->lineEditNew->text());

        if(ui->lineEditNew->text().isEmpty()){
            ui->lineEditNew->setIcon(MyLineEdit::DEFAULT);
            NewPhrase_OK = false;
        }
        else {
            ui->lineEditNew->setIcon(MyLineEdit::OK);
            NewPhrase_OK = true;
        }
    } else { // invalid file name
        delegateAfter->setAfter(QString());
        ui->lineEditNew->setIcon(MyLineEdit::ERROR);
        NewPhrase_OK = false;
        QMessageBox::critical(this, tr("Error"), tr("Contains possibly invalid character(s) for a filename!"));
    }
    setBtnRunEnable();
}

void Rename::on_lineEditNew_returnPressed()
{
    ui->lineEditNew->blockSignals(true);

    on_lineEditNew_focusOut();
    if(NewPhrase_OK){
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
