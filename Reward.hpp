//
//  Reward.hpp
//  Q-Learning - Environment
//
//  Created by Thiago Henrique on 26/02/19.
//  Copyright © 2019 Thiago Henrique. All rights reserved.
//

#ifndef REWARD_HPP
#define REWARD_HPP

#include "Environments.h"
#include "LearningAgent.hpp"
#include "Shared.hpp"
#include "StdC++.h"

class Reward {
    private:
        std::vector<double> m_rewardVector;
    public:
        Reward ();
        ~Reward ();
        void initializeReward ();
        void updateReward (bool t_alternate = false);
        double getReward (int t_objective);
};

extern Reward reward;

#endif /* Reward_hpp */
