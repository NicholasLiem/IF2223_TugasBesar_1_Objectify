#include "../../lib/entities/Combo.hpp"

#include <iostream>
#include <vector>
using namespace std;


vector<Combo*> Combo::combos;

Combo::Combo(string name) : name(name){};

Combo::Combo(Combo& other) : name(other.name){};

void Combo::registerCombo(Combo* combo){
    Combo::combos.push_back(combo);
}

void Combo::clearCombos(){
    Combo::combos.clear();
}

vector<Combo*>& Combo::getCombos(){
    return Combo::combos;
}



