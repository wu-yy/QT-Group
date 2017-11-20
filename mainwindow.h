#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_Edit_cursorPositionChanged(int arg1, int arg2);

    void on_Start_clicked();

    void on_actionPriori_2_triggered();

    void on_SaveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
