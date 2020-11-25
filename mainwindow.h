#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MyVideoCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_InitOpenCV_button_clicked();

private:
    Ui::MainWindow *ui;
    MyVideoCapture *mOpenCV_videoCapture;
};

#endif // MAINWINDOW_H
