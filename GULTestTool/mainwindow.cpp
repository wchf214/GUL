#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConstantDef.h"
#include "TestFunc.h"

#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataFilePath("")
    , resultFolderPath("")
{
    ui->setupUi(this);
    InitializeUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeUI()
{
    InitConnect();

    InitTestIFs();
    InitComboBox();
}

void MainWindow::InitTestIFs()
{
    mIFs.clear();
    mIFs.push_back(ChoiceOneIF);
    mIFs.push_back("01FormatWeekSecTime");
    mIFs.push_back("02FormatStandardTime");
    mIFs.push_back("03GNSSTimeToUTCTime");
    mIFs.push_back("04GNSSTimeToUTCSecTime");
    mIFs.push_back("05UTCTimeToGNSSTime");
    mIFs.push_back("06UTCTimeToGNSSSecTime");
    mIFs.push_back("07GNSSTimeConvert");
    mIFs.push_back("08WeekSecToSec");
    mIFs.push_back("09XYZ2BLH");
    mIFs.push_back("10BLH2XYZ");
    mIFs.push_back("11XYZ2ENU");
    mIFs.push_back("12ENU2XYZ");
    mIFs.push_back("13CalcGlonassEphSatClock");
    mIFs.push_back("14CalcEphSatClock");
    mIFs.push_back("15CalcGlonassEphSatPos");
    mIFs.push_back("16CalcEphSatPos");
    mIFs.push_back("17FormatAngleByDegree");
    mIFs.push_back("18FormatAngleByDMS");
    mIFs.push_back("19Deg2Rad");
    mIFs.push_back("20DMS2Rad");
    mIFs.push_back("21Rad2Deg");
    mIFs.push_back("22Rad2DMS");
    mIFs.push_back("23MatrixAdd");
    mIFs.push_back("24MatrixSub");
    mIFs.push_back("25MatrixMul");
    mIFs.push_back("26MatrixTransposition");
    mIFs.push_back("27MatrixInverse");
    mIFs.push_back("28MatrixAddRowCol");
    mIFs.push_back("29MatrixSubRowCol");

}

void MainWindow::InitComboBox()
{
    ui->comboTestIF->clear();
    for (int idx = 0; idx < mIFs.count(); ++idx) {
        ui->comboTestIF->insertItem(idx, mIFs.at(idx));
    }
}

void MainWindow::InitConnect()
{
    connect(ui->btnTestDataPath, &QPushButton::clicked, this, &MainWindow::OpenFileDlg);
    connect(ui->btnResultPath, &QPushButton::clicked, this, &MainWindow::OpenFolderDlg);
    connect(ui->btnExecTest, &QPushButton::clicked, this, &MainWindow::ExecTest);
}

void MainWindow::OpenFileDlg()
{
    QString title("请选择一个测试数据文件");
    QString fileFilter = tr("All Files(*.*);;JSon Files(*.json);;Text Files(*.txt)");
    QString defaultFileFileter = tr("JSon Files(*.json)");
    dataFilePath = QFileDialog::getOpenFileName(nullptr, title, ".", fileFilter, &defaultFileFileter);
    if (dataFilePath.isEmpty()) {
        return;
    }
    ui->txtTestDataPath->setText(dataFilePath);
}

void MainWindow::OpenFolderDlg()
{
    QString title("请选择测试结果要保存的位置");
    QString startIndexPos("");
    resultFolderPath = QFileDialog::getExistingDirectory(nullptr, title, startIndexPos, QFileDialog::ShowDirsOnly);
    if (resultFolderPath.isEmpty()) {
        return;
    }
    ui->txtResultPath->setText(resultFolderPath);
}

void MainWindow::ExecTest()
{
    QString testData;
    QString result;
    bool dataType = false;
    int funcIdx = ui->comboTestIF->currentIndex();
    if (funcIdx == 0) {
        return;
    } else if ((funcIdx >= 13 && funcIdx <= 16) || (funcIdx >= 23 && funcIdx <=29)) { // 文件类数据
        if (!(ui->txtTestDataPath->text().isEmpty() && ui->txtResultPath->text().isEmpty())) {
            return;
        }
        testData = ui->txtTestDataPath->text();
        result = ui->txtResultPath->text();
        dataType = true;
    } else { // 简单数据
        if (ui->txtSimpleTestData->text().isEmpty()) {
            return;
        }
        testData = ui->txtSimpleTestData->text();
        ui->txtRtkResult->text().clear();
        ui->txtGULResult->text().clear();
    }

    // 执行测试用例
    CTestFunc testFunc;
    testFunc.ExecuteTest(testData, ui->comboTestIF->currentIndex(), result);

    // 输出测试结果
    // 非文件的输出结果，以";"隔开，第一个字段存为Rtk接口的结果，第二个字段为GUL接口的结果
    // 如果有接口未实现或不存在，则显示为null
    if (dataType) {
        return;
    }
    QStringList rets = result.split(";");
    if (rets.count() != 2) {
        return;
    }
    ui->txtRtkResult->setText(rets[0]);
    ui->txtGULResult->setText(rets[1]);
}

