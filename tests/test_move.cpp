/**
 * @file test_move.cpp
 * @brief Unit tests for the Move class.
 */
#include "TestFramework.h"
#include "kernel/Move.h"

TEST_CASE("Move: Rock vs Scissors -> UserWins") {
    Move m(Hand(Combination::Rock), Hand(Combination::Scissors));
    ASSERT_EQ(m.getWhoWins(), MoveResult::UserWins);
}

TEST_CASE("Move: Scissors vs Rock -> ComputerWins") {
    Move m(Hand(Combination::Scissors), Hand(Combination::Rock));
    ASSERT_EQ(m.getWhoWins(), MoveResult::ComputerWins);
}

TEST_CASE("Move: Paper vs Paper -> Draw") {
    Move m(Hand(Combination::Paper), Hand(Combination::Paper));
    ASSERT_EQ(m.getWhoWins(), MoveResult::Draw);
}

TEST_CASE("Move stores user hand correctly") {
    Hand userHand(Combination::Paper);
    Hand compHand(Combination::Rock);
    Move m(userHand, compHand);
    ASSERT_EQ(m.getUserHand().getCombination(), Combination::Paper);
}

TEST_CASE("Move stores computer hand correctly") {
    Hand userHand(Combination::Paper);
    Hand compHand(Combination::Rock);
    Move m(userHand, compHand);
    ASSERT_EQ(m.getComputerHand().getCombination(), Combination::Rock);
}

TEST_CASE("moveResultToString UserWins") {
    ASSERT_EQ(moveResultToString(MoveResult::UserWins), std::string("User Wins"));
}

TEST_CASE("moveResultToString ComputerWins") {
    ASSERT_EQ(moveResultToString(MoveResult::ComputerWins), std::string("Computer Wins"));
}

TEST_CASE("moveResultToString Draw") {
    ASSERT_EQ(moveResultToString(MoveResult::Draw), std::string("Draw"));
}
