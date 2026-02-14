/**
 * @file test_session.cpp
 * @brief Unit tests for the Session class.
 */
#include "TestFramework.h"
#include "kernel/Session.h"
#include "kernel/User.h"
#include "kernel/ComputerAI.h"
#include <memory>

/// Helper: creates a User that always plays Rock.
static std::shared_ptr<IPlayer> makeRockUser() {
    return std::make_shared<User>("RockFan", []() { return Combination::Rock; });
}

/// Helper: creates a User that always plays Scissors (acts as "computer").
static std::shared_ptr<IPlayer> makeScissorsBot() {
    return std::make_shared<User>("ScissorsBot", []() { return Combination::Scissors; });
}

/// Helper: creates a User that always plays Rock (acts as "computer").
static std::shared_ptr<IPlayer> makeRockBot() {
    return std::make_shared<User>("RockBot", []() { return Combination::Rock; });
}

// ── Session basics ─────────────────────────────────────────────────

TEST_CASE("Session default is 10 rounds") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp);
    ASSERT_EQ(s.getTotalRounds(), 10);
}

TEST_CASE("Session custom rounds") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 5);
    ASSERT_EQ(s.getTotalRounds(), 5);
}

TEST_CASE("Session starts with zero score") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp);
    ASSERT_EQ(s.getUserScore(), 0);
    ASSERT_EQ(s.getComputerScore(), 0);
    ASSERT_EQ(s.getDrawCount(), 0);
}

// ── Full session ───────────────────────────────────────────────────

TEST_CASE("Session: Rock vs Scissors -> user wins all 5 rounds") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 5);
    s.start();

    ASSERT_EQ(s.getUserScore(), 5);
    ASSERT_EQ(s.getComputerScore(), 0);
    ASSERT_EQ(s.getDrawCount(), 0);
    ASSERT_EQ(s.getRoundsPlayed(), 5);
    ASSERT_FALSE(s.isRunning());
    ASSERT_EQ(s.whoWins(), std::string("RockFan"));
}

TEST_CASE("Session: all draws when both play Rock") {
    auto user = makeRockUser();
    auto comp = makeRockBot();
    Session s(user, comp, 3);
    s.start();

    ASSERT_EQ(s.getDrawCount(), 3);
    ASSERT_EQ(s.getUserScore(), 0);
    ASSERT_EQ(s.getComputerScore(), 0);
    ASSERT_EQ(s.whoWins(), std::string("Draw"));
}

// ── playRound one at a time ────────────────────────────────────────

TEST_CASE("Session playRound increments scores correctly") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 2);

    Move m1 = s.playRound();
    ASSERT_EQ(m1.getWhoWins(), MoveResult::UserWins);
    ASSERT_EQ(s.getRoundsPlayed(), 1);

    Move m2 = s.playRound();
    ASSERT_EQ(m2.getWhoWins(), MoveResult::UserWins);
    ASSERT_EQ(s.getRoundsPlayed(), 2);
    ASSERT_FALSE(s.isRunning());
}

TEST_CASE("Session playRound throws when all rounds done") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 1);
    s.playRound();

    ASSERT_THROWS(s.playRound(), std::runtime_error);
}

// ── Round callback ─────────────────────────────────────────────────

TEST_CASE("Session round callback is invoked for each round") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 3);

    int callbackCount = 0;
    s.onRoundCompleted([&callbackCount](int, const Move&) {
        ++callbackCount;
    });

    s.start();
    ASSERT_EQ(callbackCount, 3);
}

// ── getMoves ───────────────────────────────────────────────────────

TEST_CASE("Session getMoves returns all played moves") {
    auto user = makeRockUser();
    auto comp = makeScissorsBot();
    Session s(user, comp, 4);
    s.start();

    ASSERT_EQ(static_cast<int>(s.getMoves().size()), 4);
}
