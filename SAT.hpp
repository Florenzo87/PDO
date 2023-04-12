#pragma once 
#include <iostream>
#include <vector>
#include "Clause.hpp"



class SAT{
    public:
        bool verify();                                      //uberprüft ob die Belegung richtig ist
        int biggesterror();                                 //findet die grösste Variable die in eine fehlerhafte Klausel ist
        void print();                                       //print
        SAT(char const * filename);                         //baut SAT element aus den Textdokument
        void set_belegung(std::vector<int> neubelegung);    //ganz neue belegung geben 
        void set_belegung(int pos, int val);                //belegung an eine Position ändern
        void set_belegung(int pos);                         //belegung an eine Position ändern (0 ->1, 1 ->0, 2 ->2)
        std::vector<int> get_belegung();                    //gibt Belegung zurück
        int variables();                                    //gibt Anxahl an Variablen zurück
    
    private:
        std::vector<Clause> sat;                            //sat ist ein Vektor aus der klasse Clause
        std::vector<int> belegung;                          //als vector von int 0,1,2 mit 2 als noch nicht belegt/gleichzeitig wahr und falsch
        int var;                                            //Anzahl an Variablen
        int clauses;                                        //Anzahl an Klauseln
    
};
