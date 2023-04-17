#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "SAT.hpp"

SAT backtrackingnaiv(SAT sat, int pos);                                         //legacy
std::vector<int> backtracking(SAT& sat);                                        //setzt für jede Variable die Besetzung als falsch, falls ein Problem auftritt, versucht es wahr einzusetzen, falls weder falsch oder wahr gültig sind, geht es zur nächste besetzung bis er eine richtige findet
void print(const std::vector<int>& vec);                                        //obvious
std::vector<int> next(const SAT& sat, const int depth);                         //legacy
bool last(const std::vector<int>& belegung, const int depth);                   //Funktion zum überprüfen ob man schon am Ende aller Besetzungen ist
int nextimp(SAT& sat, int depth);                                               //findet die nächste Belegung die richtig sein könnte, diese ist die improved version und schaut sich an welche die kleinste Variable ist die fie grösste einer falsche Klausel ist um nicht durch alle nach diese gehen zu müssen, da man direkt diese verändern kann
int next(std::vector<int>& belegung, const int depth);                          //gibt die nächste Belegung der Reihenfolge nach


int main (int argc, char** argv) {                              //liest text aus den gegebenen Dokument und baut eine SAT Klasse dafür, ruft dann ein backtracking auf um eine Lösung zu finden
        const std::string filename = argv[1];
        SAT sat1 = SAT(filename);
        std::vector<int> losung = backtracking(sat1);
        print(losung);
        return 0;
}


std::vector<int> backtracking(SAT& sat){
        int var = sat.variables();
        for (int depth = 0; depth < var+1; depth++){
                sat.set_belegung(depth, 0);
                bool correct = sat.verify(depth);
                if(!correct){
                        sat.set_belegung(depth, 1);
                        correct = sat.verify(depth);
                        if(!correct){
                                std::vector<int> belegung = sat.get_belegung();
                                bool end = last(belegung, depth);
                                int geaendert_ab = depth;
                                while(!sat.verify(geaendert_ab, depth) && !end){
                                        geaendert_ab = nextimp(sat,depth);
                                        belegung = sat.get_belegung();
                                        depth = belegung[0];
                                        sat.set_belegung(belegung);
                                        end = last(belegung, depth);
                                        //print(sat.get_belegung());
                                }
                                if (sat.verify() == false){
                                std::cout << "no solution found" << std::endl;
                                std::vector <int> empty;
                                return empty;
                                }                    
                        }
                }
                //print(sat.get_belegung());
        }

        return sat.get_belegung();
}

int next(std::vector<int>& belegung, const int depth){
        int geaendert = depth;
        for(int i = depth ; i > 0; i--){
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

int nextimp(SAT& sat, int depth){
        std::vector<int> belegung = sat.get_belegung();
        int pos = sat.backtrack_until();
        int geaendert_ab = pos;
        for(int i = depth ; i > pos; i--){
                belegung[i] = 2;
        }
        if (belegung[pos] == 0){
                belegung [pos] = 1;
        }
        else {
                geaendert_ab = next(belegung, pos);
        }
        belegung[0] = pos;
        sat.set_belegung(belegung);
        return geaendert_ab;
}

bool last(const std::vector<int>& belegung, const int depth){                        
        for(int i = 0; i < depth-1; i++){
                if (belegung[i]==0){
                        return false;
                }
        }
        return true;
}

void print(const std::vector<int>& vec){                               
        for(int i = 0; i < int(vec.size()); i++){
                std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
}
