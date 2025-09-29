#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H

template <typename T>
class TournamentNode{
    public:
        TournamentNode(TournamentNode<T>* left, TournamentNode<T>* right);
        TournamentNode(T winner);
        TournamentNode();
        ~TournamentNode();
        T getWinner();
        T getLoser();
        bool hasChild();
        T m_winner;
        TournamentNode<T>* m_left;
        TournamentNode<T>* m_right;
};

template <typename T>
TournamentNode<T>::TournamentNode(TournamentNode<T>* left, TournamentNode<T>* right){
    m_left = left;
    m_right = right;
    // takes the winners of the left and right
    // and takes the higher value between the two
    if (m_left -> m_winner < m_right -> m_winner){
        m_winner = m_right -> m_winner;
    } else{
        m_winner = m_left -> m_winner;
    }
}

template <typename T>
TournamentNode<T>::TournamentNode(T winner){
    m_winner = winner;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
TournamentNode<T>::TournamentNode(){
}

template <typename T>
TournamentNode<T>::~TournamentNode(){
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
T TournamentNode<T>::getWinner(){
    return m_winner;
}

template <typename T>
T TournamentNode<T>::getLoser(){
    if (m_left -> m_winner < m_winner){
        return m_left -> m_winner;
    } else{
        return m_right -> m_winner;
    }
}

template <typename T>
bool TournamentNode<T>::hasChild(){
    if (m_left != NULL){
        return true;
    } else{
        return false;
    }
}

#endif