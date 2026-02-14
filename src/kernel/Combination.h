#ifndef COMBINATION_H
#define COMBINATION_H

#include <string>
#include <stdexcept>

/**
 * @file Combination.h
 * @brief Defines the three possible hand gestures in Rock-Scissors-Paper.
 *
 * This is a strongly-typed enum (enum class) that represents the domain
 * value-object for the game.  Using an enum class instead of a plain enum
 * enforces type safety and prevents implicit conversions (Open/Closed
 * Principle – new combinations would require an explicit extension).
 *
 * @par Design Patterns
 * - **Value Object** – immutable, identity-less, compared by value.
 *
 * @par SOLID
 * - **Single Responsibility** – only models the three gestures.
 */
enum class Combination {
    Rock,      ///< Beats Scissors
    Scissors,  ///< Beats Paper
    Paper      ///< Beats Rock
};

/**
 * @brief Converts a Combination to its human-readable string.
 * @param c The combination to convert.
 * @return A string representation ("Rock", "Scissors", or "Paper").
 * @throws std::invalid_argument if the value is out of range.
 */
inline std::string combinationToString(Combination c) {
    switch (c) {
        case Combination::Rock:     return "Rock";
        case Combination::Scissors: return "Scissors";
        case Combination::Paper:    return "Paper";
    }
    throw std::invalid_argument("Unknown Combination value");
}

/**
 * @brief Determines whether the left combination beats the right one.
 * @param lhs The attacking combination.
 * @param rhs The defending combination.
 * @return true if @p lhs wins against @p rhs.
 *
 * The canonical rules are:
 * | lhs      | beats    |
 * |----------|----------|
 * | Rock     | Scissors |
 * | Scissors | Paper    |
 * | Paper    | Rock     |
 */
inline bool beats(Combination lhs, Combination rhs) {
    return (lhs == Combination::Rock     && rhs == Combination::Scissors) ||
           (lhs == Combination::Scissors && rhs == Combination::Paper)    ||
           (lhs == Combination::Paper    && rhs == Combination::Rock);
}

#endif // COMBINATION_H
