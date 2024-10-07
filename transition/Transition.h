//
// Created by Misha on 02.10.2024.
//

#ifndef AUTO_TRANSITION_H
#define AUTO_TRANSITION_H

#include <string>
#include <functional>

class Transition {
public:
    std::string fromState;
    std::string toState;
    std::string signal;

    Transition() = default;

    Transition(std::string from, std::string to, std::string act);

    bool operator==(const Transition& other) const;
    [[nodiscard]] size_t hash() const;

};


namespace std {
    template <>
    struct hash<Transition> {
        size_t operator()(const Transition& tr) const {
            return tr.hash();
        }
    };
}

#endif //AUTO_TRANSITION_H
