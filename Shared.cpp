//
//  Shared.cpp
//  Q-Learning - Environment
//
//  Created by Thiago Henrique on 27/02/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#include "Shared.hpp"

Data::~Data () {
    
}

void Data::initVariables () {
    this->finishEpisode = false;
    this->totalConverged = false; //Se todas as soluções foram encontradas
    this->resetPolicy = false;
    this->converged = false; //Convergência por cada solução
    this->somaDelta = 0.0;
    this->delta = 0.0001;
    this->cumReward = 0.0;
    this->actionsCount = 0;
    this->runsForAverage = 20;
    this->totalConvergences = 10;
    this->convergenceCount = 0;
    this->episodeCount = 0;
    this->totalEpisodes = 3001; //Used for define a limit of episodes for a comparison with other algorithms
    this->episodesBySolution = 300; //Used for define a limit of episodes for a comparison with other algorithms
    this->scalarizedQ.reserve(problem.rowXcol);
    this->scalarizedQ.resize(problem.rowXcol, std::vector<double> (problem.shots, 0));
    this->lastScalarizedQ.reserve(problem.rowXcol);
    this->lastScalarizedQ.resize(problem.rowXcol, std::vector<double> (problem.shots, 0));
    this->matrixDelta.reserve(problem.rowXcol);
    this->matrixDelta.resize(problem.rowXcol, std::vector<double> (problem.shots, 0));
    this->storedQValues.reserve(2);
    this->storedQValues.resize(2, std::vector<double> (this->totalEpisodes, 0));
    this->uselessActionsBySolution.reserve(this->episodesBySolution);
    this->uselessActionsBySolution.resize(this->episodesBySolution, 0);
    this->averageUselessActions.reserve(this->totalEpisodes);
    this->averageUselessActions.resize(this->totalEpisodes, 0);
    this->storedUselessActions.reserve(this->runsForAverage);
    this->storedUselessActions.resize(this->runsForAverage, std::vector<int> (this->totalEpisodes, 0));
    this->storedSolutions.reserve(this->totalEpisodes);
    this->storedSolutions.resize(this->totalEpisodes, std::vector<std::vector<int>> (this->totalConvergences, std::vector<int>(2, 0)));
    this->optimalValuesOfSolutions.reserve(this->totalConvergences);
    this->optimalValuesOfSolutions.resize(this->totalConvergences, std::vector<int> (this->totalConvergences, 0));
    
    problem.setSolutions();
}

void Data::resetVariables () {
    this->actionsCount = 0;
    this->finishEpisode = false;
    
    agent.resetVariables();
    policy.resetVariables();
}

void Data::testConvergence () {
    auto& delta = this->matrixDelta;
    auto& lastQ = this->lastScalarizedQ;
    auto& Q = this->scalarizedQ;
    this->somaDelta = 0.0;
    this->converged = false;
    
    for (int i = 0; i < problem.rowXcol; ++i) {
        for (int j = 0; j < problem.shots; ++j) {
            delta[i][j] = abs(lastQ[i][j] - Q[i][j]);
            this->somaDelta += delta[i][j];
        }
    }
    
    if (this->somaDelta < this->delta) {
        if (this->convergenceCount < 50) {
            this->convergenceCount++;
        } else {
            this->converged = true;
            
            if (manager.getConvergences() == this->totalConvergences) {
                this->totalConverged = true;
            }
        }
    } else {
        this->convergenceCount = 0;
    }
    
    lastQ = Q;
}

double Data::getAccumulatedQValue () {
    double t_total_value = 0.0;
    
    t_total_value += this->scalarizedQ[0][policy.allActions[0]];
    
    for (int i = 0, j = i + 1; i < policy.currentPolicy.size(); ++i, ++j) {
        if (i < policy.currentPolicy.size() - 1) {
            t_total_value += this->scalarizedQ[policy.currentPolicy[i]][policy.allActions[j]];
        }
    }
    
    return t_total_value;
}

void Data::resetQTables () {
    for (int i = 0; i < problem.rowXcol; i++) {
        for (int j = 0; j < problem.shots; j++) {
            this->scalarizedQ[i][j] = 0;
            this->lastScalarizedQ[i][j] = 0;
        }
    }
}

void Data::storeQValues () {
    this->storedQValues[0][this->episodeCount] = this->getAccumulatedQValue();//abs(this->getAccumulatedQValue());
    this->storedQValues[1][this->episodeCount] = this->episodeCount;
}

void Data::storeSolutions (int t_lastState) {
    for (int i = 0; i < this->totalConvergences; i++) {
        if (manager.getSolutionConvergence(i)) {
            this->storedSolutions[this->episodeCount][i][0] = abs(manager.getTotalRewardObjective(i, 1));
            this->storedSolutions[this->episodeCount][i][1] = (manager.getTotalRewardObjective(i, 0) * -1);
        } else if (manager.getFinalState(i) == t_lastState) {
            this->storedSolutions[this->episodeCount][i][0] = abs(reward.getReward(1));
            this->storedSolutions[this->episodeCount][i][1] = (reward.getReward(0) * -1);
        }
    }
}
//Useful function when I need to compute solutions for analysis
bool Data::finishSolutionSearch () {
    bool t_return = false;
    
    if (this->episodeCount % this->episodesBySolution == 0) {
        t_return = true;
    }
    
    return t_return;
}
//Useful function when I need to compute solutions for analysis
bool Data::allOptimalSolutionsFound () {
    bool t_return = true;
    
    for (int i = 0; i < this->totalConvergences; i++) {
        if (this->optimalValuesOfSolutions[i][1] != manager.getTotalRewardObjective(i, 1)) {
            t_return = false;
        }
    }
    
    return t_return;
}

void Data::storeUselessActions (int t_optimalSolutionsFound) {
    for (int i = 0; i < this->totalConvergences; i++) {
        if (agent.currentState == manager.getFinalState(i)) {
            int t_initialEpisode = (i * 300) + 1;
            int t_finalEpisode = (i * 300) + 300;
            int t_actionsCount = 0;
            
            for (int j = t_initialEpisode, k = 0; j <= t_finalEpisode; j++, k++) {
                t_actionsCount = this->uselessActionsBySolution[k];
                t_actionsCount -= abs(manager.getTotalRewardObjective(i, 1));
                this->storedUselessActions[t_optimalSolutionsFound][j] = t_actionsCount;
            }
            
            break;
        }
    }
    
    std::fill(this->uselessActionsBySolution.begin(), this->uselessActionsBySolution.end(), 0);
}

void Data::storeUselessActionsBySolution () {
    if (this->episodeCount == 0) {
        return;
    } else {
        this->uselessActionsBySolution[(this->episodeCount - 1) % this->episodesBySolution] = this->actionsCount;
    }
}
