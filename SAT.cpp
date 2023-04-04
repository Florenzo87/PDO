#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>
#include "SAT.hpp"
using namespace std;



SAT::SAT(char const * filename)                                                 //baut ein SAT Element durch lesen eines textdokuments
{
     //std::vector<std::vector<int>> sat = {};
     //int var, clauses;
     string line;
     ifstream myfile (filename);
     if (myfile.is_open())
     {
          while ( getline (myfile,line) )
          {
                    std::istringstream is(line);
                    string c;
                    is >> c;
                    if (c == "p"){
                         string cnf;
                         is >> cnf >> var >> clauses;
                         //cout << var << " " << clauses << endl;
                         break;
                    }
          }
          for (int i=0; i < var+1; i++){
               belegung.push_back(2);
          }
          while ( getline (myfile,line) )
          {
                    std::vector<int> vec = {};
                    std::istringstream is(line);
                    int n;
                    while( is >> n ) {
                         vec.push_back(n);
                         //cout << n << " ";
                    }
                    Clause cls = Clause(vec);
                    sat.push_back(cls);
                    //cout << endl;
          }
          myfile.close();
     }

     else cout << "Unable to open file"; 

}

void SAT::print(){                                //drückt ein SAT Element auf die konsole
     cout << var << clauses << endl;
     for (int i=0; i < clauses; i++){
          sat[i].print();
     }
}

bool SAT::verify(){                               //überprüft ob die Besetzung des SAT gültig ist
     bool correct = true;
     for (int i=0; i < clauses; i++){
          if(sat[i].verify(belegung) == false){
               correct = false;
          }
     }
     return correct;
}

int SAT::biggesterror(){                          //findet die grösste Variable die in eine fehlerhafte Klausel ist
     int error = 0;
     for (int i=0; i < clauses; i++){
          int neuerror = sat[i].biggesterror(belegung);
          cout << neuerror << endl;
          if(neuerror > error){
               error = neuerror;
          }
     }
     return error;
}

void SAT::set_belegung(std::vector<int> neubelegung){       //ändert die Belegung zum gegebenen Vektor, Achtung muss die richtige Länge haben
     belegung = neubelegung;
}

void SAT::set_belegung(int pos, int val){                   //ändert der Wert der Belegung an der gegebene Stelle zum gegebenen Wert
     belegung[pos] = val;
}

void SAT::set_belegung(int pos){                            //ändert der Wert der Belegung an der gegebenen Stelle zum entgegengesetztes Wert, 0->1 1->0 2->2
     if(belegung[pos] == 0){
               belegung[pos] = 1;
     }
     if(belegung[pos] == 1){
               belegung[pos] = 0;
     }
}

std::vector<int> SAT::get_belegung(){                       //wirft der aktuelle Belegung zurück
     return belegung;
}

int SAT::variables(){                                       //wirft der Anzahl an Variablen zurück
     return var;
}
