/**
 * @file test_game.cpp
 * @brief Unit tests for the Game class.
 */
#include "TestFramework.h"
#include "kernel/Game.h"
#include <memory>
#include <vector>

/// Helper: deterministic user (always Paper).
static std::shared_ptr<IPlayer> makePaperUser() {
    return std::make_shared<User>("PaperPal", []() { return Combination::Paper; });
}

/// Helper: deterministic AI (always Rock).
static std::shared_ptr<IPlayer> makeRockAI() {
    return std::make_shared<User>("RockAI", []() { return Combination::Rock; });
}

TEST_CASE("Game initial state is Idle") {
    Game g(makePaperUser(), makeRockAI());
    ASSERT_EQ(g.getState(), GameState::Idle);
}

TEST_CASE("Game newSession transitions to Running") {
    Game g(makePaperUser(), makeRockAI());
    g.newSession(3);
    ASSERT_EQ(g.getState(), GameState::Running);
}

TEST_CASE("Game playSingleRound works") {
    Game g(makePaperUser(), makeRockAI());
    g.newSession(2);

    Move m = g.playSingleRound();
    ASSERT_EQ(m.getWhoWins(), MoveResult::UserWins); // Paper beats Rock
}

TEST_CASE("Game transitions to Finished after all rounds") {
    Game g(makePaperUser(), makeRockAI());
    g.newSession(2);

    g.playSingleRound();
    g.playSingleRound();

    ASSERT_EQ(g.getState(), GameState::Finished);
}

TEST_CASE("Game output callback receives messages") {
    Game g(makePaperUser(), makeRockAI());

    std::vector<std::string> messages;
    g.setOutputCallback([&messages](const std::string& msg) {
        messages.push_back(msg);
    });

    g.newSession(1);
    g.playSingleRound();

    // At least the session-start message and round result
    ASSERT_TRUE(messages.size() >= 2);
}

TEST_CASE("Game playSingleRound throws without session") {
    Game g(makePaperUser(), makeRockAI());
    ASSERT_THROWS(g.playSingleRound(), std::runtime_error);
}
