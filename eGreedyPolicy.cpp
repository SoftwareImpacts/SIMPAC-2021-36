//
//  eGreedyPolicy.cpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#include "eGreedyPolicy.hpp"
//Definition variables
eGreedy::eGreedy () {
    this->m_epsilon = 0.90;
    this->currentPolicy.reserve(50);
    this->allActions.reserve(50);
}

eGreedy::~eGreedy () {
    
}

void eGreedy::resetVariables () {
    this->allActions.clear();
    this->currentPolicy.clear();
    this->allActions.reserve(50);
    this->currentPolicy.reserve(50);
}
//Generate a random number to define if action is greedy or not
double eGreedy::randomNumber () {
    std::random_device random;
    std::mt19937 seed(random());
    std::uniform_real_distribution<double> randomNum(0.0, 1.0);
    
    return randomNum(seed);
}
//Generate a random number to define that action the agent going to take
int eGreedy::randomNumberInt () {
    std::random_device random;
    std::mt19937 seed(random());
    std::uniform_int_distribution<int> randomNum(0, 3);
    
    return randomNum(seed);
}
//Scalarization function - without weights
void eGreedy::scalarizeActions (bool t_alternate) {
    int size = agent.getObjectives();
    int& stateOrNext = (t_alternate == true) ? agent.nextState : agent.currentState;
    double t_value = 0.0;
    
    for (int i = 0; i < problem.possibleActions[stateOrNext].size(); ++i) {
        if (problem.possibleActions[stateOrNext][i] == -1) {
            continue;
        } else {
            for (int j = 0; j < size; ++j) {
                t_value += (agent.getQValue(j, stateOrNext, i) * agent.getWeightObjective(j));
            }
            
            data.scalarizedQ[stateOrNext][i] = t_value;
        }
        
        t_value = 0.0;
    }
}
//Do action
int eGreedy::doAction (bool t_alternate) {
    int& action = agent.action;
    int& state = agent.currentState;
    int& nextState = agent.nextState;
    
    if (t_alternate == false) {
        double tipoAcao = randomNumber();
        
        this->scalarizeActions();
        
        if (tipoAcao < this->m_epsilon) {
            action = this->forcedRandomAction(state);
        } else {
            action = this->greedyAction();
        }
    } else {
        action = this->forcedRandomAction(state);
    }

    nextState = problem.possibleActions[state][action];
    
    return action;
}
//When the manager force the agent to take another action
int eGreedy::forcedRandomAction (int t_state) {
    int t_action = 0;
    
    do {
        t_action = this->randomNumberInt();
    } while (problem.possibleActions[t_state][t_action] == -1);
    
    return t_action;
}

bool eGreedy::checkOptions (bool t_alternate) {
    auto& actions = problem.possibleActions;
    auto& scalarizedQ = data.scalarizedQ;
    int& stateOrNext = (t_alternate == true) ? agent.nextState : agent.currentState;
    bool t_return = false;
    
    for (int i = 0; i < actions[stateOrNext].size(); ++i) {
        if (actions[stateOrNext][i] != -1 && scalarizedQ[stateOrNext][i] != 0) {
            t_return = true;
            break;
        }
    }
    
    return t_return;
}

int eGreedy::greedyAction () {
    double t_betterQValue = INT_MAX * (-1);
    int t_betterAction = NULL;
    int& state = agent.currentState;

    if (this->checkOptions()) {
        for (int i = 0; i < problem.possibleActions[state].size(); ++i) {
            if (problem.possibleActions[state][i] == -1) {
                continue;
            }
            
            double valueScalarized = data.scalarizedQ[state][i];
            
            if (valueScalarized > t_betterQValue) {
                t_betterQValue = data.scalarizedQ[state][i];
                t_betterAction = i;
            }
        }
    } else {
        t_betterAction = this->forcedRandomAction(state);
    }
    
    return t_betterAction;
}

int eGreedy::nextGreedyAction () {
    double t_betterNextQValue = INT_MAX * (-1);
    int t_betterNextAction = NULL;
    int& nextState = agent.nextState;
    
    this->scalarizeActions(true);
    
    if (this->checkOptions(true)) {
        for (int i = 0; i < problem.possibleActions[nextState].size(); ++i) {
            if (problem.possibleActions[nextState][i] == -1) {
                continue;
            }
            
            double valueScalarized = data.scalarizedQ[nextState][i];
            
            if (valueScalarized > t_betterNextQValue) {
                t_betterNextQValue = data.scalarizedQ[nextState][i];
                t_betterNextAction = i;
            }
        }
    } else {
        t_betterNextAction = forcedRandomAction(nextState);
    }
    
    return t_betterNextAction;
}

void eGreedy::updateEpsilon () {
    this->m_epsilon *= 0.97; //0.9996 dá mais ou menos 5 mil episodios aleatórios
}

void eGreedy::resetEpsilon () {
    if (this->m_epsilon <= 0.30) {
        this->m_epsilon = 0.30;
    }
}
