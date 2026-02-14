/**
 * @file test_combination.cpp
 * @brief Unit tests for the Combination enum and helper functions.
 */
#include "TestFramework.h"
#include "kernel/Combination.h"

// ── beats() ────────────────────────────────────────────────────────

TEST_CASE("Rock beats Scissors") {
    ASSERT_TRUE(beats(Combination::Rock, Combination::Scissors));
}

TEST_CASE("Scissors beats Paper") {
    ASSERT_TRUE(beats(Combination::Scissors, Combination::Paper));
}

TEST_CASE("Paper beats Rock") {
    ASSERT_TRUE(beats(Combination::Paper, Combination::Rock));
}

TEST_CASE("Rock does NOT beat Paper") {
    ASSERT_FALSE(beats(Combination::Rock, Combination::Paper));
}

TEST_CASE("Scissors does NOT beat Rock") {
    ASSERT_FALSE(beats(Combination::Scissors, Combination::Rock));
}

TEST_CASE("Paper does NOT beat Scissors") {
    ASSERT_FALSE(beats(Combination::Paper, Combination::Scissors));
}

TEST_CASE("Same combination never beats itself (Rock)") {
    ASSERT_FALSE(beats(Combination::Rock, Combination::Rock));
}

TEST_CASE("Same combination never beats itself (Scissors)") {
    ASSERT_FALSE(beats(Combination::Scissors, Combination::Scissors));
}

TEST_CASE("Same combination never beats itself (Paper)") {
    ASSERT_FALSE(beats(Combination::Paper, Combination::Paper));
}

// ── combinationToString() ──────────────────────────────────────────

TEST_CASE("combinationToString Rock") {
    ASSERT_EQ(combinationToString(Combination::Rock), std::string("Rock"));
}

TEST_CASE("combinationToString Scissors") {
    ASSERT_EQ(combinationToString(Combination::Scissors), std::string("Scissors"));
}

TEST_CASE("combinationToString Paper") {
    ASSERT_EQ(combinationToString(Combination::Paper), std::string("Paper"));
}
