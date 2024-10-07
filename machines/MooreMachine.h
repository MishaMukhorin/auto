//
// Created by Misha on 02.10.2024.
//

#ifndef AUTO_MOOREMACHINE_H
#define AUTO_MOOREMACHINE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>
#include "../transition/Transition.h"


class MealyMachine;

class MooreMachine {
public:
    std::vector<std::string> inputSignals;
    std::unordered_map<std::string, std::string> states;
    std::unordered_set<Transition> transitions;

    MooreMachine();

    MealyMachine ToMealy();
    void WriteCsv(const std::string& file);
};


#endif //AUTO_MOOREMACHINE_H
