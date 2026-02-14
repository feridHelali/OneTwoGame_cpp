/**
 * @file test_hand.cpp
 * @brief Unit tests for the Hand class.
 */
#include "TestFramework.h"
#include "kernel/Hand.h"

TEST_CASE("Hand default constructor gives Rock") {
    Hand h;
    ASSERT_EQ(h.getCombination(), Combination::Rock);
}

TEST_CASE("Hand explicit constructor stores combination") {
    Hand h(Combination::Paper);
    ASSERT_EQ(h.getCombination(), Combination::Paper);
}

TEST_CASE("Hand setCombination changes value") {
    Hand h(Combination::Rock);
    h.setCombination(Combination::Scissors);
    ASSERT_EQ(h.getCombination(), Combination::Scissors);
}

TEST_CASE("Hand equality operator - same") {
    Hand a(Combination::Paper);
    Hand b(Combination::Paper);
    ASSERT_TRUE(a == b);
}

TEST_CASE("Hand equality operator - different") {
    Hand a(Combination::Rock);
    Hand b(Combination::Paper);
    ASSERT_TRUE(a != b);
}

TEST_CASE("Hand::generateCombination returns valid combination") {
    // Generate many hands and verify they are all valid
    for (int i = 0; i < 100; ++i) {
        Hand h = Hand::generateCombination();
        Combination c = h.getCombination();
        ASSERT_TRUE(c == Combination::Rock ||
                    c == Combination::Scissors ||
                    c == Combination::Paper);
    }
}
