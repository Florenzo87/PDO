#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "SAT.hpp"

SAT backtrackingnaiv(SAT sat, int pos);
std::vector<int> backtracking(SAT& sat);
void print(const std::vector<int>& vec);
std::vector<int> next(const SAT& sat, const int depth);
bool last(const std::vector<int>& belegung, const int depth);
int nextimp(SAT& sat, int depth);
int next(std::vector<int>& belegung, const int depth);


int main (int argc, char** argv) {                              //liest text aus den gegebenen Dokument und baut eine SAT Klasse dafür, ruft dann ein backtracking auf um eine Lösung zu finden
        const std::string filename = argv[1];
        SAT sat1 = SAT(filename);
        std::vector<int> losung = backtracking(sat1);
        print(losung);
        return 0;
}


std::vector<int> backtracking(SAT& sat){                         //setzt für jede Variable die Besetzung als falsch, falls ein Problem auftritt, versucht es richtig einzusetzen
        int var = sat.variables();
        for (int depth = 0; depth < var+1; depth++){
                sat.set_belegung(depth, 0);
                bool correct = sat.verify(depth);
                //std::std::cout << correct << std::endl;
                if(correct == 0){
                        //std::cout << "incorrect" << std::endl;
                        sat.set_belegung(depth, 1);
                        correct = sat.verify(depth);
                        if(correct == 0){
                                //print(sat.get_belegung());
                                //sat = backtrackingnaiv(sat, i);                               //falls weder falsch oder richtig gültig sind, geht es zur nächste besetzung bis er eine richtige findet
                                std::vector<int> belegung = sat.get_belegung();
                                bool end = last(belegung, depth);
                                int geaendert = depth;
                                while(sat.verify(geaendert, depth) == 0 && end == 0){
                                        //print(sat.get_belegung());
                                        geaendert = nextimp(sat,depth);
                                        belegung = sat.get_belegung();
                                        depth = belegung[0];
                                        sat.set_belegung(belegung);
                                        end = last(belegung, depth);
                                        //if (end == true){
                                                //std::cout << "END" << std::endl;
                                        //}
                                        //if (sat.verify(geaendert, depth) == true){
                                                //std::cout << "TRUE" << std::endl;
                                                //break;
                                        //}
                                        //print(sat.get_belegung());
                                }
                                if (sat.verify() == false){
                                std::cout << "no solution found" << std::endl;
                                break;
                                }                    
                        }
                }
                //print(sat.get_belegung());
        }

        return sat.get_belegung();
}

int next(std::vector<int>& belegung, const int depth){            //gleich wie oben aber für belegungsvektoren statt SATs
        int geaendert = depth;
        for(int i = depth ; i > 0; i--){
                //std::cout << belegung[i] << std::endl;
                if (belegung[i] == 1){
                        belegung[i] = 0;
                }
                else if (belegung[i] == 0){
                        belegung[i] = 1;
                        geaendert = i;
                        break;
                } 
        }
        return geaendert;
}

int nextimp(SAT& sat, int depth){                          //findet die nächste Besetzung abhängig vn der tiefe der Suche und der aktuelle Besetzung
        std::vector<int> belegung = sat.get_belegung();                    //diese ist die improved version von der obere und schaut sich an welche die größte Variable ist die sich in eine falsche Klausel befindet um nicht durch alle nach diese gehen zu müssen, da man direkt diese verändern kann
        int pos = sat.backtrack_until();
        int geaendert = pos;                                                    //wir benutzen geaendert um zu wissen welche positionen wir geaendert haben
        //if(pos != depth){
                //std::cout << "es ist besser als der normale" << std::endl;
        //}
        //std::cout << pos << std::endl;
        //std::cout << belegung[pos] << std::endl;
        for(int i = depth ; i > pos; i--){
                //std::cout << "a" << std::endl;
                belegung[i] = 2;
        }
        bool checked = false;
        if (belegung[pos] == 0){
                //std::cout << "b" << std::endl;
                belegung [pos] = 1;
                checked = true;
        }
        if (belegung[pos] == 1 && checked == false){
                //std::cout << "c" << std::endl;
                geaendert = next(belegung, pos);
        }
        belegung[0] = pos;
        sat.set_belegung(belegung);
        return geaendert;
}

bool last(const std::vector<int>& belegung, const int depth){                        //Funktion zum überprüfen ob man schon am Ende aller Besetzungen ist
        bool end = true;
        for(int i = 0; i < depth-1; i++){
                if (belegung[i]==0){
                        end = false;
                }
        }
        return end;
}

void print(const std::vector<int>& vec){                               
        for(int i = 0; i < int(vec.size()); i++){
                std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
}
