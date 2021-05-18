//
//  Reward.cpp
//  Q-Learning - Environment
//
//  Created by Thiago Henrique on 26/02/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#include "Reward.hpp"

Reward::Reward () {
    this->initializeReward();
}

Reward::~Reward () {
    
}

void Reward::initializeReward () {
    if (this->m_rewardVector.size() == 0) {
        this->m_rewardVector.resize(agent.getObjectives(), 0.0);
    } else {
        for (unsigned int i = 0; i < agent.getObjectives(); ++i) {
            this->m_rewardVector[i] = 0.0;
        }
    }
}

double Reward::getReward (int t_objective) {
    return this->m_rewardVector[t_objective];
}

void Reward::updateReward (bool t_alternate) {
    int& nextState = agent.nextState;
    
    if (problem.matrixEnvironment[(nextState / 10)][(nextState % 10)] > 0) {
        this->m_rewardVector[0] = problem.matrixEnvironment[(nextState / 10)][(nextState % 10)];
    } else {
        this->m_rewardVector[0] = 0.0;
    }
    
    if (t_alternate == false) {
        this->m_rewardVector[1]--;
    }
}
