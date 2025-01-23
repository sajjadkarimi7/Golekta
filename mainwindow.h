#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectButtonClicked();
    void onSendButtonClicked();
    void onReadyRead();
    void onDisconnected();

private:
    Ui::MainWindow *ui;
    QTcpSocket *clientSocket;
    QString serverIp;
    quint16 serverPort;
    QLabel *statusLabel;
    QLineEdit *messageEntry;
    QTextEdit *messageLog;
    QPushButton *sendButton;
    QPushButton *connectButton;
    QLineEdit *serverIpInput; // New field to input server IP
    void setupUI();
    void connectToServer();
};

#endif // MAINWINDOW_H
