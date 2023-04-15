#pragma once 
#include <iostream>
#include <vector>
#include "Clause.hpp"



class SAT{
    public:
        bool verify() const;                                                //uberprüft ob die Belegung richtig ist
        bool verify(const int zuletz_geaenderte_variable) const;            //uberprüft ob die Belegung richtig ist aber nicht an alle clauseln
        bool verify(const int erste_geaenderte_variable, const int letzte_geaenderte_variable) const;
        int backtrack_until() const;                                        //findet die grösste Variable die in eine fehlerhafte Klausel ist
        void print() const;                                                 //print
        SAT(const std::string filename);                                    //baut SAT element aus den Textdokument
        void set_belegung(const std::vector<int>& neubelegung);             //ganz neue belegung geben 
        void set_belegung(const int pos, const int val);                    //belegung an eine Position ändern
        void set_belegung(const int pos);                                   //belegung an eine Position ändern (0 ->1, 1 ->0, 2 ->2)
        std::vector<int> get_belegung() const;                              //gibt Belegung zurück
        int variables() const;                                              //gibt Anzahl an Variablen zurück
    
    private:
        std::vector<Clause> sat;                                            //sat ist ein Vektor aus der klasse Clause
        std::vector<int> belegung;                                          //als vector von int 0,1,2 mit 2 als noch nicht belegt/gleichzeitig wahr und falsch
        int var;                                                            //Anzahl an Variablen
        int clauses;                                                        //Anzahl an Klauseln
        std::vector<std::vector<int>> clauseln_der_variable;                //in welche Klauseln sich jede Variable befindet
    
};
