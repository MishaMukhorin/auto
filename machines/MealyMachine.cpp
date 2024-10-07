//
// Created by Misha on 02.10.2024.
//

#include "MealyMachine.h"
#include "MooreMachine.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

MealyMachine::MealyMachine() = default;

std::string MealyMachine::getTransitionOutSignal(const Transition& tr)
{
    if (transitions.contains(tr))
    {
        return transitions.at(tr);
    }
    return "";
}

MooreMachine MealyMachine::ToMoore() {
    MooreMachine newMachine;
    std::map<std::string, std::vector<std::string>> stateMap;
    std::vector<std::tuple<std::string, std::string, Transition>> edgesToIterate;

    for (const std::string& state : states) {
        std::map<std::string, std::vector<Transition>> clusteredTransitions;

        for (const auto& [tr, outSignal] : transitions) {

            auto it = std::find_if(transitions.begin(), transitions.end(),
                                   [&state, &outSignal](const std::pair<Transition, std::string>& tran) {
                                       return tran.first.toState == state && tran.second == outSignal;
                                   });
            if (it != transitions.end())
            {
                clusteredTransitions[outSignal].push_back(tr);
            }
        }

        for (const auto& [outSignal, transitionsList] : clusteredTransitions)
        {
            std::string newStateName;
            newStateName.append(state);
            newStateName.append("_");
            newStateName.append(outSignal);

            newMachine.states[newStateName] = outSignal;
            stateMap[state].push_back(newStateName);

            for (const auto& tr : transitionsList) {
                edgesToIterate.emplace_back( newStateName, outSignal, tr);
            }
        }
    }

    for (const auto& [newFromStateName, outSignal, tr]: edgesToIterate)
    {
        if (stateMap.contains(tr.fromState))
        {
            for (const std::string& mooreFromState : stateMap[tr.fromState])
            {

                Transition newTr(mooreFromState, tr.toState+"_" + outSignal, tr.signal);
                newMachine.transitions.insert(newTr);
            }
        }
    }

    newMachine.inputSignals = inputSignals;
    return newMachine;
}

void MealyMachine::WriteCsv(const std::string& file) {
    std::ofstream f(file);
    std::vector<std::string> orderedActivators(inputSignals);

    std::vector<std::string> orderedStates(states);


    for (const std::string& state : orderedStates) {
        f << ";" << state;
    }
    f << std::endl;
    for (const std::string& activator : orderedActivators) {
        f << activator;
        for (const std::string& state : orderedStates) {
            auto it = std::find_if(transitions.begin(), transitions.end(),
                                   [&state, &activator](const std::pair<Transition, std::string>& tr) {
                                       return tr.first.fromState == state && tr.first.signal == activator;
                                   });
            if (it != transitions.end()) {
                f << ";" << it->first.toState << "/" << it->second;
            } else {
                f << ";";
            }
        }
        f << std::endl;
    }
    f.close();
}
