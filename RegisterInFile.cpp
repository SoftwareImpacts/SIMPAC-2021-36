//
//  RegisterInFile.cpp
//  QManaged_Environment
//
//  Created by Thiago Henrique on 19/08/20.
//

#include "RegisterInFile.hpp"

File::File () {
    
}

File::~File () {
    
}

void File::regTime (int t_execution) {
    std::ofstream save;
    save.open("DadosColetados/report.txt", std::ios::app);
    
    time_t now = time(NULL);
    struct tm* timeInfo;
    timeInfo = localtime(&now);
    char *currentTime = asctime(timeInfo);
    currentTime[strlen(currentTime) - 1] = '\0';
    save << "--------->>>> " << currentTime << " - Execution: " << t_execution << " <<<<---------" << std::endl;
    
    save.close();
}

void File::regActions () {
    std::ofstream save;
    save.open("DadosColetados/report.txt", std::ios::app);
    
    save << "Action: " << agent.action << std::endl;
    save << "Current State: " << agent.currentState << std::endl;
    save << "Next State: " << agent.nextState << std::endl;
    save << "Next Better Action: " << agent.nextBetterAction << std::endl;
    save << "Treasure Objective: " << reward.getReward(0) << std::endl;
    save << "Time Objective: " << reward.getReward(1) << std::endl;
    save << "Actions: " << data.actionsCount << std::endl;
    save << "-----------------------------------------------------" << std::endl;
    
    save.close();
}

void File::regEpisodes () {
    std::ofstream save;
    save.open("DadosColetados/report.txt", std::ios::app);
    
    save << "Actions: ";
    
    for (int i = 0; i < policy.allActions.size(); ++i) {
        save << policy.allActions[i] << " ";
    }
    
    save << std::endl;
    
    save << "Policy: ";
    
    for (int i = 0; i < policy.currentPolicy.size(); ++i) {
        save << policy.currentPolicy[i] << " ";
    }
    
    save << std::endl;
    save << "Cumulative Reward Q: " << data.getAccumulatedQValue() << std::endl;
    save << "Treasure Objective: " << reward.getReward(0) << std::endl;
    save << "Time Objective: " << reward.getReward(1) << std::endl;
    save << "Episode: " << data.episodeCount << std::endl;
    save << "Convergence: " << data.convergenceCount << std::endl;
    save << "-----------------------------------------------------" << std::endl;
    
    save.close();
}

void File::regSolutions (int t_solution) {
    std::ofstream save;
    save.open("DadosColetados/report.txt", std::ios::app);
    
    std::vector<int> t_policy = manager.getPolicy(t_solution);
    
    save << "Solution: " << (t_solution + 1) << std::endl;
    save << "Episodes Needed: " << manager.getRegisteredEpisode(t_solution) << std::endl;
    save << "Final State: " << manager.getFinalState(t_solution) << std::endl;
    save << "Cumulative Reward Q: " << data.getAccumulatedQValue() << std::endl;
    save << "Treasure Objective: " << manager.getTotalRewardObjective(t_solution, 0) << std::endl;
    save << "Time Objective: " << manager.getTotalRewardObjective(t_solution, 1) << std::endl;
    save << "Policy: ";
    
    for (int i = 0; i < t_policy.size(); ++i) {
        save << t_policy[i] << " ";
    }
    
    save << std::endl;
    save << "-----------------------------------------------------" << std::endl;
    
    save.close();
}

void File::regStoredSolutions (int t_optimalSolutionsFound) {
    std::ofstream save;
    
    std::string nomeArquivo = "DadosColetados/solutions_" + std::to_string(t_optimalSolutionsFound) + ".txt";
    save.open(nomeArquivo, std::ios::app);
    
    for (int i = 0; i < data.storedSolutions.size(); i++) {
        for (int j = 0; j < data.totalConvergences - 1; j++) {
            save << data.storedSolutions[i][j][0] << " ";
            save << data.storedSolutions[i][j][1] << " ";
        }
        
        save << data.storedSolutions[i][data.totalConvergences - 1][0];
        save << " " << data.storedSolutions[i][data.totalConvergences - 1][1] << std::endl;
    }
    
    save.close();
}

void File::regOptimalSolutions (int t_totalConvergences, int t_optimalSolutionsFound) {
    std::ofstream save;
    
    std::string nomeArquivo = "DadosColetados/report" + std::to_string(t_optimalSolutionsFound) + ".txt";
    save.open(nomeArquivo, std::ios::app);
    
    for (int i = 0; i < t_totalConvergences; i++) {
        std::vector<int> t_policy = manager.getPolicy(i);
        
        save << "Solution: " << (i + 1) << std::endl;
        save << "Episodes Needed: " << manager.getRegisteredEpisode(i) << std::endl;
        save << "Final State: " << manager.getFinalState(i) << std::endl;
        save << "Cumulative Reward Q: " << manager.getMaxAccumulatedQValue(i) << std::endl;
        save << "Treasure Objective: " << manager.getTotalRewardObjective(i, 0) << std::endl;
        save << "Time Objective: " << manager.getTotalRewardObjective(i, 1) << std::endl;
        save << "Policy: ";
        
        for (int j = 0; j < t_policy.size(); j++) {
            save << t_policy[j] << " ";
        }
        
        save << std::endl;
        save << "-----------------------------------------------------" << std::endl;
    }
    
    save.close();
}

void File::regAvgUselessActions () {
    int t_totalUselessActions = 0;

    std::ofstream save;
    save.open("DadosColetados/actionsCount.txt", std::ios::app);

    save << "actionsCount = [";

    for (int i = 0; i < data.totalEpisodes; i++) {
        for (int j = 0; j < data.runsForAverage; j++) {
            t_totalUselessActions += data.storedUselessActions[j][i];
        }
        
        data.averageUselessActions[i] = double(double(t_totalUselessActions) / double(data.runsForAverage));
        
        save << data.averageUselessActions[i] << " ";
        
        t_totalUselessActions = 0;
    }

    save << "]";

    save.close();
}
