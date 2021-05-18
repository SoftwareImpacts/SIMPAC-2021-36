//
//  DST_Problem.hpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#ifndef DST_PROBLEM_hpp
#define DST_PROBLEM_hpp

#include "Shared.hpp"
#include "StdC++.h"

class Environment {
    public: //Variables
        int rows;
        int cols;
        int rowXcol;
        int shots;
        std::vector<int> size;
        std::vector<int> times;
        std::vector<int> treasures;
        std::vector<std::vector<int>> possibleActions;
        std::vector<std::vector<int>> matrixEnvironment;
    public: //Methods
        Environment ();
        ~Environment ();
        void constructEnvironment ();
        void extractPossiblesActions ();
        void showExtractPossibleActions ();
        void showEnvironment ();
        void setSolutions ();
};

extern Environment problem;

#endif /* DST_Problem_hpp */
