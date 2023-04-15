#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>
#include <algorithm>
#include "Clause.hpp"

Clause::Clause(std::vector<int>& vec){
    cls = vec;
}

void Clause::print() const{
    for (int i=0; i < int(cls.size()); i++){
               std::cout << cls[i] << " ";
        }
    std::cout << std::endl;
}

bool Clause::verify(const std::vector<int>& belegung) const{
    bool correct = false;
    for (int pos : cls){
        if (pos > 0){
            if (belegung[pos] == 1 or belegung[pos] == 2){
                correct = true;
            }
        }
        if (pos < 0){
            if (belegung[-pos] == 0 or belegung[-pos] == 2){
                correct = true;
            }
        }
    }
    return correct;
}

int Clause::biggesterror(const std::vector<int>& belegung) const{
    int error = 0;
    for (int i=0; i < int(cls.size()); i++){
        error = std::max(error, abs(cls[i]));
    }
    return error;
}