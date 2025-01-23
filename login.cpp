#include "login.h"

#include "ui_login.h"
#include<fstream>
//#include<about.h>
#include<iostream>
#include<QString>
#include<QTimer>
#include<QMessageBox>
#include<QShortcut>
#include<QDesktopServices>
#include <QMovie>
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{

    //shortcuts
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(on_LoginButton_pressed()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(makecheckerok()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(on_SignUpButton_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT(help()));



    ui->setupUi(this);

        exit(1);


    QTimer *timer=new QTimer;

    timer->start(1000);

    ui->Captcha->hide();
    ui->Recaptcha->hide();
    ui->RECAPTCHAOK->hide();


      //  int i=0;
}

Login::~Login()
{

    delete ui;
}
void Login::mousePressEvent(QMouseEvent *event)
{
    mouseClickMove_X = event->x();
    mouseClickMove_Y = event->y();
}

void Login::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX()-mouseClickMove_X,event->globalY()-mouseClickMove_Y);
}






bool Login::check_Captcha(QString &captcha, QString &user_input){
    return captcha.compare(user_input) == 0;
}
// function to generate CAPTCHA of length n
void Login::generateCaptcha(){
    time_t t;
    int n=7;
    srand((unsigned)time(&t));
    QString required_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    captcha = "";
    while(n--)
        captcha.push_back(required_chars[rand()%62]);

}
void Login::on_RECAPTCHAOK_clicked()
{
    if(ui->Recaptcha->text()==captcha){
        counts_of_login=0;
        ui->Captcha->hide();
        ui->Recaptcha->hide();
        ui->RECAPTCHAOK->hide();
    }
    else{
        generateCaptcha();
        ui->Captcha->setText(captcha);
    }
}


void Login::on_usernameinput_textChanged(const QString &arg1)
{
    counter_in_suggestionlist=0;
//    QRegExp RegExp(arg1,Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->SuggestionList->clear();
    for(auto it=users.begin();it!=users.end();it++){
        if(it->contains(arg1)){
            ui->SuggestionList->addItem(*it);
            counter_in_suggestionlist++;
        }
        if(counter_in_suggestionlist==0){
            ui->SuggestionList->hide();
        }
        else{
            ui->SuggestionList->show();
        }
    }




}


void Login::on_SuggestionList_itemDoubleClicked(QListWidgetItem *item)
{
    QString user=item->text();
    int j=0;
     for(auto it=users.begin();it!=users.end();it++){
         if(*it==user){
            break;
         }
         j++;
     }
     counter_in_suggestionlist=-1;
     ui->usernameinput->setText(user);
     ui->passwordinput->setText(passwords[j]);
     ui->SuggestionList->hide();

}


void Login::on_Seepasswordbutton_pressed()
{
    ui->passwordinput->setEchoMode(QLineEdit::Normal);
}


void Login::on_Seepasswordbutton_clicked()
{
    ui->passwordinput->setEchoMode(QLineEdit::Password);
}




void Login::on_LoginButton_pressed()
{

        generateCaptcha();
        ui->Captcha->show();
        ui->Recaptcha->show();
        ui->RECAPTCHAOK->show();
        if(counts_of_login>=4){
            ui->Recaptcha->setStyleSheet("background-color:rgba(0,0,0,0);"
                                             "border:none;"
                                             "border-bottom: 2px solid rgba(255,0,0,200);"
                                             "color:rgba(0,0,0,240);"
                                             "padding-bottom:7px;");
        }
        ui->Captcha->setText(captcha);

    }




