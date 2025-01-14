#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("سیستم مدیریت دانشگاه");

    this->resize(420, 270);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->loginButton->setStyleSheet("background-color: blue; color: white; border-radius: 5px;");
    ui->loginButton->setCursor(Qt::PointingHandCursor);
}



MainWindow::~MainWindow()
{
    delete ui;
}
