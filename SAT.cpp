#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "SAT.hpp"



SAT::SAT(const std::string filename)                                               //baut ein SAT Element durch lesen eines textdokuments
{
     //std::vector<std::vector<int>> sat = {};
     //int var, clauses;
     std::string line;
     std::ifstream myfile (filename);
     if (myfile.is_open())
     {
          while ( getline (myfile,line) )
          {
                    std::istringstream is(line);
                    std::string c;
                    is >> c;
                    if (c == "p"){
                         std::string cnf;
                         is >> cnf >> var >> clauses;
                         //std::cout << var << " " << clauses << std::endl;
                         break;
                    }
          }
          for (int i=0; i < var+1; i++){
               belegung.push_back(2);
               std::vector<int> empty;
               clauseln_der_variable.push_back(empty);    
          }
          int clausel = 0;
          while ( getline (myfile,line) )
          {
                    std::vector<int> vec = {};
                    std::istringstream is(line);
                    int n;
                    while( is >> n ) {
                         if (n != 0){
                              vec.push_back(n);
                              clauseln_der_variable[std::abs(n)].push_back(clausel);    
                         }
                         //std::cout << n << " ";
                    }
                    Clause cls = Clause(vec);
                    sat.push_back(cls);
                    clausel += 1;                      
          }
          myfile.close();
     }

     else std::cout << "Unable to open file"; 

}

void SAT::print() const{                                //drückt ein SAT Element auf die konsole
     std::cout << var << clauses << std::endl;
     for (int i=0; i < clauses; i++){
          sat[i].print();
     }
}

bool SAT::verify() const{                               //überprüft ob die Besetzung des SAT gültig ist
     bool correct = true;
     for (int i=0; i < clauses; i++){
          if(sat[i].verify(belegung) == false){
               correct = false;
          }
     }
     return correct;
}

bool SAT::verify(const int zuletz_geaenderte_variable) const{                               //überprüft ob die Besetzung des SAT gültig ist
     bool correct = true;
     for (int i=0; i < int(clauseln_der_variable[zuletz_geaenderte_variable].size()); i++){
          if(sat[clauseln_der_variable[zuletz_geaenderte_variable][i]].verify(belegung) == false){
               correct = false;
          }
     }
     return correct;
}

bool SAT::verify(const int erste_geaenderte_variable, const int letzte_geaenderte_variable) const{                               //überprüft ob die Besetzung des SAT gültig ist
     bool correct = true;
     for (int variable = erste_geaenderte_variable; variable < letzte_geaenderte_variable+1; variable++){
          for (int i=0; i < int(clauseln_der_variable[variable].size()); i++){
               if(sat[clauseln_der_variable[variable][i]].verify(belegung) == false){
                    correct = false;
               }
          }
     }
     return correct;
}


int SAT::backtrack_until() const{                          //findet die kleinste grösste Variable die in eine fehlerhafte Klausel ist
     int error = var;
     for (int i=0; i < clauses; i++){
          if(sat[i].verify(belegung) == 0){
               //std::cout << i << " " << error << std::endl;
               error = std::min(error, sat[i].biggesterror(belegung));
          }
     }
     return error;
}

void SAT::set_belegung(const std::vector<int>& neubelegung){       //ändert die Belegung zum gegebenen Vektor, Achtung muss die richtige Länge haben
     belegung = neubelegung;
}

void SAT::set_belegung(const int pos, const int val){                   //ändert der Wert der Belegung an der gegebene Stelle zum gegebenen Wert
     belegung[pos] = val;
}

void SAT::set_belegung(const int pos){                            //ändert der Wert der Belegung an der gegebenen Stelle zum entgegengesetztes Wert, 0->1 1->0 2->2
     if(belegung[pos] == 0){
               belegung[pos] = 1;
     }
     if(belegung[pos] == 1){
               belegung[pos] = 0;
     }
}

std::vector<int> SAT::get_belegung() const{                       //wirft der aktuelle Belegung zurück
     return belegung;
}

int SAT::variables() const{                                       //wirft der Anzahl an Variablen zurück
     return var;
}
