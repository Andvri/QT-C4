#ifndef TABLE_H
#define TABLE_H

#define W 1024
#define H 768
#define PIXEL 96

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QRectF>
#include <iostream>
#include <QtTest/QTest>
#include <QStyleOptionGraphicsItem>
#include <QFontDatabase>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "logicengine.h"


class Table : public QGraphicsItem{

public:

    int Saltos [7][2]={	{-1,-1}, {1,1}, {0,-1}, {0,1}, {1,-1}, {-1,1}, {1,0} };

    int gridTable[6][7];
    int gridHover[7];
    static int player1;
    static int player2;
    int yOffSet = 96;
    int move;

    QGraphicsScene *tableScene;
    QGraphicsScene *auxScene;

    QLabel *turn1, *p1Win;
    QLabel *turn2, *p2Win;
    QLabel *draw;

      Table(QGraphicsItem *parent = 0);
    Table(QGraphicsScene *parentScene, QGraphicsScene *auxScene, QGraphicsItem *parent = 0);

    bool mousePressed;
    bool turn, endGame;
    bool winP1, winP2;

    void resetHover();
    void paintPlayer(int j, int i,int currPlayer, QPainter *painter, QPen &pen);
    void paintTable(int j, int i, QPainter *painter, QPen &pen);
    void paintHover(int j, int i, QPainter *painter, QPen &pen);

    int  SeguirDireccion(int posX,int posY,int bus,int SX,int SY,int cant=1);
    bool comprobarVictoria(int bus,int cx,int cy);
    bool checkDraw();
    void resetElements();

    int checkTerminalState(int player);
    void add(int j, int player);
    void remove(int j);
    bool canPlace(int j);
    int staticEvaluator();
    int checkSpaces(int col, int player);
    //Minimax procedure
    int max(int depth);
    int min(int depth);

    //Must Override to Instantiate
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:

    //MouseEvents
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void setPlayerInGrid(int currPlayer, int x, int &y);

};

#endif // TABLE_H
