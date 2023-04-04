#pragma once 

#include <iostream>
#include <vector>


class Clause{
    public:
        Clause(std::vector<int>& cls);              //Baut ein Clause element aus ein Vektor von ints
        void print();                               //print
        bool verify(std::vector<int>);              //uberprüft anhand einer gegebene Belegung ob diese bei die Klausel gültig ist
        int biggesterror(std::vector<int>);         //gibt die grösste Variable in der Klausel falls diese falsch ist
    
    private:
        std::vector<int> cls;                       //Klausel ist ein Vektor aus ints
    
};