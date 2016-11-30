#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <QTextStream>
#include <stdio.h>
#include <string.h>
//#include "table.h"

class LogicEngine{

public:

    int logicMatrix[6][7];
    LogicEngine();
    int move;
    //AI movement
    int AIturn();
    void resetLEngine();
    //Set Current State
    void setCurrentTable(int gridTable[6][7]);

    //Checks for Terminal State
    int checkTerminalState(int player);

    void add(int j, int player);
    void remove(int j);
    bool canPlace(int j);

    void printLogicMatrix();

    int staticEvaluator();
    int checkSpaces(int col, int player);
    //Minimax procedure
    int max(int depth);
    int min(int depth);


};

#endif // LOGICENGINE_H
