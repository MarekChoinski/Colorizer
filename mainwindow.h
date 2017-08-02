#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QSettings>

//#include <random>
#include <ctime>
#include <thread>

#include "encode.hpp"
#include "decode.hpp"

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

    void on_settingsButton_clicked();

    void on_settingsButton_2_clicked();

    void on_settingsButton_pressed();

    void on_settingsButton_released();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QSettings settings;

    void checkSettings();

};

#endif // MAINWINDOW_H
