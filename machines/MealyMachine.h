//
// Created by Misha on 02.10.2024.
//

#ifndef AUTO_MEALYMACHINE_H
#define AUTO_MEALYMACHINE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "../transition/Transition.h"

class MooreMachine;  

class MealyMachine {
public:
    std::string inState;
    std::vector<std::string> inputSignals;
    std::vector<std::string> states;
    std::unordered_map<Transition, std::string> transitions;

    MealyMachine();

    MooreMachine ToMoore();
    void WriteCsv(const std::string& file);

private:
    [[nodiscard]] std::string getTransitionOutSignal(const Transition& tr);
};


#endif //AUTO_MEALYMACHINE_H
