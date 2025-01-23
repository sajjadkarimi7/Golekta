#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QShortcut>
#include<qtimer.h>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(on_LoginButton_pressed()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(makecheckerok()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(on_SignUpButton_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT(help()));
    ui->setupUi(this);
    ui->SuggestionList->hide();
    generateCaptcha();

}
void MainWindow::generateCaptcha(){
    time_t t;
    int n=7;
    srand((unsigned)time(&t));
    QString required_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    captcha = "";
    while(n--)
        captcha.push_back(required_chars[rand()%62]);
    ui->Captcha->setText(captcha);



}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginButton_pressed()
{
    if(captcha!=ui->Recaptcha->text()){
        ui->Recaptcha->setStyleSheet("background-color:rgba(0,0,0,0);"
                                     "border:none;"
                                     "border-bottom: 2px solid rgba(255,0,0,200);"
                                     "color:rgba(0,0,0,240);"
                                     "padding-bottom:7px;");
        ui->Recaptcha->setText("");
    }
    else if(ui->passwordinput->text()=="1234"&&ui->usernameinput->text()=="admin"){

    }
    else if(ui->passwordinput->text()==""&&ui->usernameinput->text()==""){}
    else{
        ui->passwordinput->setStyleSheet("background-color:rgba(0,0,0,0);"
                                     "border:none;"
                                     "border-bottom: 2px solid rgba(255,0,0,200);"
                                     "color:rgba(0,0,0,240);"
                                     "padding-bottom:7px;");
        ui->usernameinput->setStyleSheet("background-color:rgba(0,0,0,0);"
                                         "border:none;"
                                         "border-bottom: 2px solid rgba(255,0,0,200);"
                                         "color:rgba(0,0,0,240);"
                                         "padding-bottom:7px;");

        ui->Recaptcha->setText("");

    }
    generateCaptcha();
    ui->Recaptcha->setText("");
}

