#ifndef MOVE_H
#define MOVE_H

#include "Hand.h"
#include <string>

/**
 * @file Move.h
 * @brief Represents a single round (one confrontation of two Hands).
 *
 * A Move captures the two hands played in a round and determines the
 * outcome.  It is an immutable record once both hands are set, making
 * it safe to store in collections (e.g. inside Session).
 *
 * @par Design Patterns
 * - **Value Object** – a Move is identified by its data, not by an ID.
 * - **Information Expert** – the Move itself knows how to judge who won.
 *
 * @par SOLID
 * - **Single Responsibility** – encapsulates the outcome logic for one
 *   round.
 */

/**
 * @brief Enumerates the possible outcomes of a single move.
 */
enum class MoveResult {
    UserWins,     ///< The user's hand beats the computer's hand.
    ComputerWins, ///< The computer's hand beats the user's hand.
    Draw          ///< Both hands are identical – no winner.
};

/**
 * @brief Converts a MoveResult to a human-readable string.
 * @param result The result to convert.
 * @return "User Wins", "Computer Wins", or "Draw".
 */
inline std::string moveResultToString(MoveResult result) {
    switch (result) {
        case MoveResult::UserWins:     return "User Wins";
        case MoveResult::ComputerWins: return "Computer Wins";
        case MoveResult::Draw:         return "Draw";
    }
    return "Unknown";
}

/**
 * @class Move
 * @brief One round of the game – two hands and a result.
 */
class Move {
public:
    /**
     * @brief Constructs a Move from two pre-selected Hands.
     * @param userHand     The hand played by the human user.
     * @param computerHand The hand played by the computer AI.
     */
    Move(const Hand& userHand, const Hand& computerHand);

    /**
     * @brief Evaluates and returns who won this move.
     * @return A MoveResult indicating the outcome.
     */
    MoveResult getWhoWins() const;

    /** @brief Returns the user's Hand for this move. */
    Hand getUserHand() const;

    /** @brief Returns the computer's Hand for this move. */
    Hand getComputerHand() const;

private:
    Hand userHand_;     ///< The gesture played by the user.
    Hand computerHand_; ///< The gesture played by the AI.
};

#endif // MOVE_H
