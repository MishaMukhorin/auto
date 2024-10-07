//
// Created by Misha on 02.10.2024.
//

#include "MooreMachine.h"
#include "MealyMachine.h"
#include <fstream>
#include <iostream>

MooreMachine::MooreMachine() = default;


MealyMachine MooreMachine::ToMealy() {
    MealyMachine newMachine;

    for (const Transition& tr : transitions) {
        if (states.contains(tr.toState))
        {
            std::string outSignal = states.at(tr.toState);
            Transition newTr(tr.fromState, tr.toState, tr.signal);
            newMachine.transitions.emplace(newTr, outSignal);
        }
    }
    newMachine.inState = inState;
    newMachine.inputSignals = inputSignals;
    for (const auto& [state, signal] : states) {
        newMachine.states.push_back(state);
    }

    return newMachine;
}


void MooreMachine::WriteCsv(const std::string& file) {
    std::ofstream f(file);
    std::vector<std::string> orderedActivators(inputSignals);
    std::sort(orderedActivators.begin(), orderedActivators.end());

    std::vector<std::string> orderedStates;
    orderedStates.push_back(inState);
    for (const auto& [state, outSignal] : states)
    {
        if (state != inState)
        {
            orderedStates.push_back(state);
        }
    }

    for (const std::string& state : orderedStates) {
        f << ";" << states[state];
    }
    f << std::endl;
    for (const std::string& state : orderedStates) {
        f << ";" << state;
    }
    f << std::endl;
    for (const std::string& activator : orderedActivators) {
        f << activator;
        for (const std::string& state : orderedStates) {
            auto it = std::find_if(transitions.begin(), transitions.end(),
                                   [&state, &activator](const Transition& tr) {
                                       return tr.fromState == state && tr.signal == activator;
                                   });
            if (it != transitions.end()) {
                f << ";" << it->toState;
            } else {
                f << ";";
            }
        }
        f << std::endl;
    }
    f.close();
}
