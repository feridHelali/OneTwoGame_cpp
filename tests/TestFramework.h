#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

/**
 * @file TestFramework.h
 * @brief Minimal single-header unit-test framework (no external deps).
 *
 * Provides macros for defining test cases, assertions, and a runner.
 * Inspired by Catch2/doctest but deliberately tiny for educational use.
 *
 * Usage:
 * @code
 *   TEST_CASE("Rock beats Scissors") {
 *       ASSERT_TRUE(beats(Combination::Rock, Combination::Scissors));
 *   }
 *   // in main():  return TestRunner::instance().runAll();
 * @endcode
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Lightweight test-case registration and runner.
class TestRunner {
public:
    struct TestCase {
        std::string name;
        std::function<void()> body;
    };

    static TestRunner& instance() {
        static TestRunner runner;
        return runner;
    }

    void addTest(const std::string& name, std::function<void()> body) {
        tests_.push_back({name, std::move(body)});
    }

    /// @brief Runs all registered tests. Returns 0 on success, 1 on failure.
    int runAll() {
        int passed = 0, failed = 0;
        for (auto& tc : tests_) {
            try {
                tc.body();
                std::cout << "  [PASS] " << tc.name << "\n";
                ++passed;
            } catch (const std::exception& e) {
                std::cerr << "  [FAIL] " << tc.name << " - " << e.what() << "\n";
                ++failed;
            }
        }
        std::cout << "\n  Results: " << passed << " passed, "
                  << failed << " failed, "
                  << (passed + failed) << " total.\n";
        return failed == 0 ? 0 : 1;
    }

private:
    std::vector<TestCase> tests_;
};

/// @brief Helper for auto-registering a test case at static-init time.
struct TestRegistrar {
    TestRegistrar(const std::string& name, std::function<void()> body) {
        TestRunner::instance().addTest(name, std::move(body));
    }
};

// ── Macros ─────────────────────────────────────────────────────────

/// Two-level indirection so __COUNTER__ is fully expanded before paste.
#define TF_CAT_IMPL(a, b) a##b
#define TF_CAT(a, b) TF_CAT_IMPL(a, b)

/**
 * @brief Defines and auto-registers a test case.
 *
 * Usage: @code TEST_CASE("description") { ... assertions ... } @endcode
 *
 * Implementation: a helper macro (TEST_CASE_IMPL) receives the already-
 * expanded __COUNTER__ value so that the function name and registrar
 * share the same unique suffix.
 */
#define TEST_CASE_IMPL(testname, id)                                           \
    static void TF_CAT(_tf_func_, id)();                                       \
    static TestRegistrar TF_CAT(_tf_reg_, id)(                                 \
        testname, TF_CAT(_tf_func_, id));                                      \
    static void TF_CAT(_tf_func_, id)()

#define TEST_CASE(testname) TEST_CASE_IMPL(testname, __COUNTER__)

/// Asserts that an expression is true.
#define ASSERT_TRUE(expr)                                                \
    do {                                                                  \
        if (!(expr)) {                                                    \
            std::ostringstream oss;                                       \
            oss << "ASSERT_TRUE failed: " #expr " (" << __FILE__         \
                << ":" << __LINE__ << ")";                                \
            throw std::runtime_error(oss.str());                          \
        }                                                                 \
    } while (false)

/// Asserts that an expression is false.
#define ASSERT_FALSE(expr)                                               \
    do {                                                                  \
        if ((expr)) {                                                     \
            std::ostringstream oss;                                       \
            oss << "ASSERT_FALSE failed: " #expr " (" << __FILE__        \
                << ":" << __LINE__ << ")";                                \
            throw std::runtime_error(oss.str());                          \
        }                                                                 \
    } while (false)

/// Asserts that two values are equal.
#define ASSERT_EQ(a, b)                                                  \
    do {                                                                  \
        if (!((a) == (b))) {                                              \
            std::ostringstream oss;                                       \
            oss << "ASSERT_EQ failed: " #a " != " #b " (" << __FILE__   \
                << ":" << __LINE__ << ")";                                \
            throw std::runtime_error(oss.str());                          \
        }                                                                 \
    } while (false)

/// Asserts that two values are NOT equal.
#define ASSERT_NE(a, b)                                                  \
    do {                                                                  \
        if ((a) == (b)) {                                                 \
            std::ostringstream oss;                                       \
            oss << "ASSERT_NE failed: " #a " == " #b " (" << __FILE__   \
                << ":" << __LINE__ << ")";                                \
            throw std::runtime_error(oss.str());                          \
        }                                                                 \
    } while (false)

/// Asserts that a block throws a specific exception type.
#define ASSERT_THROWS(expr, ExType)                                      \
    do {                                                                  \
        bool caught = false;                                              \
        try { expr; } catch (const ExType&) { caught = true; }           \
        if (!caught) {                                                    \
            std::ostringstream oss;                                       \
            oss << "ASSERT_THROWS failed: " #expr " did not throw "      \
                << #ExType << " (" << __FILE__ << ":" << __LINE__ << ")"; \
            throw std::runtime_error(oss.str());                          \
        }                                                                 \
    } while (false)

#endif // TEST_FRAMEWORK_H
