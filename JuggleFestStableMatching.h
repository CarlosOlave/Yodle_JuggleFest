//
//  StableMatching.h
//  JuggleFest
//
//  Created by Carlos Olave on 10/28/13.
//  Copyright (c) 2013 Carlos Olave. All rights reserved.
//

#ifndef __JuggleFest__StableMatching__
#define __JuggleFest__StableMatching__
#define loop(i,x) for(unsigned i=0; i< x; ++i)

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <algorithm>

struct juggler {
    
    std::string name;
    int total;
    int H;
    int E;
    int P;
    std::vector<std::string> circuits;
    std::map<std::string, int> calculatedCircuits;
};

struct circuit {
    
    int H;
    int E;
    int P;
};

class JuggleFestStableMatching {
    
    // juggler *temp = new juggler[4];
    std::map<std::string, std::vector<juggler>> circuitSolution;
    
    // The collection of circuits.
    std::map<std::string, circuit> circuits;
    
    // The collection of jugglers.
    std::map<std::string, juggler> jugglers;
    
    // The collection of circuit in order.
    std::vector<std::string> orderCircuits;
    
    // The collection of free jugglers to be match to a circuit.
    std::queue<std::string> freeJugglers;
    
    // The size of the number of jugglers to fit into a circuit.
    int circuitJugglerMaximumSize;
    
    // Provides a compare function for stable sorting.
    static bool StableCompare(const juggler &J1, const juggler &J2);
    
public:
    
    // Constructor
    JuggleFestStableMatching();
    
    // Destructor
    ~JuggleFestStableMatching();
    
    // Add a circuit to the collection
    void AddCircuit(std::string key, circuit c);
    
    // Add a juggler to the collection
    void AddJuggler(std::string key, juggler j);
    
    // Initialize
    void Initialize();
    
    // Matching algorithm
    void GaleShapleyAlgorithm();
    
    // Print
    void Print(std::string outputFileName);
};

#endif /* defined(__JuggleFest__StableMatching__) */
