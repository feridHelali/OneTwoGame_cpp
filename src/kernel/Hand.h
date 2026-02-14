#ifndef HAND_H
#define HAND_H

#include "Combination.h"

/**
 * @file Hand.h
 * @brief Represents a single hand gesture chosen during a move.
 *
 * A Hand wraps a Combination and can be explicitly set (for the User)
 * or randomly generated (for the Computer AI).
 *
 * @par Design Patterns
 * - **Value Object** – compared by the contained Combination.
 *
 * @par SOLID
 * - **Single Responsibility** – holds / generates one gesture.
 * - **Open/Closed** – new generation strategies can be introduced
 *   without modifying this class (e.g. via a Strategy injected in
 *   the player classes).
 */
class Hand {
public:
    /**
     * @brief Default-constructs a Hand with Rock.
     */
    Hand();

    /**
     * @brief Constructs a Hand with a specific Combination.
     * @param combination The gesture to store.
     */
    explicit Hand(Combination combination);

    /**
     * @brief Factory that creates a Hand with a random Combination.
     * @return A Hand containing Rock, Scissors, or Paper at random.
     */
    static Hand generateCombination();

    /**
     * @brief Returns the current combination held by this hand.
     * @return The stored Combination value.
     */
    Combination getCombination() const;

    /**
     * @brief Sets (overrides) the combination held by this hand.
     * @param combination The new gesture.
     */
    void setCombination(Combination combination);

    /** @brief Equality operator – compares by Combination value. */
    bool operator==(const Hand& other) const;

    /** @brief Inequality operator. */
    bool operator!=(const Hand& other) const;

private:
    Combination currentCombination_; ///< The gesture this hand represents.
};

#endif // HAND_H
