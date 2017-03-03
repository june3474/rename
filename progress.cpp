#include "progress.h"
#include "ui_progress.h"

#include <QtDebug>

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);

    initTableWidget();

    //for(int i=0; i<5; i++)
        //addItem(new QTableWidgetItem(QString::number(i)));
}

Progress::~Progress()
{
    delete ui;
}

void Progress::initTableWidget()
{
    // set up horizontal header
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("File") << tr("Status"));

    // adjust width
    const int PADDING = 20;
    QHeaderView *header = ui->tableWidget->horizontalHeader();
    int width = ui->tableWidget->fontMetrics().width("Status") + PADDING;

    ui->tableWidget->setColumnWidth(1, width);
    header->setResizeMode(header->logicalIndex(0), QHeaderView::Stretch);

    // hide grid
}

void Progress::setUpProgressBar(int maxStep)
{
    ui->progressBar->setMaximum(maxStep);
}

void Progress::updateProgressBar(int currentStep)
{
    ui->progressBar->setValue(currentStep);
}

void Progress::addItem(QTableWidgetItem *item)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, item);
}

void Progress::on_btnOK_clicked()
{
    close();
}

