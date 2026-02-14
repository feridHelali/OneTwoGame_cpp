#ifndef COMPUTER_AI_H
#define COMPUTER_AI_H

#include "IPlayer.h"

/**
 * @file ComputerAI.h
 * @brief AI opponent that selects a random hand each round.
 *
 * ComputerAI is the simplest Strategy implementation: pure randomness.
 * It satisfies the Liskov Substitution Principle – any code that works
 * with an IPlayer also works with ComputerAI without modification.
 *
 * @par Design Patterns
 * - **Strategy** – random selection strategy.
 * - **Null Object (light)** – always produces a valid Hand, never
 *   blocks or fails.
 *
 * @par SOLID
 * - **Single Responsibility** – only generates random hands.
 * - **Liskov Substitution** – drop-in replacement for any IPlayer.
 */
class ComputerAI : public IPlayer {
public:
    /**
     * @brief Constructs the AI with an optional display name.
     * @param name Display name (defaults to "Computer").
     */
    explicit ComputerAI(const std::string& name = "Computer");

    /** @copydoc IPlayer::getName */
    std::string getName() const override;

    /**
     * @copydoc IPlayer::chooseHand
     * @note Always returns a randomly-generated Hand.
     */
    Hand chooseHand() override;

private:
    std::string name_; ///< Display name of the AI player.
};

#endif // COMPUTER_AI_H
