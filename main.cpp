#include <iostream>
#include "RunScareGame.h"

int main(int argc, char** argv){
    RunScareGame rsg;
    if (argc > 2){ // the amount of arguments must exceed 3 otherwise, input and/or output file is unknown
        rsg.runTournament(argv[2], argv[1], "bracket.dot");
    } else{
        std::cout << "More arguments necessary, add input and output file." << std::endl;
        return 1;
    }
    return 0;
}