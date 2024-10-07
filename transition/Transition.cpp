//
// Created by Misha on 02.10.2024.
//

#include "Transition.h"

#include <utility>

Transition::Transition(std::string  from, std::string  to, std::string  act)
        : fromState(std::move(from)), toState(std::move(to)), signal(std::move(act)) {}


// Equality operator for unordered_set and unordered_map
bool Transition::operator==(const Transition& other) const {
    return fromState == other.fromState && toState == other.toState && signal == other.signal;
}

// Hash function for use in unordered_set and unordered_map
size_t Transition::hash() const {
    size_t hash_value = std::hash<std::string>()(fromState);
    hash_value ^= std::hash<std::string>()(toState) << 1;
    hash_value ^= std::hash<std::string>()(signal) << 2;
    return hash_value;
}