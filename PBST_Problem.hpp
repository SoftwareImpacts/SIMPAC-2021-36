//
//  DeepSeaTreasure_Problem.hpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#ifndef PBST_PROBLEM_hpp
#define PBST_PROBLEM_hpp

#include "Shared.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>

class DeepSeaTreasure {
    public: //Variáveis
        int rows;
        int cols;
        int rowXcol;
        int shots;
        std::vector<int> size;
        std::vector<int> times;
        std::vector<int> pressure;
        std::vector<int> treasures;
        std::vector<std::vector<int>> possibleActions;
        std::vector<std::vector<int>> matrixEnvironment;
    public: //Métodos
        DeepSeaTreasure ();
        ~DeepSeaTreasure ();
        void constructEnvironment ();
        void extractPossiblesActions ();
        void showExtractPossibleActions ();
        void showEnvironment ();
};

extern DeepSeaTreasure problem;

#endif /* DeepSeaTreasure_Problem_hpp */
