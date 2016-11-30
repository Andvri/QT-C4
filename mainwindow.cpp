#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    this->setFixedSize(W,H);
    this->setWindowTitle("Connect 4");
    gameScene = new QGraphicsScene(0,0,PIXEL*7,H,this);
    this->gameScene->setBackgroundBrush(QBrush(Qt::black,Qt::SolidPattern));

    this->gameBackground = new QGraphicsScene(0,0,PIXEL*7,H,this);
    this->gameBackground->setBackgroundBrush(QBrush(Qt::black,Qt::SolidPattern));

    this->gameView = new QGraphicsView(this);
    this->gameView->setGeometry(QRect(0,0,PIXEL*7,H));
    this->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->gameView->setScene(this->gameBackground);
    this->gameView->setMouseTracking(true);
    this->gameView->show();

    QFontDatabase::addApplicationFont(":/Fonts/CT4 Res/Lost in Wild.ttf");
    QFontDatabase::addApplicationFont(":/Fonts/CT4 Res/osakare.ttf");

    this->auxScene = new QGraphicsScene(PIXEL*7,0,PIXEL*4,H,this);
    this->auxScene->setBackgroundBrush(QBrush(Qt::black,Qt::SolidPattern));
    this->currTable = new Table(this->gameScene,this->auxScene);


    QString family1 = QFontDatabase::applicationFontFamilies(0).at(0);
    QString family2 = QFontDatabase::applicationFontFamilies(1).at(0);

    QFont toSet1(family1), toSet2(family2);
    toSet2.setPointSize(22);

    QGraphicsTextItem *text = auxScene->addText("Connect 4");
    text->setFont(toSet1);
    text->setScale(3);
    text->setDefaultTextColor(Qt::white);
    text->setPos(PIXEL*7+20,0);

    QPushButton *play = new QPushButton("Play");
    play->setFixedSize(336,40);
    play->setStyleSheet("background-color:white;");
    play->setFont(toSet2);
    QObject::connect(play,SIGNAL(clicked()), this,SLOT(play()));

    QPushButton *restart = new QPushButton("Restart");
    restart->setFixedSize(336,40);
    restart->setStyleSheet("background-color:white;");
    restart->setFont(toSet2);
    QObject::connect(restart,SIGNAL(clicked()), this,SLOT(restart()));

    QPushButton *credits = new QPushButton("Credits");
    credits->setFixedSize(336,40);
    credits->setStyleSheet("background-color:white;");
    credits->setFont(toSet2);
    QObject::connect(credits,SIGNAL(clicked()), this,SLOT(credits()));

    QPushButton *quit = new QPushButton("Quit");
    quit->setFixedSize(336,40);
    quit->setStyleSheet("background-color:white;");
    quit->setFont(toSet2);
    QObject::connect(quit,SIGNAL(clicked()), this,SLOT(quit()));


    this->auxView = new QGraphicsView(this);
    QGridLayout *buttonGrid = new QGridLayout(this->auxView);
    buttonGrid->setAlignment(Qt::AlignBottom);
    buttonGrid->addWidget(play);
    buttonGrid->addWidget(restart);
    buttonGrid->addWidget(credits);
    buttonGrid->addWidget(quit);

    this->auxView->setGeometry(PIXEL*7,0,PIXEL*4,H);
    this->auxView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->auxView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->auxView->setScene(auxScene);
    this->auxView->show();


}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::play(){
    
    this->gameView->setScene(this->gameScene);
    
        
    
}

void MainWindow::restart(){
    this->currTable->resetElements();
    this->gameScene->update();
}

void MainWindow::credits(){

}

void MainWindow::quit(){
    QApplication::quit();
}


