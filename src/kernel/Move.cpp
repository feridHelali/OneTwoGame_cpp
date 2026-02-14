#include "kernel/Move.h"

Move::Move(const Hand& userHand, const Hand& computerHand)
    : userHand_(userHand)
    , computerHand_(computerHand)
{}

MoveResult Move::getWhoWins() const {
    if (userHand_ == computerHand_) {
        return MoveResult::Draw;
    }
    if (beats(userHand_.getCombination(), computerHand_.getCombination())) {
        return MoveResult::UserWins;
    }
    return MoveResult::ComputerWins;
}

Hand Move::getUserHand() const {
    return userHand_;
}

Hand Move::getComputerHand() const {
    return computerHand_;
}
