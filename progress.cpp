#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);

    initTableWidget();
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
#if QT_VERSION >= 0x05000
    header->setSectionResizeMode(header->logicalIndex(0), QHeaderView::Stretch);
#else
    headerr->setResizeMode(header->logicalIndex(0), QHeaderView::Stretch);
#endif
    // make not editable
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // hide grid
    //ui->tableWidget->setShowGrid(false);
}

void Progress::setUpProgressBar(int maxStep)
{
    ui->progressBar->setRange(0, maxStep);
}

void Progress::updateProgressBar(int currentStep)
{
    ui->progressBar->setValue(currentStep);
}

void Progress::addItem(QString &fileName)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);    
    ui->tableWidget->setItem(row, 0, (new QTableWidgetItem(fileName)));
}

void Progress::addResult(QString result, QColor color)
{
    int row = ui->tableWidget->rowCount() -1;
    QTableWidgetItem *item = new QTableWidgetItem(result);
    item->setTextAlignment(Qt::AlignCenter);
    item->setForeground(QBrush(color));
    ui->tableWidget->setItem(row, 1, item);
}

void Progress::on_btnOK_clicked()
{
    close();
}

void Progress::closeEvent(QCloseEvent *event)
{
    ui->tableWidget->setRowCount(0);
    ui->progressBar->reset();
    event->accept();
}

