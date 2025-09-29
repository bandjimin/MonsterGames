#include "RunScareGame.h"
#include <fstream>
#include <sstream>

RunScareGame::RunScareGame() {
    // Constructor body (if needed)
}

RunScareGame::~RunScareGame() {
    // Destructor body (if needed)
}

void RunScareGame::runTournament(std::string format, std::string input, std::string output) {
    std::ifstream file(input); // Open the input file
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << input << std::endl;
        return;
    }

    TournamentTree<Monster> tree(format); // Create the tournament tree
    std::string line;
    
    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        int spl;
        
        // Assuming the input format is "Name, Power" (e.g., "Sulley, 120")
        std::getline(ss, name, ','); // Read the name
        ss >> spl; // Read the spl value
        
        // Remove any trailing spaces or newline characters
        name = name.substr(0, name.find_last_not_of(" \n\r\t") + 1);

        // Create a Monster object and add it to the tree
        Monster monster(name, spl);
        tree.addLeaf(monster);
    }
    
    // Create the tournament tree and save the result
    tree.createTree();
    tree.saveTree(output);
}