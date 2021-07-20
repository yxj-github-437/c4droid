#include "cell.h"
std::set<int> getrandom(int num,int size){
    std::set<int> s;
    while(s.size()<num){
        s.insert(rand()%size);
    }
    return s;
}