/**
 * @file test_main.cpp
 * @brief Test runner entry-point – just invokes all auto-registered tests.
 */
#include "TestFramework.h"

int main() {
    std::cout << "\n  ===== Rock-Scissors-Paper Unit Tests =====\n\n";
    return TestRunner::instance().runAll();
}
