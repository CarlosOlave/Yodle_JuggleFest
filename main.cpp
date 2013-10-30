//
//  main.cpp
//  JuggleFest
//
//  Created by Carlos Olave on 10/26/13.
//  Copyright (c) 2013 Carlos Olave. All rights reserved.
//

#include "JuggleFestStableMatching.h"
#include <iostream>
#include <fstream>

std::vector<std::string> &Split(std::string &str, char delim, std::vector<std::string> &elems) {
    
    size_t found;
    found = str.find_first_of(delim);
    while(found != std::string::npos){
        if(found > 0){
            elems.push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(delim);
    }
    if(str.length() > 0){
        elems.push_back(str);
    }
    
    return elems;
}

int main(int argc, const char * argv[]) {
    
    std::string inputFileName = "jugglefest.txt";
    std::string outputFileName = "output.txt";
    if (argc > 1)
        inputFileName = argv[1];
    if (argc > 2)
        outputFileName = argv[2];
        
    std::ifstream infile;
    infile.open(inputFileName, std::ifstream::in);
    
    std::string line;
    std::vector<std::string> elems;
    std::vector<std::string> jugglersAbilities;
    std::vector<std::string> jugglersCircuits;
    
    JuggleFestStableMatching jftm;
    
    // Construct circuits and jugglers.
    while(std::getline(infile, line)) {
    
        if (line == "")
            continue;
        
        elems = Split(line, ' ', elems);
        
        if (elems[0] == "C") {
        
            //C C0 H:7 E:7 P:10
            jugglersAbilities = Split(elems[2], ':', jugglersAbilities);
            jugglersAbilities = Split(elems[3], ':', jugglersAbilities);
            jugglersAbilities = Split(elems[4], ':', jugglersAbilities);
            circuit c;
            c.H = atoi(jugglersAbilities[1].c_str());
            c.E = atoi(jugglersAbilities[3].c_str());
            c.P = atoi(jugglersAbilities[5].c_str());
            jftm.AddCircuit(elems[1], c);
            jugglersAbilities.clear();
            
        } else if (elems[0] == "J") {
            
            //J J0 H:3 E:9 P:2 C2,C0,C1
            jugglersAbilities = Split(elems[2], ':', jugglersAbilities);
            jugglersAbilities = Split(elems[3], ':', jugglersAbilities);
            jugglersAbilities = Split(elems[4], ':', jugglersAbilities);
            jugglersCircuits = Split(elems[5], ',', jugglersCircuits);
            juggler j;
            j.H = atoi(jugglersAbilities[1].c_str());
            j.E = atoi(jugglersAbilities[3].c_str());
            j.P = atoi(jugglersAbilities[5].c_str());
            j.circuits = jugglersCircuits;
            j.name = elems[1];
            jftm.AddJuggler(elems[1], j);
            jugglersAbilities.clear();
            jugglersCircuits.clear();
        }
        
        elems.clear();
    }
    infile.close();
    
    jftm.Initialize();
    jftm.GaleShapleyAlgorithm();
    jftm.Print(outputFileName);
    
    return 0;
}

