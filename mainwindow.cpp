#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setFixedSize(QSize(600, 400));
    ui->stackedWidget->setCurrentIndex(0);

    checkSettings();
    //QSettings settings("MarekChoinski","Colorizer" );
    //settings.setValue("pref/s_useAlphaChannel", false);
    //settings.setValue("pref/s_openAfterCoding", false);

    //qDebug()<<settings.value("pref/s_openAfterCoding").toInt();
    //qDebug()<<settings.contains("pref/s_openAfterCoding");
    //settings.setValue("pref/s_openAfterCoding", 30);
    //settings.sync();
    //qDebug()<<settings.value("pref/s_openAfterCoding").toInt();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkSettings()
{
    QSettings settings("MarekChoinski","Colorizer" );

    //useAlphaChannel
    if(settings.contains("pref/s_useAlphaChannel") == false)
    {
        settings.setValue("pref/s_useAlphaChannel", false);
    }
    else
    {
        int useAlphaChannel = settings.value("pref/s_useAlphaChannel").toBool();
        if(useAlphaChannel)
        {
            ui->checkBox->setChecked(true);
        }
    }

    //openAfterCoding
    if(settings.contains("pref/s_openAfterCoding") == false)
    {
        settings.setValue("pref/s_openAfterCoding", false);
    }
    else
    {
        int openAfterCoding = settings.value("pref/s_openAfterCoding").toBool();
        if(openAfterCoding)
        {
            ui->checkBox_2->setChecked(true);
        }
    }


}


void MainWindow::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                QDir::currentPath() ,
                                                tr("Text files to encode (*.txt);"));
    if(!fileName.isEmpty())
    {
       Encode encode(fileName);
    }




}

void MainWindow::on_pushButton_pressed()
{
        srand( time( NULL ) );

        int r = ( std::rand() % 255 );
        int g = ( std::rand() % 255 );
        int b = ( std::rand() % 255 );

        ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                        "background-color: rgb("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+");"
                                        "color: black;"
                                        "font: 75 18pt 'HelveticaNeueLT Std';"
                                        "border-style: solid;"
                                        "border-width: 5px;"
                                        "border-color:black;}");

        ui->label->setPixmap(QPixmap(":/logos/logo_glitch.png"));

}

void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("QPushButton#pushButton{"
                                    "background-color: white;"
                                    "color: black;"
                                    "font: 75 18pt 'HelveticaNeueLT Std';"
                                    "border-style: solid;"
                                    "border-width: 5px;"
                                    "border-color:black;}"

                                    "QPushButton#pushButton:hover{"
                                    "background-color: rgba(150, 150, 150, 128);}");

    ui->label->setPixmap(QPixmap(":/logos/logo_normal.png"));
}



void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                QDir::currentPath() ,
                                                tr("Images to decode (*.png)"));
    if(!fileName.isEmpty())
    {
        Decode decode(fileName);
    }
}

void MainWindow::on_pushButton_2_pressed()
{
        srand( time( NULL ) );

        int r = ( std::rand() % 255 );
        int g = ( std::rand() % 255 );
        int b = ( std::rand() % 255 );

        ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                        "background-color: rgb("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+");"
                                        "color: black;"
                                        "font: 75 18pt 'HelveticaNeueLT Std';"
                                        "border-style: solid;"
                                        "border-width: 5px;"
                                        "border-color:black;}");

        ui->label->setPixmap(QPixmap(":/logos/logo_glitch.png"));
}

void MainWindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                    "background-color: white;"
                                    "color: black;"
                                    "font: 75 18pt 'HelveticaNeueLT Std';"
                                    "border-style: solid;"
                                    "border-width: 5px;"
                                    "border-color:black;}"

                                    "QPushButton#pushButton_2:hover{"
                                    "background-color: rgba(150, 150, 150, 128);}");

    ui->label->setPixmap(QPixmap(":/logos/logo_normal.png"));
}

void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_settingsButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_settingsButton_pressed()
{
    QPixmap pixmap(":/logos/question_mark_rotated.png");
    QIcon ButtonIcon(pixmap);
    ui->settingsButton->setIcon(ButtonIcon);
    //button->setIconSize(qSize(40,40));
}

void MainWindow::on_settingsButton_released()
{
    QPixmap pixmap(":/logos/question_mark.png");
    QIcon ButtonIcon(pixmap);
    ui->settingsButton->setIcon(ButtonIcon);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    QSettings settings("MarekChoinski", "Colorizer");

    //settings.setValue("pref/s_useAlphaChannel", 5);
    //settings.sync();

    if(ui->checkBox->isChecked())
        settings.setValue("pref/s_useAlphaChannel", true);
    else
        settings.setValue("pref/s_useAlphaChannel", false);

    settings.sync();

    qDebug()<<settings.value("pref/s_useAlphaChannel").toBool();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    QSettings settings("MarekChoinski", "Colorizer");

    if(ui->checkBox_2->isChecked())
        settings.setValue("pref/s_openAfterCoding", true);
    else
        settings.setValue("pref/s_openAfterCoding", false);

    settings.sync();

    qDebug()<<settings.value("pref/s_openAfterCoding").toBool();
}
