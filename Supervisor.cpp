//
//  Supervisor.cpp
//  Treinamento Programacao
//
//  Created by Thiago Henrique on 18/01/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#include "Supervisor.hpp"

Supervisor::~Supervisor () {
    
}

void Supervisor::initializeManager () {
    this->m_constraints.resize(data.totalConvergences);
    this->m_constraints[0].finalState = 10;
    this->m_constraints[1].finalState = 21;
    this->m_constraints[2].finalState = 32;
    this->m_constraints[3].finalState = 43;
    this->m_constraints[4].finalState = 44;
    this->m_constraints[5].finalState = 45;
    this->m_constraints[6].finalState = 76;
    this->m_constraints[7].finalState = 77;
    this->m_constraints[8].finalState = 98;
    this->m_constraints[9].finalState = 109;
    
    for (unsigned int i = 0; i < data.totalConvergences; ++i) {
        this->m_constraints[i].maxAccumulatedQValue = INT_MAX * (-1);
        this->m_constraints[i].totalRewardsObjectives.resize(agent.getObjectives(), 0);
        this->m_constraints[i].totalRewardsObjectives[1] = INT_MAX * (-1);
        this->m_constraints[i].registeredEpisode = 0;
        this->m_constraints[i].converged = false;
    }
}

int Supervisor::getConvergences () {
    return this->m_convergences;
}

int Supervisor::getFinalState (int t_solution) {
    return this->m_constraints[t_solution].finalState;
}

int Supervisor::getRegisteredEpisode (int t_solution) {
    return this->m_constraints[t_solution].registeredEpisode;
}

std::vector<int> Supervisor::getPolicy (int t_solution) {
    return this->m_constraints[t_solution].bestPolicy;
}

double Supervisor::getMaxAccumulatedQValue (int t_solution) {
    return this->m_constraints[t_solution].maxAccumulatedQValue;
}

double Supervisor::getTotalRewardObjective (int t_solution, int t_objective) {
    return this->m_constraints[t_solution].totalRewardsObjectives[t_objective];
}

bool Supervisor::getSolutionConvergence (int t_solution) {
    return this->m_constraints[t_solution].converged;
}

bool Supervisor::convergedSolution () {
    bool t_return = false;
    
    for (int i = 0; i < data.totalConvergences; ++i) {
        if (this->m_constraints[i].finalState == agent.nextState) {
            if (this->m_constraints[i].converged == true) {
                t_return = true;
                
                break;
            }
        }
    }
    
    return t_return;
}

bool Supervisor::compareSolutions (int t_solution, double t_reward) {
    bool t_policies = false;
    bool t_objectives1 = false;
    bool t_objectives2 = false;
    bool t_return = false;
    
    if ((this->m_constraints[t_solution].maxAccumulatedQValue < t_reward)) {
        t_policies = true;
    }
    
    if (this->m_constraints[t_solution].totalRewardsObjectives[0] <= reward.getReward(0)) {
        t_objectives1 = true;
    }
    
    if (abs(this->m_constraints[t_solution].totalRewardsObjectives[1]) > abs(reward.getReward(1))) {
        t_objectives2 = true;
    }
    
    if (t_policies || (t_objectives1 && t_objectives2)) {
        t_return = true;
    }
    
    return t_return;
}

void Supervisor::observePolicy (double t_reward) {
    for (int i = 0; i < data.totalConvergences; ++i) {
        if (this->m_constraints[i].finalState == agent.currentState) {
            if (this->m_constraints[i].maxAccumulatedQValue < t_reward) {//this->compareSolutions(i, t_reward)
                this->m_constraints[i].maxAccumulatedQValue = t_reward;
                this->m_constraints[i].totalRewardsObjectives[0] = reward.getReward(0);
                this->m_constraints[i].totalRewardsObjectives[1] = reward.getReward(1);
                this->m_constraints[i].bestPolicy = policy.currentPolicy;
                
                break;
            } else {
                break;
            }
        }
    }
}

bool Supervisor::checkState (double t_reward) {
    bool t_return = true;
    
    for (int i = 0; i < data.totalConvergences; ++i) {
        if (this->m_constraints[i].finalState == agent.nextState) {
            if (data.converged && this->m_constraints[i].converged) {
                this->removePossible(agent.nextState);
                
                data.resetPolicy = true;
                data.converged = false;
                t_return = false;
                
                break;
            } else if (this->compareSolutions(i, t_reward)) {
                this->m_constraints[i].maxAccumulatedQValue = t_reward;
                this->m_constraints[i].totalRewardsObjectives[0] = reward.getReward(0);
                this->m_constraints[i].totalRewardsObjectives[1] = reward.getReward(1);
                this->m_constraints[i].bestPolicy = policy.currentPolicy;
                this->m_constraints[i].bestPolicy.push_back(agent.nextState);
                
                if (this->m_constraints[i].converged == true) {
                    this->m_constraints[i].converged = false;
                    this->m_convergences--;
                }
                
                data.converged = false;
                t_return = true;
                
                break;
            } else {
                if (this->m_constraints[i].converged == false) {
                    this->m_constraints[i].registeredEpisode = data.episodeCount;
                    this->m_constraints[i].converged = true;
                    this->m_convergences++;
                    
                    file.regSolutions(i);
                }
                
                data.resetPolicy = true;
                data.converged = false;
                t_return = true;
                
                break;
            }
        }
    }
    
    return t_return;
}

void Supervisor::removePossible (int t_currentState) {
    for (int i = 0; i < problem.possibleActions.size(); ++i) {
        for (int j = 0; j < problem.possibleActions[i].size(); ++j) {
            if (problem.possibleActions[i][j] == t_currentState) {
                problem.possibleActions[i][j] = -1;
            }
        }
    }
}
