//
// Created by Misha on 02.10.2024.
//

#ifndef AUTO_MACHINEREADER_H
#define AUTO_MACHINEREADER_H


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "MooreMachine.h"
#include "MealyMachine.h"

// Helper function to split a string by a delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Read Mealy machine from CSV file
MealyMachine readMealyCSV(const std::string& file) {
    std::ifstream infile(file);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + file);
    }

    std::string line;
    MealyMachine machine;
    bool firstLine = true;

    while (std::getline(infile, line)) {
        std::vector<std::string> tokens = split(line, ';');

        // First line contains the states
        if (firstLine) {
            machine.states.insert(machine.states.end(), tokens.begin() + 1, tokens.end());
            firstLine = false;
            continue;
        }

        // Process each subsequent line
        std::string signal = tokens[0];
        machine.inputSignals.push_back(signal);

        for (size_t i = 1; i < tokens.size(); ++i) {
            std::vector<std::string> transitionParts = split(tokens[i], '/');
            if (transitionParts.size() != 2) continue;

            std::string toState = transitionParts[0];
            std::string outSignal = transitionParts[1];
            // Create a transition and add it to the machine
            Transition transition(machine.states[i - 1], toState, signal);
            machine.transitions[transition] = outSignal;
        }
    }
    infile.close();
    return machine;
}

// Read Moore machine from CSV file
MooreMachine readMooreCSV(const std::string& file) {
    std::ifstream infile(file);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + file);
    }

    std::string line;
    MooreMachine machine;
    bool firstLine = true, secondLine = true;
    std::vector<std::string> states;
    std::vector<std::string> outputs;

    while (std::getline(infile, line)) {
        std::vector<std::string> tokens = split(line, ';');

        if (firstLine) {
            for (size_t i = 1; i < tokens.size(); ++i) {
                outputs.push_back(tokens[i]);
            }
            firstLine = false;
            continue;
        }

        if (secondLine) {
            for (size_t i = 1; i < tokens.size(); ++i) {
                states.push_back(tokens[i]);
                machine.states[states.back()] = outputs[i];
            }
            secondLine = false;
            continue;
        }

        std::string signal = tokens[0];
        machine.inputSignals.push_back(signal);

        for (size_t i = 1; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                Transition transition(states[i - 1], tokens[i], signal);
                machine.transitions.insert(transition);
            }
        }
    }
    infile.close();
    return machine;
}

#endif //AUTO_MACHINEREADER_H
