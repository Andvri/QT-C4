#include "table.h"

int Table::player1 = 1;
int Table::player2 = 2;

Table::Table(QGraphicsItem *parent):QGraphicsItem(parent){

    this->tableScene = NULL;

}

Table::Table(QGraphicsScene *parentScene, QGraphicsScene *auxScene, QGraphicsItem *parent):QGraphicsItem(parent){

    this->setAcceptHoverEvents(true);
    this->tableScene = parentScene;
    this->tableScene->addItem(this);

    this->auxScene = auxScene;

    mousePressed = true;
    turn = true;
    endGame = false;
    winP1 = false;
    winP2 = false;

    QString family1 = QFontDatabase::applicationFontFamilies(1).at(0);
    QFont toSet1(family1);
    toSet1.setPointSize(35);

    draw = new QLabel("    Draw!     ");
    draw->setFont(toSet1);
    draw->setStyleSheet("QLabel{background-color: black; color : white;}");
    QGraphicsProxyWidget *p0Wid = this->auxScene->addWidget(draw);
    p0Wid->setPos(PIXEL*7+55,320);
    draw->hide();

    turn1 = new QLabel("   Red Turn    ");
    turn1->setFont(toSet1);
    turn1->setStyleSheet("QLabel{background-color: black; color : red;}");
    QGraphicsProxyWidget *p1Wid = this->auxScene->addWidget(turn1);
    p1Wid->setPos(PIXEL*7+30,320);
    turn1->hide();

    turn2 = new QLabel("Yellow Turn");
    turn2->setFont(toSet1);
    turn2->setStyleSheet("QLabel{background-color: black; color : yellow;}");
    QGraphicsProxyWidget *p2Wid = this->auxScene->addWidget(turn2);
    p2Wid->setPos(PIXEL*7+30,320);
    turn2->hide();

    p1Win = new QLabel("   Red Wins!   ");
    p1Win->setFont(toSet1);
    p1Win->setStyleSheet("QLabel{background-color: black; color : red;}");
    QGraphicsProxyWidget *p3Wid = this->auxScene->addWidget(p1Win);
    p3Wid->setPos(PIXEL*7+30,320);
    p1Win->hide();

    p2Win = new QLabel("Yellow Wins!");
    p2Win->setFont(toSet1);
    p2Win->setStyleSheet("QLabel{background-color: black; color : yellow;}");
    QGraphicsProxyWidget *p4Wid = this->auxScene->addWidget(p2Win);
    p4Wid->setPos(PIXEL*7+24,320);
    p2Win->hide();


    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            this->gridTable[i][j]=0;
            this->gridHover[j]=-1;
        }

    }

}

void Table::resetElements(){


    mousePressed = true;
    turn = true;
    endGame = false;
    winP1 = false;
    winP2 = false;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            this->gridTable[i][j]=0;
            this->gridHover[j]=-1;
        }

    }
    this->turn1->hide();
    this->turn2->hide();
    this->p1Win->hide();
    this->p2Win->hide();
    this->resetHover();

}

void Table::resetHover(){

    for(int i = 0; i < 7; i++)
        this->gridHover[i] = -1;

}

void Table::paintPlayer(int i, int j,int currPlayer, QPainter *painter, QPen &pen){

    if(currPlayer == player1){
    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter->setPen(pen);
    painter->drawRect(i*PIXEL, j*PIXEL+yOffSet, PIXEL, PIXEL);
    pen.setColor(Qt::red);
    pen.setWidth(5);
    QBrush brush(Qt::red);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(i*PIXEL+5, j*PIXEL+yOffSet+5, PIXEL-10, PIXEL-10);
    }

    if(currPlayer == player2){
    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter->setPen(pen);
    painter->drawRect(i*PIXEL, j*PIXEL+yOffSet, PIXEL, PIXEL);
    pen.setColor(Qt::yellow);
    pen.setWidth(5);
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(i*PIXEL+5, j*PIXEL+yOffSet+5, PIXEL-10, PIXEL-10);
    }


}

void Table::paintTable(int i, int j,QPainter *painter, QPen &pen){

    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter->setPen(pen);
    painter->drawRect(i*PIXEL,j*PIXEL+yOffSet, PIXEL,PIXEL);
    painter->drawEllipse(i*PIXEL,j*PIXEL+yOffSet, PIXEL,PIXEL);

}

void Table::paintHover(int j,int i, QPainter *painter, QPen &pen){

    Q_UNUSED(i);

    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter->setPen(pen);

    QRectF rect = QRectF(j*PIXEL+PIXEL/4, PIXEL/4, PIXEL/2, PIXEL/2);
    QPainterPath path;

    path.moveTo(rect.left() + (rect.width() / 2), rect.bottom());
    path.lineTo(rect.topLeft());
    path.lineTo(rect.topRight());
    path.lineTo(rect.left() + (rect.width() / 2), rect.bottom());

    if(turn)
    painter->fillPath(path, QBrush(QColor ("red")));
    else
    painter->fillPath(path, QBrush(QColor ("yellow")));
}

int Table::SeguirDireccion(int posX, int posY, int bus, int SX, int SY, int cant){

    int newX=posX+SX, newY=posY+SY;

        if(  (newX >=0) && (newX <6) && (newY >=0) && (newY <7) ){

            if(this->gridTable[newX][newY]==bus){
               if(cant==3){
                   return 1;
               }else{
                   return 1+ SeguirDireccion(newX,newY,bus,SX,SY,cant+1);
               }
            }

        }

     return 0;

}

bool Table::comprobarVictoria(int bus, int cx, int cy){

    int Caminos=0;
    int ru=0;
        qDebug() << "X:" << cx << "Y:" << cy;
        do{

            if(Caminos%2==0)
            ru=1;

            ru+=SeguirDireccion(cx,cy,bus,Saltos[Caminos][0],Saltos[Caminos][1]);

            if(ru>=4)
            return true;

            Caminos++;

        }while( (Caminos<6)  );

        ru=1;
        ru+=SeguirDireccion(cx,cy,bus,Saltos[6][0],Saltos[6][1]);

        if(ru>=4)
        return true;

        return false;

}

bool Table::checkDraw(){

    int *aux;
    aux = this->gridTable[0];
    bool swi = true;

    for(int i = 0; i < 7; i++){
        if(aux[i] == 0){
            swi = false;
            break;
        }

    }

    return swi;

}



void Table::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::white);

    if(!endGame){
        if(turn){
            turn1->show();
            turn2->hide();
        }else{
            turn2->show();
            turn1->hide();
        }
    }else{
        turn1->hide();
        turn2->hide();
    }


    for(int i = 0; i < 6; i++){

        for(int j = 0;j < 7;j++){

            painter->setBrush(Qt::NoBrush);

            if(this->gridTable[i][j] == player1){
                this->paintPlayer(j,i,player1,painter,pen);
            }

            if(this->gridTable[i][j] == player2){
                this->paintPlayer(j,i,player2,painter,pen);
            }

            if(this->gridTable[i][j] == 0){
                this->paintTable(j,i,painter,pen);
            }

            if(this->gridHover[j] == 0){
                this->paintHover(j,i,painter,pen);
            }

        }

    }



}

void Table::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(mousePressed && !endGame){// start main if

    int x = (int) event->pos().x()/(PIXEL);
    int y = (int) (event->pos().y()+yOffSet)/(PIXEL)-2;
    qDebug() << "I>" << y << "J>" << x;

    mousePressed = false;

        turn = true;
        this->setPlayerInGrid(player1,x,y);

            if(this->comprobarVictoria(player1,y,x)){
                qDebug() << "Player 1 Victory!";
                this->winP1 = true;
                this->p1Win->show();
                this->resetHover();
                this->update();
                this->endGame = true;
            }else if(this->checkDraw()){
                qDebug() << "Draw!";
                this->draw->show();
                this->resetHover();
                this->update();
                this->endGame = true;
            }
        

        turn = false;
        if(!winP1){
        max(4);
        this->setPlayerInGrid(player2,move,y);

        if(this->comprobarVictoria(player2,y,move)){
            qDebug() << "Player 2 Victory!";
            this->winP2 = true;
            this->p2Win->show();
            this->resetHover();
            this->update();
            this->endGame = true;
        }else if(this->checkDraw()){
            qDebug() << "Draw!";
            this->draw->show();
            this->resetHover();
            this->update();
            this->endGame = true;
        }
        }
        turn = true;
        update();

   /*     QTextStream aux(stdout, QIODevice::WriteOnly);

        for(int i = 0; i < 6; i++){

            for(int j = 0;j < 7;j++){
                aux << this->gridTable[i][j] << ' ';
            }

            aux << '\n';

        }

        aux << '\n';*/

   }// end main if

}

void Table::hoverMoveEvent(QGraphicsSceneHoverEvent *event){

   // QGraphicsItem::hoverMoveEvent(event);

    int x = (int) event->pos().x()/(PIXEL);

   // qDebug() << "J>" << x;

    if(!endGame){

        this->gridHover[x] = 0;
        int pJ = x;
        int nJ = x;

        if(x-1 >= 0){
            while(pJ-1 >= 0){
            this->gridHover[pJ-1] = -1;
            pJ--;
            }
        }
        if(x+1 < 7){
            while(nJ+1 < 7){
            this->gridHover[nJ+1] = -1;
            nJ++;
            }
        }

        this->update();

    }

}

void Table::setPlayerInGrid(int currPlayer, int x, int &y){

    Q_UNUSED(y);

    for(int j = 0; j < 6; j++){

            if(j-1 >= 0){

                this->gridTable[j-1][x]=0;
                this->update();
                QTest::qWait(45);

            }

            if(j == 0 && (this->gridTable[j+1][x] == player1 || this->gridTable[j+1][x] == player2) ){

                if(this->gridTable[j][x] != player1 && this->gridTable[j][x] != player2){
                    this->gridTable[j][x] = currPlayer;
                    y = j;
                    this->update();
                    mousePressed = true;
                    break;
                }

            }
            if(j+1 < 6){

                if(this->gridTable[j+1][x] != player1 && this->gridTable[j+1][x] != player2){
                this->gridTable[j+1][x]= currPlayer;
                y = j+1;
                this->update();
                }else{
                mousePressed = true;
                break;
                }

            }else{
                mousePressed = true;
                break;
            }

    }

}


QRectF Table::boundingRect() const{
    return QRectF(0,0,tableScene->width(),tableScene->height());
}

bool  Table::canPlace(int j){

    bool yes = false;

    for(int i = 6-1; i >= 0 && !yes; i--){

        if(gridTable[i][j] == 0)
        yes = true;

    }

    return yes;

}

int Table::checkTerminalState(int player){

    //Horizontal
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 7-3; j++)
            if(gridTable[i][j] == player && gridTable[i][j+1] == player && gridTable[i][j+2] == player && gridTable[i][j+3] == player)
                return player;

    //Vertical
    for(int i = 0; i < 6-3; i++)
        for(int j = 0; j < 7; j++)
            if(gridTable[i][j] == player && gridTable[i+1][j] == player && gridTable[i+2][j] == player && gridTable[i+3][j] == player)
                return player;

    //Diagonal "\"
    for(int i = 0; i < 6-3; i++)
        for(int j = 0; j < 7-3; j++)
            if(gridTable[i][j] == player && gridTable[i+1][j+1] == player && gridTable[i+2][j+2] == player && gridTable[i+3][j+3] == player)
                return player;

    //Diagonal "/"
    for(int i = 0; i < 6; i++)
        for(int j = 7-1; j >= 3; j--)
            if(gridTable[i][j] == player && gridTable[i+1][j-1] == player && gridTable[i+2][j-2] == player && gridTable[i+3][j-3] == player)
                return player;

    //Full Table
    return 0;

}

void  Table::add(int j, int player){


    for(int i = 6-1; i >= 0; i--)
        if(gridTable[i][j] == 0){
            gridTable[i][j] = player;
            break;
        }

   // printLogicMatrix();

}

void  Table::remove(int j){

    for(int i = 0; i < 6; i++)
        if(gridTable[i][j] != 0){
            gridTable[i][j] = 0;
            break;
        }

   // printLogicMatrix();

}

int  Table::staticEvaluator(){

    int cpuWin = 0;
    int cpuLoss = 0;

    for(int i = 0; i < 7; i++){

        cpuWin += checkSpaces(i,2);
        cpuLoss += checkSpaces(i,1);

    }

    return cpuWin - cpuLoss;
}

int Table::checkSpaces(int col, int player){


    int detectedThreats = 0;

        for(int i = 0; i < 6; i++){

        if(gridTable[i][col] == 0){

            int horizontal = 0;
            int vertical = 0;
            int mainDiag = 0;
            int invDiag = 0;

            //Horizontal Right
            for(int j = col; j < col+3; j++){
                if(j+1 < 7 && (gridTable[i][j+1] == player || gridTable[i][j+1] == 0) )
                horizontal++;
                else
                break;
            }

            //Horizontal Left
            for(int j = col; j > col-3; j--){
                if(j-1 >= 0 && (gridTable[i][j-1] == player || gridTable[i][j-1] == 0) )
                horizontal++;
                else
                break;
            }

            if(horizontal >= 3)
            detectedThreats+=20;

            //Vertical
            for(int j = i; j < i+3; j++)
                if(j+1 < 6 && (gridTable[j+1][col] == player || gridTable[j+1][col] == 0) )
                vertical++;
                else
                break;

            if(vertical >= 3)
            detectedThreats+=20;

            int q = col;
            //Diagonal "\" Lower Bound
            for(int j = i; j < i+3; j++){
                if(q+1 < 7 && j+1 < 6 && (gridTable[j+1][q+1] == player || gridTable[j+1][q+1] == 0) ){
                    mainDiag++;
                    q++;
                }else
                break;
            }

            q = col;
            //Diagonal "\"  Upper Bound
            for(int j = i; j > i-3; j--){
                if(q-1 >= 0 && j-1 >= 0 && (gridTable[j-1][q-1] == player || gridTable[j-1][q-1] == 0) ){
                    mainDiag++;
                    q--;
                }else
                break;
            }

            if(mainDiag >= 3)
            detectedThreats += 20;

             q = col;
            //Diagonal "/" Lower Bound
            for(int j = i; j < i+3; j++){
                if(q-1 >= 0 && j+1 < 6 && (gridTable[j+1][q-1] == player || gridTable[j+1][q-1] == 0) ){
                    invDiag++;
                    q--;
                }else
                break;
            }

            q = col;
            //Diagonal "/"  Upper Bound
            for(int j = i; j > i-3; j--){
                if(q+1 < 7 && j-1 >= 0 && (gridTable[j-1][q+1] == player || gridTable[j-1][q+1] == 0)){
                    invDiag++;
                    q++;
                }else
                break;
            }

            if(invDiag >= 3)
            detectedThreats += 20;

        }

    }

    return detectedThreats;



}

int  Table::max(int depth){

    /*NOTE: Evaluate both terminal states in order to have an accurate response */

    int op1 = checkTerminalState(2);
    int op2 = checkTerminalState(1);

    if(op1){

            if(op1 == 2)
            return 200000;
            else
            return 0;

    }

    if(op2){

            if(op2 == 1)
            return -200000;
            else
            return 0;

    }

    if(!depth)
    return staticEvaluator();

    int bestState = INT_MIN;

    for(int i = 0; i < 7; i++){

        if(canPlace(i)){

            add(i,2);
            int n =  min(depth - 1);

            if(n > bestState){
                bestState = n;
                move = i;
            }

            remove(i);
        }

    }

    return bestState;
}

int Table::min(int depth){

    /*NOTE: Evaluate both terminal states in order to have an accurate response */

    int op1 = checkTerminalState(1);
    int op2 = checkTerminalState(2);

    if(op1){

        if(op1 == 1)
        return -200000;
        else
        return 0;

    }

    if(op2){

        if(op2 == 2)
        return 200000;
        else
        return 0;

    }

    if(!depth)
    return staticEvaluator();

        int worstState = INT_MAX;

        for(int i = 0; i < 7; i++){

            if(canPlace(i)){

                add(i,1);
                int n =  max(depth - 1);

                if(n < worstState){
                    worstState = n;
                }

                remove(i);

            }

        }

   return worstState;


}

