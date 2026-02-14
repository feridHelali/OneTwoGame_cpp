#include "kernel/ComputerAI.h"

ComputerAI::ComputerAI(const std::string& name)
    : name_(name)
{}

std::string ComputerAI::getName() const {
    return name_;
}

Hand ComputerAI::chooseHand() {
    return Hand::generateCombination();
}
