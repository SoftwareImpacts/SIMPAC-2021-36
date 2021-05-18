//
//  Supervisor.hpp
//  Treinamento Programacao
//
//  Created by Thiago Henrique on 18/01/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#ifndef SUPERVISOR_HPP
#define SUPERVISOR_HPP

#include "Environments.h"
#include "RegisterInFile.hpp"
#include "LearningAgent.hpp"
#include "eGreedyPolicy.hpp"
#include "Shared.hpp"
#include "Reward.hpp"
#include "StdC++.h"

class Supervisor {
    private:
        struct m_constraint {
            int finalState;
            int registeredEpisode;
            double maxAccumulatedQValue;
            std::vector<double> totalRewardsObjectives;
            std::vector<int> bestPolicy;
            bool converged;
        };
        int m_convergences;
        std::vector<m_constraint> m_constraints;
    public:
        Supervisor ()
            : m_convergences{0}
            { initializeManager(); }
        ~Supervisor ();
        bool compareSolutions (int t_solution, double t_reward);
        bool getSolutionConvergence (int t_solution);
        bool hardCompareSolutions (int t_solution);
        bool convergedSolution ();
        bool checkState (double t_reward);
        void removePossible (int t_currentState);
        void initializeManager ();
        void observePolicy (double t_reward);
        int getConvergences ();
        int getFinalState (int t_solution);
        int getRegisteredEpisode (int t_solution);
        double getMaxAccumulatedQValue (int t_solution);
        double getTotalRewardObjective (int t_solution, int t_objective);
        std::vector<int> getPolicy (int t_solution);
};

extern Supervisor manager;

#endif /* Supervisor_hpp */
