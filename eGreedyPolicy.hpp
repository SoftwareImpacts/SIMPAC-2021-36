//
//  eGreedyPolicy.hpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#ifndef EGREEDYPOLICY_HPP
#define EGREEDYPOLICY_HPP

#include "Environments.h"
#include "LearningAgent.hpp"
#include "Shared.hpp"
#include "StdC++.h"

class eGreedy {
    private:
        double m_epsilon;
    public:
        std::vector<int> currentPolicy;
        std::vector<int> allActions;
    public:
        eGreedy ();
        ~eGreedy ();
        void scalarizeActions (bool t_alternate = false);
        void resetVariables ();
        void updateEpsilon ();
        void resetEpsilon ();
        int doAction (bool t_alternate = false);
        int greedyAction ();
        int nextGreedyAction ();
        int randomNumberInt ();
        int forcedRandomAction (int t_state);
        bool checkOptions (bool t_alternate = false);
        double randomNumber ();
};

extern eGreedy policy;

#endif /* eGreedyPolicy_hpp */
