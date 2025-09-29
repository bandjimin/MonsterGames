#ifndef TOURNAMENT_TREE_H
#define TOURNAMENT_TREE_H

#include <fstream>
#include <string>
#include <vector>

#include "Monster.h"
#include "TournamentNode.h"

template <typename T> // type in this case is Monster
class TournamentTree{
    public:
        // Ideally inputs a vector of monsters which gets turned into Tournament Nodes
        TournamentTree(std::string format);
        ~TournamentTree();
        void addLeaf(T leaf);
        void createTree();
        void saveTree(const std::string& filename);
        TournamentNode<T>* getRoot();
        TournamentTree<T>* loserTree;
    private:
        std::vector<TournamentNode<T>*> m_winners;

        std::vector<T> losers;

        bool isDouble;

        TournamentNode<T>* root;

        void runRound(); // helper function for createTree()
        void saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode);
        void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID);
};

/*
You will use these methods in your code to save your winner and/ or loser bracket trees as DOT files
Then, you'll be able to visualize your trees at this link: https://dreampuf.github.io/GraphvizOnline/
*/

template <typename T>
TournamentTree<T>::TournamentTree(std::string format){
    if (format == "double"){
        isDouble = true;
        loserTree = new TournamentTree<T>("single");
    } else{
        isDouble = false;
        loserTree = nullptr;
    }
    root = nullptr;
}

template <typename T>
TournamentTree<T>::~TournamentTree(){
    root = nullptr;
    delete root;
    if (loserTree){
        delete loserTree;
    }
}

template <typename T>
void TournamentTree<T>::addLeaf(T leaf){
    // adds to the winners vector
    TournamentNode<T>* node = new TournamentNode<T>(leaf);
    m_winners.push_back(node);
}

template <typename T>
void TournamentTree<T>::runRound(){
    std::vector<TournamentNode<T>*> winners;
    TournamentNode<T>* node;
    for (int i = 0; i + 1 < m_winners.size(); i += 2){ // takes pairs and puts them against each other
        node = new TournamentNode<T>((m_winners[i]),(m_winners[i+1])); // makes node from the winner btw the two
        losers.push_back(node->getLoser());
        winners.push_back(node);
    }
    if (m_winners.size() % 2 == 1){
        winners.push_back(m_winners.back()); // pushes the last item
    }
    m_winners = winners;
}

template <typename T>
void TournamentTree<T>::createTree(){
    while (m_winners.size() >= 2){ // until m_winners is size 0
        runRound();
    }
    if (m_winners.size() == 1){
        root = m_winners[0];
    }

    if (isDouble){
        for (int i = 0; i < losers.size(); i++){
            loserTree->addLeaf(losers[i]);
        }
        loserTree->createTree();
    }
}

template <typename T>
void TournamentTree<T>::saveTree(const std::string& filename) {
    if (isDouble){
        saveTreeAsDot("w_" + filename, root);
        saveTreeAsDot("l_" + filename, loserTree->getRoot());
    } else {
        saveTreeAsDot(filename,root);
    }
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::getRoot(){
    return root;
}

// Function to save the tree as a DOT file
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for DOT output: " << filename << "\n";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    // Change the rootNode to winner or loser depending on 
    // saveTreeAsDotHelper(rootNode, file, nodeID);
    saveTreeAsDotHelper(rootNode, file, nodeID);
    file << "}\n";
    file.close();
}

// Recursive helper function for DOT file generation
// typename T is irrelevant in the Dot File instances
template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) {
    if (node == NULL) return;

    int currentID = nodeID++;
    file << "    node" << currentID << " [label=\"" << node->m_winner.getName()
         << " (Power: " << node->m_winner.getSPL() << ")\"];\n";

    if (node->m_left) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->m_left, file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->m_right) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->m_right, file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
}

#endif