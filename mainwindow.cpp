#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), clientSocket(nullptr),
    serverIp("192.168.0.3"), serverPort(1234)  // Default to the local IP for testing
{
    ui->setupUi(this);
    setupUI();
    connectToServer();

    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    statusLabel = new QLabel("Disconnected", this);
    mainLayout->addWidget(statusLabel);

    messageLog = new QTextEdit(this);
    messageLog->setReadOnly(true);
    mainLayout->addWidget(messageLog);

    messageEntry = new QLineEdit(this);
    mainLayout->addWidget(messageEntry);

    sendButton = new QPushButton("Send", this);
    mainLayout->addWidget(sendButton);

    connectButton = new QPushButton("Connect", this);
    mainLayout->addWidget(connectButton);

    serverIpInput = new QLineEdit(this); // Text input for server IP
    serverIpInput->setPlaceholderText("Enter server IP (Public or Local)");
    mainLayout->addWidget(serverIpInput);

    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);

    centralWidget->setLayout(mainLayout);
}

void MainWindow::connectToServer()
{
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, &QTcpSocket::connected, [this]() {
        statusLabel->setText("Connected to Server");
        messageLog->append("Connected to Server...");
    });

    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);

    clientSocket->connectToHost(QHostAddress(serverIp), serverPort);
}

void MainWindow::onConnectButtonClicked()
{
    QString serverIp = "192.168.0.4";
    if (serverIp.isEmpty()) {
        statusLabel->setText("Server IP is required");
        return;
    }

    if (clientSocket->state() != QTcpSocket::ConnectedState) {
        clientSocket->connectToHost(QHostAddress(serverIp), serverPort);
    } else {
        statusLabel->setText("Already connected");
    }
}

void MainWindow::onSendButtonClicked()
{
    QString message = messageEntry->text();
    if (!message.isEmpty() && clientSocket->state() == QTcpSocket::ConnectedState) {
        clientSocket->write(message.toUtf8());
        messageLog->append("You: " + message);
        messageEntry->clear();
    }
}

void MainWindow::onReadyRead()
{
    QByteArray data = clientSocket->readAll();
    messageLog->append("Server: " + QString::fromUtf8(data));
}

void MainWindow::onDisconnected()
{
    statusLabel->setText("Disconnected from Server");
    messageLog->append("Disconnected from Server");
}
