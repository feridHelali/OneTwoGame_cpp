/**
 * @file test_players.cpp
 * @brief Unit tests for User and ComputerAI player classes.
 */
#include "TestFramework.h"
#include "kernel/User.h"
#include "kernel/ComputerAI.h"

// ── User ───────────────────────────────────────────────────────────

TEST_CASE("User getName returns username") {
    User u("Alice", []() { return Combination::Rock; });
    ASSERT_EQ(u.getName(), std::string("Alice"));
}

TEST_CASE("User getUsername returns same as getName") {
    User u("Bob", []() { return Combination::Paper; });
    ASSERT_EQ(u.getUsername(), u.getName());
}

TEST_CASE("User chooseHand delegates to callback") {
    int callCount = 0;
    User u("Tester", [&callCount]() {
        ++callCount;
        return Combination::Scissors;
    });

    Hand h = u.chooseHand();
    ASSERT_EQ(h.getCombination(), Combination::Scissors);
    ASSERT_EQ(callCount, 1);
}

TEST_CASE("User callback can return different values") {
    int round = 0;
    User u("Dynamic", [&round]() {
        return static_cast<Combination>(round++ % 3);
    });

    ASSERT_EQ(u.chooseHand().getCombination(), Combination::Rock);
    ASSERT_EQ(u.chooseHand().getCombination(), Combination::Scissors);
    ASSERT_EQ(u.chooseHand().getCombination(), Combination::Paper);
}

// ── ComputerAI ─────────────────────────────────────────────────────

TEST_CASE("ComputerAI default name is Computer") {
    ComputerAI ai;
    ASSERT_EQ(ai.getName(), std::string("Computer"));
}

TEST_CASE("ComputerAI custom name") {
    ComputerAI ai("DeepBlue");
    ASSERT_EQ(ai.getName(), std::string("DeepBlue"));
}

TEST_CASE("ComputerAI chooseHand returns valid combination") {
    ComputerAI ai;
    for (int i = 0; i < 100; ++i) {
        Combination c = ai.chooseHand().getCombination();
        ASSERT_TRUE(c == Combination::Rock ||
                    c == Combination::Scissors ||
                    c == Combination::Paper);
    }
}
