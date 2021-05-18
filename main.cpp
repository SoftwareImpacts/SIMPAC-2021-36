//
//  main.cpp
//  Pratica
//
//  Created by Thiago Henrique on 13/03/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#include "eGreedyPolicy.hpp"
#include "LearningAgent.hpp"
#include "Environments.h"
#include "Shared.hpp"
#include "Supervisor.hpp"
#include "Reward.hpp"
#include "RegisterInFile.hpp"
#include "StdC++.h"

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::string;
//Objects creation
Environment problem;
File file;
Data data;
Agent agent;
eGreedy policy;
Reward reward;
Supervisor manager;

int main () {
    int optimalSolutionsFound = 0;
    int countExecutions = 0;
    
    while (optimalSolutionsFound < data.runsForAverage) {
        file.regTime(countExecutions + 1);
        
        while (data.totalConverged != true) {
            data.cumReward = 0;
            
            while (data.finishEpisode != true) {
                policy.doAction();
                reward.updateReward();
                agent.checkLastState();

                if ((data.converged || manager.convergedSolution()) && agent.lastState == true) {
                    int t_action = agent.action;
                    double tempCumReward = data.cumReward + data.scalarizedQ[agent.currentState][agent.action];
                    
                    if (!manager.checkState(tempCumReward)) {
                        while (t_action == agent.action) {
                            policy.doAction();
                        }
                        
                        reward.updateReward(true);
                        agent.checkLastState();
                    }
                }
                
                data.cumReward += data.scalarizedQ[agent.currentState][agent.action];
                agent.temporalDifference();
                agent.updateState();
                
                ++data.actionsCount;
                
                if (agent.lastState || data.actionsCount == 1000) {
                    if (agent.lastState) {
                        manager.observePolicy(data.cumReward);
                    }
                    
                    data.finishEpisode = true;
                }
            }
            
            policy.updateEpsilon();
            data.testConvergence();
            //data.storeUselessActionsBySolution(); //Store useless actions
            //data.storeSolutions(policy.currentPolicy[policy.currentPolicy.size() - 1]);
            //data.storeQValues();
            
            data.episodeCount++;
            //file.regEpisodes();
            
            if (data.episodeCount % 1000 == 0) {
                cout << "----------------------------------------------" << endl;
                cout << "Episode: " << data.episodeCount << endl;
                cout << "Solutions found: " << manager.getConvergences() << endl;
                cout << "----------------------------------------------" << endl;
            }
            
            reward.initializeReward();
            data.resetVariables();
            
            if (data.resetPolicy) {
                policy.resetEpsilon();
                //If will use the reset version, the following two lines must be uncommented
                //agent.resetQObjectivesTables(); //With reset version
                //data.resetQTables(); //With reset version
                
                data.resetPolicy = false;
            }
        }
        
        if (manager.getConvergences() == data.totalConvergences && data.allOptimalSolutionsFound()) {
            //file.regQValues();
            //file.regStoredSolutions(optimalSolutionsFound);
            file.regOptimalSolutions(data.totalConvergences, optimalSolutionsFound);
            
            optimalSolutionsFound++;
        }
        
        cout << "Finished Execution " << (countExecutions + 1) << endl;
        cout << endl;
        
        countExecutions++;
        
        std::vector<std::vector<int>> temp(data.runsForAverage, std::vector<int> (data.totalEpisodes, 0));
        temp = data.storedUselessActions;
        
        new (&problem) Environment();
        new (&data) Data();
        new (&agent) Agent();
        new (&policy) eGreedy();
        new (&reward) Reward();
        new (&manager) Supervisor();
        
        //data.storedUselessActions = temp;
    }
    
    //file.regAvgUselessActions();
    
    return 0;
}
