//
//  RegisterInFile.hpp
//  QManaged_Environment
//
//  Created by Thiago Henrique on 19/08/20.
//

#ifndef RegisterInFile_hpp
#define RegisterInFile_hpp

#include "eGreedyPolicy.hpp"
#include "LearningAgent.hpp"
#include "Supervisor.hpp"
#include "Reward.hpp"
#include "Shared.hpp"
#include "StdC++.h"

class File {
    public:
        File ();
        ~File ();
        void regTime (int t_execution);
        void regActions ();
        void regEpisodes ();
        void regAvgUselessActions ();
        void regStoredSolutions (int t_optimalSolutionsFound);
        void regOptimalSolutions (int t_solution, int t_optimalSolutionsFound);
        void regSolutions (int t_solution);
};

extern File file;

#endif /* RegisterInFile_hpp */
