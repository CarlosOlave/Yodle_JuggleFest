//
//  StableMatching.cpp
//  JuggleFest
//
//  Created by Carlos Olave on 10/28/13.
//  Copyright (c) 2013 Carlos Olave. All rights reserved.
//

#include "JuggleFestStableMatching.h"

// Constructor
JuggleFestStableMatching::JuggleFestStableMatching() {
    
    circuitJugglerMaximumSize = 0;
}

// Destructor
JuggleFestStableMatching::~JuggleFestStableMatching() {
    
    orderCircuits.clear();
    jugglers.clear();
    circuits.clear();
    circuitSolution.clear();
}

// Setup data
void JuggleFestStableMatching::Initialize() {
    
    if (circuits.size() != 0 &&
        jugglers.size() != 0) {
        
        circuitJugglerMaximumSize = (int)jugglers.size()/(int)circuits.size();
    }
}

// Implements a generalize version of the Gale Sharpley algorithm
// describe at http://en.wikipedia.org/wiki/Stable_marriage_problem
void JuggleFestStableMatching::GaleShapleyAlgorithm() {
    
    std::string freeJugglerKey = "";
    std::string freeJugglerCircuit = "";
    
    // true iff ∃ a juggler who is not matched to a circuit.
    while (!freeJugglers.empty()) {
        
        freeJugglerKey = freeJugglers.front();
        freeJugglers.pop();
        juggler j = jugglers[freeJugglerKey];
        loop(i, j.circuits.size()) {
            
            freeJugglerCircuit = j.circuits[i];
            j.total = j.calculatedCircuits[freeJugglerCircuit];
            if ((circuitSolution.find(freeJugglerCircuit) == circuitSolution.end()) ||
                (circuitSolution[freeJugglerCircuit].size() < circuitJugglerMaximumSize)) {
                
                circuitSolution[freeJugglerCircuit].push_back(j);
                std::stable_sort(circuitSolution[freeJugglerCircuit].begin(), circuitSolution[freeJugglerCircuit].end(), JuggleFestStableMatching::StableCompare);
                break;
            }
            else {
                
                int lowestIndex = (int)circuitSolution[freeJugglerCircuit].size()-1;
                int lowestJugglerMatchKey = circuitSolution[freeJugglerCircuit].at(lowestIndex).total;
                int currentJugglerKey = j.calculatedCircuits[freeJugglerCircuit];
                if (lowestJugglerMatchKey < currentJugglerKey) {
                
                    std::string lowestJugglerName = circuitSolution[freeJugglerCircuit].at(lowestIndex).name;
                    freeJugglers.push(lowestJugglerName);
                    circuitSolution[freeJugglerCircuit].erase(--circuitSolution[freeJugglerCircuit].end());
                    circuitSolution[freeJugglerCircuit].push_back(j);
                    std::stable_sort(circuitSolution[freeJugglerCircuit].begin(), circuitSolution[freeJugglerCircuit].end(), JuggleFestStableMatching::StableCompare);
                    break;
                }
            }
        }
    }
}

// Add a circuit to the collection.
void JuggleFestStableMatching::AddCircuit(std::string key, circuit c) {
    
    circuits[key] = c;
    orderCircuits.push_back(key);
}

// Add a juggler to the collection.
void JuggleFestStableMatching::AddJuggler(std::string key, juggler j) {
    
    loop(i, j.circuits.size()) {
        
        circuit c = circuits[j.circuits[i]];
        int H = j.H*c.H;
        int E = j.E*c.E;
        int P = j.P*c.P;
        j.calculatedCircuits[j.circuits[i]] = H + E + P;
    }
    
    freeJugglers.push(key);
    jugglers[key] = j;
}

// Prints solution.
void JuggleFestStableMatching::Print(std::string outputFileName) {
    
    std::ofstream outputFile;
    outputFile.open(outputFileName);
    int total = 0;
    loop(i1, orderCircuits.size()) {
    
        //std::cout<<orderCircuits[i1];
        outputFile<<orderCircuits[i1]<<" ";
        loop(i2, circuitSolution[orderCircuits[i1]].size()) {
            
            outputFile<<circuitSolution[orderCircuits[i1]][i2].name<<" ";
            if (orderCircuits[i1] == "C1970") {
                
                std::string temp = circuitSolution[orderCircuits[i1]][i2].name.substr(1);
                int tempValue = atoi(temp.c_str());
                total+=tempValue;
            }
            loop(i3, circuitSolution[orderCircuits[i1]][i2].circuits.size()) {
                
                std::string key = circuitSolution[orderCircuits[i1]][i2].circuits[i2];
                outputFile<<key<<":"<<circuitSolution[orderCircuits[i1]][i2].calculatedCircuits[key]<<" ";
            }
        }
        //std::cout<<std::endl;
        outputFile<<std::endl;
    }
    outputFile<<total<<std::endl;
    outputFile.close();
}

// Stable sort.
bool JuggleFestStableMatching::StableCompare(const juggler &J1, const juggler &J2) {
    
    return J1.total > J2.total;
}