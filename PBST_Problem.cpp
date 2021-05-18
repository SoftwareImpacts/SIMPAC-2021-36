//
//  PBST_Problem.cpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#include "PBST_Problem.hpp"

DeepSeaTreasure::DeepSeaTreasure () {
    this->size.resize(2, 0.0);
    this->size[0] = 11;
    this->size[1] = 10;
    this->rows = this->size[0];
    this->cols = this->size[1];
    this->rowXcol = 110;
    this->shots = 4;
    this->matrixEnvironment.reserve(this->size[0]);
    this->matrixEnvironment.resize(this->size[0], std::vector<int>(this->size[1], 0));
    this->possibleActions.reserve(rowXcol);
    this->possibleActions.resize(rowXcol, std::vector<int> (shots, 0));
    this->times = {-1, -3, -5, -7, -8, -9, -13, -14, -17, -19};
    this->treasures = {1, 2, 3, 5, 8, 16, 24, 50, 74, 124};
    
    constructEnvironment();
    extractPossiblesActions();
    showExtractPossibleActions();
    showEnvironment();
}

DeepSeaTreasure::~DeepSeaTreasure () {

}

void DeepSeaTreasure::constructEnvironment () {
    this->matrixEnvironment[1][0] = 5;
    this->matrixEnvironment[2][1] = 80;
    this->matrixEnvironment[3][2] = 120;
    this->matrixEnvironment[4][3] = 140;
    this->matrixEnvironment[4][4] = 145;
    this->matrixEnvironment[4][5] = 150;
    this->matrixEnvironment[7][6] = 163;
    this->matrixEnvironment[7][7] = 166;
    this->matrixEnvironment[9][8] = 173;
    this->matrixEnvironment[10][9] = 175;
    
    for (int i = 2; i <= 10; ++i) {
        for (int j = 0; j < i - 1; ++j) {
            this->matrixEnvironment[i][j] = -99;
        }
    }
    
    this->matrixEnvironment[5][4] = -99;
    this->matrixEnvironment[5][5] = -99;
    this->matrixEnvironment[6][5] = -99;
    this->matrixEnvironment[8][7] = -99;
}

void DeepSeaTreasure::extractPossiblesActions () {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (this->matrixEnvironment[i][j] == 0) {
                if (i > 0) {
                    this->possibleActions[(i * 10) + j][0] = ((i * 10) + j) - 10;
                } else {
                    this->possibleActions[(i * 10) + j][0] = -1;
                }
                
                if (j < cols - 1) {
                    this->possibleActions[(i * 10) + j][1] = ((i * 10) + j) + 1;
                } else {
                    this->possibleActions[(i * 10) + j][1] = -1;
                }
                
                if (i < rows - 1) {
                    this->possibleActions[(i * 10) + j][2] = ((i * 10) + j) + 10;
                } else {
                    this->possibleActions[(i * 10) + j][2] = -1;
                }
                
                if (j > 0) {
                    this->possibleActions[(i * 10) + j][3] = ((i * 10) + j) - 1;
                } else {
                    this->possibleActions[(i * 10) + j][3] = -1;
                }
            }
        }
    }
    
    this->possibleActions[56][3] = -1;
    this->possibleActions[66][3] = -1;
    this->possibleActions[88][3] = -1;
}

void DeepSeaTreasure::showExtractPossibleActions () {
    for (int i = 0; i < rowXcol; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < this->possibleActions[i].size(); ++j) {
            std::cout << this->possibleActions[i][j] << " ";
        }
        
        std::cout << std::endl;
    }
}

void DeepSeaTreasure::showEnvironment () {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << this->matrixEnvironment[i][j] << " ";
        }
        
        std::cout << std::endl;
    }
}

void DeepSeaTreasure::setSolutions () {
    for (int i = 0; i < 10; i++) {
        data.optimalValuesOfSolutions[i][0] = this->treasures[i];
        data.optimalValuesOfSolutions[i][1] = this->times[i];
    }
}
