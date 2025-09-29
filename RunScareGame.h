#ifndef RUN_SCARE_GAME_H
#define RUN_SCARE_GAME_H

#include "TournamentTree.h"

class RunScareGame {
    public:
        RunScareGame();
        ~RunScareGame();
        void runTournament(std::string format, std::string input, std::string output);
};

#endif