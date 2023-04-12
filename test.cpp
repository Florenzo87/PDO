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
std::vector<int> backtracking(SAT sat);
void print(std::vector<int> vec);
std::vector<int> next(SAT sat, int depth);
bool last(std::vector<int> belegung, int depth);
std::vector<int> nextimp(SAT sat, int depth);
std::vector<int> next(std::vector<int> belegung, int depth);


int main (int argc, char** argv) {                              //liest text aus den gegebenen Dokument und baut eine SAT Klasse dafür, ruft dann ein backtracking auf um eine Lösung zu finden
        std::string filename = argv[1];
        SAT sat1 = SAT(filename);
        std::vector<int> losung = backtracking(sat1);
        print(losung);
        return 0;
}


std::vector<int> backtracking(SAT sat){                         //setzt für jede Variable die Besetzung als falsch, falls ein Problem auftritt, versucht es richtig einzusetzen
        int var = sat.variables();
        for (int i = 0; i < var+1; i++){
                sat.set_belegung(i, 0);
                bool correct = sat.verify();
                //std::std::cout << correct << std::endl;
                if(correct == 0){
                        //std::cout << "incorrect" << std::endl;
                        sat.set_belegung(i, 1);
                        correct = sat.verify();
                        if(correct == 0){
                                print(sat.get_belegung());
                                sat = backtrackingnaiv(sat, i);         //falls weder falsch oder richtig gültig sind, geht es zur nächste besetzung bis er eine richtige findet
                        }
                }
                print(sat.get_belegung());
        }

        return sat.get_belegung();
}

SAT backtrackingnaiv(SAT sat, int depth){                               //ruft die nächste Besetzung auf bis es eine gültige findet oder es schon alle durchgegangen ist
        std::vector<int> belegung = sat.get_belegung();
        bool end = last(belegung, depth);
        while(sat.verify() == 0 & end == 0){
                //print(sat.get_belegung());
                std::vector<int> belegung = nextimp(sat,depth);
                sat.set_belegung(belegung);
                end = last(belegung, depth);
                if (end == true){
                        //std::cout << "END" << std::endl;
                }
                if (sat.verify() == true){
                        //std::cout << "TRUE" << std::endl;
                        break;
                }
                print(sat.get_belegung());
        }
        if (sat.verify() == false){
        std::cout << "no solution found" << std::endl;
        }
        return sat;
}


std::vector<int> next(SAT sat, int depth){                          //findet die nächste Besetzung abhängig vn der tiefe der Suche und der aktuelle Besetzung
        std::vector<int> belegung = sat.get_belegung();
        for(int i = depth ; i > 0; i--){
                //std::cout << belegung[i] << std::endl;
                if (belegung[i] == 1){
                        belegung[i] = 0;
                }
                else if (belegung[i] == 0){
                        belegung[i] = 1;
                        break;
                } 
        }
        return belegung;
}

std::vector<int> next(std::vector<int> belegung, int depth){            //gleich wie oben aber für belegungsvektoren statt SATs
        for(int i = depth ; i > 0; i--){
                //std::cout << belegung[i] << std::endl;
                if (belegung[i] == 1){
                        belegung[i] = 0;
                }
                else if (belegung[i] == 0){
                        belegung[i] = 1;
                        break;
                } 
        }
        return belegung;
}

std::vector<int> nextimp(SAT sat, int depth){                          //findet die nächste Besetzung abhängig vn der tiefe der Suche und der aktuelle Besetzung
        std::vector<int> belegung = sat.get_belegung();                    //diese ist die improved version von der obere und schaut sich an welche die größte Variable ist die sich in eine falsche Klausel befindet um nicht durch alle nach diese gehen zu müssen, da man direkt diese verändern kann
        int pos = sat.biggesterror();
        if(pos != depth){
                std::cout << "es ist besser als der normale" << std::endl;
        }
        //std::cout << pos << std::endl;
        //std::cout << belegung[pos] << std::endl;
        for(int i = depth ; i > pos; i--){
                //std::cout << "a" << std::endl;
                belegung[i] = 0;
        }
        bool checked = false;
        if (belegung[pos] == 0){
                //std::cout << "b" << std::endl;
                belegung [pos] = 1;
                checked = true;
        }
        if (belegung[pos] == 1 & checked == false){
                //std::cout << "c" << std::endl;
                belegung = next(belegung, pos);
        }
        return belegung;
}

bool last(std::vector<int> belegung, int depth){                        //Funktion zum überprüfen ob man schon am Ende aller Besetzungen ist
        bool end = true;
        for(int i = 0; i < depth-1; i++){
                if (belegung[i]==0){
                        end = false;
                }
        }
        return end;
}

void print(std::vector<int> vec){                               
        for(int i = 0; i < vec.size(); i++){
                std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
}
