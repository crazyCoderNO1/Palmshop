/**
 * @file
 * @brief 本文件包含palmshop服务端主界面
 * @version 1.0.0.0
 * @date 2017.12.21
 * @author techeiliang
 */
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QMainWindow>
namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    /**
     * @brief 构造函数
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief 析构函数
     */
    ~MainWindow();
  protected:
    void showEvent(QShowEvent *event) override;
  private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

  private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
