#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConstantDef.h"
#include "TestFunc.h"

#include <QFileDialog>
#include <QMessageBox>       // for show error message
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

void MainWindow::showInfomationdlg(const QString &title, const QString &content)
{
    QString defaultTitle("Tips Info");
    if (!title.isEmpty()) {
        defaultTitle = title;
    }
    QMessageBox::information(this, defaultTitle, content, QMessageBox::Ok);
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
    mIFs.push_back(QString::fromLocal8Bit("GPS时间格式化"));
    mIFs.push_back(QString::fromLocal8Bit("GLONASS时间格式化"));
    mIFs.push_back(QString::fromLocal8Bit("Galileo时间格式化"));
    mIFs.push_back(QString::fromLocal8Bit("北斗时间格式化"));
    mIFs.push_back(QString::fromLocal8Bit("GPS时间转为UTC时间"));
    mIFs.push_back(QString::fromLocal8Bit("GLONASS时间转为UTC时间"));
    mIFs.push_back(QString::fromLocal8Bit("GALILEO时间转为UTC时间"));
    mIFs.push_back(QString::fromLocal8Bit("北斗时间转为UTC时间"));
    mIFs.push_back(QString::fromLocal8Bit("UTC时间转为GPS时间"));
    mIFs.push_back(QString::fromLocal8Bit("UTC时间转为GLONASS时间"));
    mIFs.push_back(QString::fromLocal8Bit("UTC时间转为GALILEO时间"));
    mIFs.push_back(QString::fromLocal8Bit("UTC时间转为北斗时间"));
    mIFs.push_back(QString::fromLocal8Bit("北斗时间转为GPS时间"));
    mIFs.push_back(QString::fromLocal8Bit("GLONASS时间转为GPS时间"));
    mIFs.push_back(QString::fromLocal8Bit("GALILEO时间转为GPS时间"));
    mIFs.push_back(QString::fromLocal8Bit("GPS时间转为北斗时间"));
    mIFs.push_back(QString::fromLocal8Bit("GPS时间转为GLONASS时间"));
    mIFs.push_back(QString::fromLocal8Bit("GPS时间转为GALILEO时间"));
    mIFs.push_back(QString::fromLocal8Bit("计算卫星钟差（GLONASS）"));
    mIFs.push_back(QString::fromLocal8Bit("计算卫星钟差（非GLONASS）"));
    mIFs.push_back(QString::fromLocal8Bit("计算卫星位置（非GLONASS）"));
    mIFs.push_back(QString::fromLocal8Bit("计算卫星位置（GLONASS）"));
    mIFs.push_back(QString::fromLocal8Bit("大地坐标转换为空间直角坐标"));
    mIFs.push_back(QString::fromLocal8Bit("空间直角坐标转换为大地坐标"));
    mIFs.push_back(QString::fromLocal8Bit("空间直角坐标转换为站心坐标"));
    mIFs.push_back(QString::fromLocal8Bit("站心坐标转换为空间直角坐标"));
    mIFs.push_back(QString::fromLocal8Bit("度转换为弧度"));
    mIFs.push_back(QString::fromLocal8Bit("弧度转换为度"));
    mIFs.push_back(QString::fromLocal8Bit("角度以度格式化输出"));
    mIFs.push_back(QString::fromLocal8Bit("角度以度分秒格式化输出"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵加法"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵减法"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵乘法"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵转置"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵求逆"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵增加行列"));
    mIFs.push_back(QString::fromLocal8Bit("矩阵减少行列"));
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
    QString title(QString::fromLocal8Bit("请选择一个测试数据文件"));
    QString fileFilter = tr("All Files(*.*);;JSon Files(*.json);;Text Files(*.txt)");
    QString defaultFileFileter = tr("Text Files(*.txt)");
    dataFilePath = QFileDialog::getOpenFileName(nullptr, title, ".", fileFilter, &defaultFileFileter);
    if (dataFilePath.isEmpty()) {
        return;
    }
    ui->txtTestDataPath->setText(dataFilePath);
}

void MainWindow::OpenFolderDlg()
{
    QString title(QString::fromLocal8Bit("请选择测试结果要保存的位置"));
    QString startIndexPos("");
    resultFolderPath = QFileDialog::getExistingDirectory(nullptr, title, startIndexPos, QFileDialog::ShowDirsOnly);
    if (resultFolderPath.isEmpty()) {
        return;
    }
    ui->txtResultPath->setText(resultFolderPath);
}

void MainWindow::ExecTest()
{
    ui->txtRtkResult->text().clear();
    ui->txtGULResult->text().clear();

    QString testData;
    QString result;
    bool dataType = false;
    int funcIdx = ui->comboTestIF->currentIndex();
    if (funcIdx == 0) {
        return;
    } else if (funcIdx >= 19 && funcIdx <= 22) { // 星历运算, 源数据由文件和时间组成
        if (ui->txtTestDataPath->text().isEmpty() || ui->txtSimpleTestData->text().isEmpty()) {
            return;
        }
        testData = ui->txtTestDataPath->text() + SEMICOLON + ui->txtSimpleTestData->text();
        result = QString("");
    } else if (funcIdx >= 31 && funcIdx <= 37) { // 矩阵运算，源数据由两个文件组成
        if (ui->txtTestDataPath->text().isEmpty() || ui->txtResultPath->text().isEmpty()) {
            return;
        }
        testData = ui->txtTestDataPath->text() + SEMICOLON + ui->txtResultPath->text();
        result = QString("");
        dataType = true;
    } else { // 简单数据
        if (ui->txtSimpleTestData->text().isEmpty()) {
            return;
        }
        testData = ui->txtSimpleTestData->text();
    }

    // 执行测试用例
    CTestFunc testFunc(this);
    testFunc.ExecuteTest(testData, ui->comboTestIF->currentIndex(), result);

    // 输出测试结果
    // 非文件的输出结果，以";"隔开，第一个字段存为Rtk接口的结果，第二个字段为GUL接口的结果
    // 如果有接口未实现或不存在，则显示为null
    if (dataType) {
        return;
    }
    QStringList rets = result.split(SEMICOLON);
    if (rets.count() != 2) {
        return;
    }
    ui->txtRtkResult->setText(rets[0]);
    ui->txtGULResult->setText(rets[1]);
}

