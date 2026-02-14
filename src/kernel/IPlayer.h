#ifndef IPLAYER_H
#define IPLAYER_H

#include "Hand.h"
#include <string>

/**
 * @file IPlayer.h
 * @brief Abstract interface for any participant (human or AI).
 *
 * This interface decouples the game logic from concrete player
 * implementations, allowing the Session / Move classes to operate on
 * any player type polymorphically.
 *
 * @par Design Patterns
 * - **Strategy** – concrete players implement different hand-selection
 *   strategies behind a uniform interface.
 * - **Interface Segregation** – minimal surface: name + choose.
 *
 * @par SOLID
 * - **Dependency Inversion** – high-level modules (Session, Move)
 *   depend on this abstraction rather than concrete classes.
 * - **Liskov Substitution** – any IPlayer subclass can replace another
 *   without breaking the game logic.
 */
class IPlayer {
public:
    virtual ~IPlayer() = default;

    /**
     * @brief Returns a display name for the player.
     * @return The player's name.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Asks the player to choose a hand for the current round.
     * @return The Hand chosen by this player.
     *
     * For a human player this would involve reading input;
     * for the AI it generates a random hand.
     */
    virtual Hand chooseHand() = 0;
};

#endif // IPLAYER_H
