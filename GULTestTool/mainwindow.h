#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using IFList = QList<QString>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showInfomationdlg(const QString &title, const QString &content); // 显示信息提示框

public Q_SLOTS:
    // 路径
    void OpenFileDlg();
    void OpenFolderDlg();
    // 执行用例
    void ExecTest();
    void slot_FileToBin();
public: // 界面功能
    // 初始化
    void InitializeUI();
    void InitTestIFs();
    void InitComboBox();
    void InitConnect();

private:
    Ui::MainWindow *ui;
private: // 界面成员
    IFList mIFs;
    QString dataFilePath;
    QString resultFolderPath;
};
#endif // MAINWINDOW_H
