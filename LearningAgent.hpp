//
//  LearningAgent.hpp
//  Pratica
//
//  Created by Thiago Henrique on 11/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#ifndef LEARNINGAGENT_HPP
#define LEARNINGAGENT_HPP

#include "Environments.h"
#include "eGreedyPolicy.hpp"
#include "Shared.hpp"
#include "Reward.hpp"
#include "StdC++.h"

class Agent {
    private: //Variáveis
        double m_gamma;
        double m_alpha;
        int m_objectives;
        std::vector<double> m_weights;
        std::vector<double> m_lastValue;
        std::vector<std::vector<std::vector<double>>> m_Q;
    public: //Variáveis
        int nextState;
        int currentState;
        int nextBetterAction;
        int action; //Possíveis ações: cima - 0, direita - 1, baixo - 2 e esquerda - 3
        bool lastState;
    public: //Métodos
        Agent ();
        ~Agent ();
        void initializeQ ();
        void updateState ();
        void checkLastState ();
        void resetVariables ();
        void resetQObjectivesTables ();
        void setGamma (double t_gamma);
        void setAlpha (double t_alpha);
        void temporalDifference ();
        double getQValue (int t_objective, int t_state, int t_action);
        double getTemporalDifference (int t_objective);
        double getWeightObjective (int t_objective);
        double getGamma ();
        double getAlpha ();
        int getObjectives ();
};

extern Agent agent;

#endif /* LearningAgent_hpp */
