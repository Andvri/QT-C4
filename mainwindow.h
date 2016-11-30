#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define W 1024
#define H 768

#include <QStack>
#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QFontDatabase>
#include <QMessageBox>
#include "table.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:

    QGraphicsView *gameView, *auxView;
    QGraphicsScene *gameScene, *gameBackground;
    QGraphicsScene *auxScene;
    Table *currTable;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private slots:
    void play();
    void restart();
    void credits();
    void quit();
};



#endif // MAINWINDOW_H
