#include "kernel/User.h"

User::User(const std::string& username, InputCallback inputCb)
    : username_(username)
    , inputCallback_(std::move(inputCb))
{}

std::string User::getName() const {
    return username_;
}

Hand User::chooseHand() {
    return Hand(inputCallback_());
}

std::string User::getUsername() const {
    return username_;
}
