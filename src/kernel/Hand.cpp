#include "kernel/Hand.h"
#include <random>

Hand::Hand() : currentCombination_(Combination::Rock) {}

Hand::Hand(Combination combination) : currentCombination_(combination) {}

Hand Hand::generateCombination() {
    // Thread-local random engine seeded once per thread
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 2);

    return Hand(static_cast<Combination>(dist(rng)));
}

Combination Hand::getCombination() const {
    return currentCombination_;
}

void Hand::setCombination(Combination combination) {
    currentCombination_ = combination;
}

bool Hand::operator==(const Hand& other) const {
    return currentCombination_ == other.currentCombination_;
}

bool Hand::operator!=(const Hand& other) const {
    return !(*this == other);
}
