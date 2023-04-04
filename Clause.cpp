#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>
#include "Clause.hpp"
using namespace std;

Clause::Clause(std::vector<int>& vec){
    cls = vec;
}

void Clause::print(){
    for (int i=0; i < cls.size(); i++){
               cout << cls[i] << " ";
        }
    cout << endl;
}

bool Clause::verify(std::vector<int> belegung){
    bool correct = false;
    for (int i=0; i < cls.size(); i++){
        int pos = cls[i];
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

int Clause::biggesterror(std::vector<int> belegung){
    int error = 0;
    bool correct = false;
    for (int i=0; i < cls.size(); i++){
        int pos = cls[i];
        if (pos > 0){
            if (belegung[pos] == 1 or belegung[pos] == 2){
                correct = true;
            }
            if (pos > error){
                    error = pos;
                }
        }
        if (pos < 0){
            if (belegung[-pos] == 0 or belegung[-pos] == 2){
                correct = true;
            }
            if (-pos > error){
                    error = pos;
                }
        }
    }
    if (correct = true){
        cout << "TRUE" << endl;
        error = 0;
    }
    
    return error;
}