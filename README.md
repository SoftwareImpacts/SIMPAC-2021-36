# Q-Managed

Q-Managed: A new algorithm for a multiobjective reinforcement learning

The algorithm has 3 environments, the same demonstrated in the article. Changing environments occurs as follows:
- Uncomment the environment you want to use and comment on others, in the Environment.h file.
- Uncomment the .CPP file of the environment you want to use, be it DST_Problem.cpp or BST_Problem.cpp or MDST_Problem.cpp.
- Comment on everyone else.

Learning rate and gamma parameters in the Learning_Agent.cpp file.

Randomness parameter can be changed in the eGreedyPolicy.cpp file.

*Environment for reproducibility*

Operational System = macOS Catalina
Xcode version = 11.0
Apple clang version = 11.0.0 (clang-1100.0.33.8)
C++ Language Dialect = GNU++ 14
C++ Standard Library = libc++ (LLVM C++ standard library with C++ 11 support
