//
//  LearningAgent.cpp
//  Pratica
//
//  Created by Thiago Henrique on 11/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#include "LearningAgent.hpp"

Agent::Agent () {
    this->m_gamma = 0.9;
    this->m_alpha = 0.7;
    this->m_objectives = 2;
    this->action = 0;
    this->nextBetterAction = 0;
    this->nextState = 0;
    this->currentState = 0;
    this->lastState = false;
    this->m_weights.reserve(this->m_objectives);
    this->m_weights.resize(this->m_objectives, 0);
    
    for (int i = 0; i < this->m_objectives; i++) {
        this->m_weights[i] = double(1) / double(this->m_objectives);
    }
    
    this->initializeQ();
}

Agent::~Agent () {
    
}

void Agent::setGamma (double t_gamma) {
    this->m_gamma = t_gamma;
}

void Agent::setAlpha (double t_alplha) {
    this->m_alpha = t_alplha;
}

int Agent::getObjectives () {
    return this->m_objectives;
}

double Agent::getGamma () {
    return this->m_gamma;
}

double Agent::getAlpha () {
    return this->m_alpha;
}

double Agent::getQValue (int t_objective, int t_state, int t_action) {
    return this->m_Q[t_objective][t_state][t_action];
}

double Agent::getTemporalDifference (int t_objective) {
    return this->m_lastValue[t_objective];
}

double Agent::getWeightObjective (int t_objective) {
    return this->m_weights[t_objective];
}

void Agent::initializeQ () {
    this->m_Q.resize(this->m_objectives, std::vector<std::vector<double>> (problem.rowXcol, std::vector<double>(problem.shots, 0)));
    this->m_lastValue.resize(this->m_objectives, 0);
}

void Agent::resetQObjectivesTables () {
    for (int i = 0; i < this->m_objectives; i++) {
        for (int j = 0; j < problem.rowXcol; j++) {
            for (int k = 0; k < problem.shots; k++) {
                this->m_Q[i][j][k] = 0;
            }
        }
    }
}

void Agent::resetVariables () {
    this->currentState = 0;
    this->action = 0;
    this->nextBetterAction = 0;
    this->nextState = 0;
    this->lastState = false;
}

void Agent::temporalDifference () {
    int& action = this->action;
    int& state = this->currentState;
    int& nextState = this->nextState;
    int& nextAction = this->nextBetterAction;
    double t_reward = 0.0;
    
    if (this->lastState == true) {
        for (int i = 0; i < this->m_objectives; i++) {
            t_reward = 0.0;
            
            if (i == 1) {
                t_reward = -1;
            } else {
                t_reward = reward.getReward(i);
            }
            
            this->m_lastValue[i] = this->m_alpha * (t_reward - this->m_Q[i][state][action]);
            this->m_Q[i][state][action] += this->m_lastValue[i];
        }
    } else {
        for (int i = 0; i < this->m_objectives; i++) {
            t_reward = 0.0;
            
            if (i == 1) {
                t_reward = -1;
            } else {
                t_reward = reward.getReward(i);
            }
            
            this->m_lastValue[i] = this->m_alpha * ((t_reward + (this->m_gamma * this->m_Q[i][nextState][nextAction])) - this->m_Q[i][state][action]);
            this->m_Q[i][state][action] += this->m_lastValue[i];
        }
    }
}

void Agent::updateState () {
    policy.allActions.push_back(this->action);
    policy.currentPolicy.push_back(this->nextState);
    
    this->currentState = this->nextState;
}

void Agent::checkLastState () {
    if (reward.getReward(0) > 0) {
        this->lastState = true;
    } else {
        this->nextBetterAction = policy.nextGreedyAction();
        this->lastState = false;
    }
}
