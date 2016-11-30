#include "logicengine.h"

LogicEngine::LogicEngine(){

    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 7; j++)
            this->logicMatrix[i][j] = 0;


}

int LogicEngine::AIturn(){

    max(6);
    return move;

}

void LogicEngine::resetLEngine(){
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 7; j++)
            this->logicMatrix[i][j] = 0;
}

void LogicEngine::setCurrentTable(int gridTable[6][7]){

    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 7; j++)
            this->logicMatrix[i][j] = gridTable[i][j];
    printLogicMatrix();

}

bool LogicEngine::canPlace(int j){

    bool yes = false;

    for(int i = 6-1; i >= 0 && !yes; i--){

        if(logicMatrix[i][j] == 0)
        yes = true;

    }

    return yes;

}

int LogicEngine::checkTerminalState(int player){

    //Horizontal
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 7-3; j++)
            if(logicMatrix[i][j] == player && logicMatrix[i][j+1] == player && logicMatrix[i][j+2] == player && logicMatrix[i][j+3] == player)
                return player;

    //Vertical
    for(int i = 0; i < 6-3; i++)
        for(int j = 0; j < 7; j++)
            if(logicMatrix[i][j] == player && logicMatrix[i+1][j] == player && logicMatrix[i+2][j] == player && logicMatrix[i+3][j] == player)
                return player;

    //Diagonal "\"
    for(int i = 0; i < 6-3; i++)
        for(int j = 0; j < 7-3; j++)
            if(logicMatrix[i][j] == player && logicMatrix[i+1][j+1] == player && logicMatrix[i+2][j+2] == player && logicMatrix[i+3][j+3] == player)
                return player;

    //Diagonal "/"
    for(int i = 0; i < 6; i++)
        for(int j = 7-1; j >= 3; j--)
            if(logicMatrix[i][j] == player && logicMatrix[i+1][j-1] == player && logicMatrix[i+2][j-2] == player && logicMatrix[i+3][j-3] == player)
                return player;

    //Full Table
    return 0;

}

void LogicEngine::add(int j, int player){

    for(int i = 6-1; i >= 0; i--)
        if(logicMatrix[i][j] == 0){
            logicMatrix[i][j] = player;
            break;
        }

   // printLogicMatrix();

}

void LogicEngine::remove(int j){

    for(int i = 0; i < 6; i++)
        if(logicMatrix[i][j] != 0){
            logicMatrix[i][j] = 0;
            break;
        }

   // printLogicMatrix();

}


void LogicEngine::printLogicMatrix(){

    QTextStream aux(stdout);

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            aux << this->logicMatrix[i][j];
        }
        aux << '\n';
    }
    aux << "---------------------"<< '\n';
}


int LogicEngine::staticEvaluator(){

    int cpuWin = 0;
    int cpuLoss = 0;

    for(int i = 0; i < 7; i++){

        cpuWin += checkSpaces(i,2);
        cpuLoss += checkSpaces(i,1);

    }

    return cpuWin - cpuLoss;
}

int LogicEngine::checkSpaces(int col, int player){

    int detectedThreats = 0;

    for(int i = 0; i < 6; i++){

        if(logicMatrix[i][col] == 0){

            int horizontal = 0;
            int vertical = 0;
            int mainDiag = 0;
            int invDiag = 0;

            //Horizontal Right
            for(int j = col; j < col+3; j++){
                if(j+1 < 7 && logicMatrix[i][j+1] == player)
                horizontal++;
                else
                break;
            }

            //Horizontal Left
            for(int j = col; j > col-3; j--){
                if(j-1 >= 0 && logicMatrix[i][j-1] == player)
                horizontal++;
                else
                break;
            }

            if(horizontal >= 3)
            detectedThreats+=20;

            //Vertical
            for(int j = i; j < i+3; j++)
                if(j+1 < 6 && logicMatrix[j+1][col] == player)
                vertical++;
                else
                break;

            if(vertical >= 3)
            detectedThreats+=20;

            int q = col;
            //Diagonal "\" Lower Bound
            for(int j = i; j < i+3; j++){
                if(q+1 < 7 && j+1 < 6 && logicMatrix[j+1][q+1] == player){
                    mainDiag++;
                    q++;
                }else
                break;
            }

            q = col;
            //Diagonal "\"  Upper Bound
            for(int j = i; j > i-3; j--){
                if(q-1 >= 0 && j-1 >= 0 && logicMatrix[j-1][q-1]){
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
                if(q-1 >= 0 && j+1 < 6 && logicMatrix[j+1][q-1] == player){
                    invDiag++;
                    q--;
                }else
                break;
            }

            q = col;
            //Diagonal "/"  Upper Bound
            for(int j = i; j > i-3; j--){
                if(q+1 < 7 && j-1 >= 0 && logicMatrix[j-1][q+1]){
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

int LogicEngine::max(int depth){

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

int LogicEngine::min(int depth){

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

