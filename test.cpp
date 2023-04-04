#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <vector>
#include <iostream>
#include <string>
#include "SAT.hpp"
using namespace std;

SAT backtrackingnaiv(SAT sat, int pos);
std::vector<int> backtracking(SAT sat);
void print(std::vector<int> vec);
std::vector<int> gggonext(SAT sat, int depth);
bool last(std::vector<int> belegung, int depth);
std::vector<int> gggonextimp(SAT sat, int depth);


int main () {                                                   //liest text aus den Dokument inst.txt und baut eine SAT Klasse dafür, ruft dann ein backtracking auf um eine Lösung zu finden
        SAT sat1 = SAT("inst.txt");                             //es müsste noch geändert werden damit der Name des Dokuments aus den input kommt
        std::vector<int> losung = backtracking(sat1);
        print(losung);
        return 0;
}


std::vector<int> backtracking(SAT sat){                         //setzt für jede Variable die Besetzung als falsch, falls ein Problem auftritt, versucht es richtig einzusetzen
        int var = sat.variables();
        for (int i = 0; i < var+1; i++){
                sat.set_belegung(i, 0);
                bool correct = sat.verify();
                //cout << correct << endl;
                if(correct == 0){
                        cout << "incorrect" << endl;
                        sat.set_belegung(i, 1);
                        correct = sat.verify();
                        cout << correct << endl;
                        if(correct == 0){
                                print(sat.get_belegung());
                                sat = backtrackingnaiv(sat, i);         //falls weder falsch oder richtig gültig sind, geht es zur nächste besetzung bis er eine richtige findet
                        }
                }
                print(sat.get_belegung());
        }

        return sat.get_belegung();
}

SAT backtrackingnaiv(SAT sat, int depth){                               //ruft die nächste Besetzung auf bis es eine gültige findet
        std::vector<int> belegung = sat.get_belegung();
        bool end = last(belegung, depth);
        while(sat.verify() == 0 & end == 0){
                //print(sat.get_belegung());
                std::vector<int> belegung = gggonextimp(sat,depth);
                sat.set_belegung(belegung);
                end = last(belegung, depth);
                if (end == true){
                        cout << "END" << endl;
                }
                if (sat.verify() == true){
                        cout << "TRUE" << endl;
                        break;
                }
                print(sat.get_belegung());
        }
        if (sat.verify() == false){
        cout << "no solution found" << endl;
        }
        return sat;
}


std::vector<int> gggonext(SAT sat, int depth){                          //findet die nächste Besetzung abhängig vn der tiefe der Suche und der aktuelle Besetzung
        std::vector<int> belegung = sat.get_belegung();
        for(int i = depth ; i > 0; i--){
                //cout << belegung[i] << endl;
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

std::vector<int> gggonextimp(SAT sat, int depth){                          //findet die nächste Besetzung abhängig vn der tiefe der Suche und der aktuelle Besetzung
        std::vector<int> belegung = sat.get_belegung();
        int pos = sat.biggesterror();
        cout << pos << endl;
        for(int i = depth ; i > pos-1; i--){
                //cout << belegung[i] << endl;
                belegung[i] = 0;
        if (belegung [pos] = 0){
                belegung [pos] = 1;
                }
        else if (belegung [pos] = 1){
                belegung[pos]=0;
                belegung[pos-1]=1;
                }
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
                cout << vec[i] << " ";
        }
        cout << endl;
}

