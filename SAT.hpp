#pragma once 
#include <iostream>
#include <vector>
#include "Clause.hpp"



class SAT{
    public:
        bool verify() const;                                                //uberprüft ob die Belegung richtig ist
        bool verify(const int zuletz_geaenderte_variable) const;            //uberprüft ob die Belegung richtig ist aber nur an der Klauseln in der sich die geänderte Variable befindet
        bool verify(const int erste_geaenderte_variable, const int letzte_geaenderte_variable) const;   //uberprüft ob die Belegung richtig ist aber nur an der Klauseln in der sich die geänderte Variablen befindet
        int backtrack_until() const;                                        //findet die kleinste Variable die die grösste in ihrer (falsche) Klausel ist
        void print() const;                                                 //druckt den SAT auf die Konsole, jede Klausel auf einer Zeile
        SAT(const std::string filename);                                    //baut SAT element aus den gegebenen Textdokument
        void set_belegung(const std::vector<int>& neubelegung);             //Belegung ändern zu den gegebenen Vektor, Achtung: überprüft nicht ob dieser die richtige Länge hat
        void set_belegung(const int pos, const int val);                    //Belegung an der gegebene Position zum gegebenen Wert ändern
        void set_belegung(const int pos);                                   //Belegung an der gegebene Position ändern (0 ->1, 1 ->0, 2 ->2)
        std::vector<int> get_belegung() const;                              //gibt Belegung zurück
        int variables() const;                                              //gibt Anzahl an Variablen zurück
    
    private:
        std::vector<Clause> sat;                                            //sat ist ein Vektor aus der klasse Clause
        std::vector<int> belegung;                                          //als vector von int 0,1,2 mit 2 als noch nicht belegt/gleichzeitig wahr und falsch, die erste Stelle entspricht keiner Variable und wird evtl. für der depth der besetzte Variablen benutzt
        int var;                                                            //Anzahl an Variablen
        int clauses;                                                        //Anzahl an Klauseln
        std::vector<std::vector<int>> clauseln_der_variable;                //in welche Klauseln sich jede Variable befindet
    
};
