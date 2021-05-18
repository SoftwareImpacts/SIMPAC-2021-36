//
//  Shared.hpp
//  Q-Learning - Environment
//
//  Created by Thiago Henrique on 27/02/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#ifndef SHARED_HPP
#define SHARED_HPP

#include "Supervisor.hpp"
#include "eGreedyPolicy.hpp"
#include "Reward.hpp"
#include "StdC++.h"

class Data {
    public:
        double somaDelta;
        double cumReward;
        double delta;
        int actionsCount;
        int totalConvergences;
        int convergenceCount;
        int episodesBySolution;
        int runsForAverage;
        int totalEpisodes;
        int episodeCount;
        bool converged;
        bool resetPolicy;
        bool finishEpisode;
        bool totalConverged;
        std::vector<std::vector<std::vector<int>>> storedSolutions;
        std::vector<std::vector<int>> optimalValuesOfSolutions;
        std::vector<std::vector<int>> storedUselessActions;
        std::vector<int> uselessActionsBySolution;
        std::vector<int> statesToObserve;
        std::vector<double> averageUselessActions;
        std::vector<std::vector<double>> scalarizedQ;
        std::vector<std::vector<double>> lastScalarizedQ;
        std::vector<std::vector<double>> matrixDelta;
        std::vector<std::vector<double>> storedQValues;
    public:
        Data ()
            { this->initVariables(); }
        ~Data ();
        void resetQTables ();
        void storeQValues ();
        void initVariables ();
        void testConvergence ();
        void resetVariables ();
        void storeSolutions (int t_lastState);
        void storeUselessActionsBySolution ();
        void storeUselessActions (int t_optimalSolutionsFound);
        bool allOptimalSolutionsFound ();
        bool finishSolutionSearch ();
        double getAccumulatedQValue ();
};

extern Data data;

#endif /* Shared_hpp */
