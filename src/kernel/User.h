#ifndef USER_H
#define USER_H

#include "IPlayer.h"
#include <string>
#include <functional>

/**
 * @file User.h
 * @brief Concrete human player that obtains its hand via an input callback.
 *
 * The User class separates *what* the player is (identity, credentials)
 * from *how* input is gathered (injected callback).  This makes it
 * testable without real I/O and GUI-agnostic.
 *
 * @par Design Patterns
 * - **Strategy** – the input callback is a strategy for hand selection.
 * - **Dependency Injection** – the input source is injected at construction.
 *
 * @par SOLID
 * - **Single Responsibility** – models user identity; delegates input.
 * - **Open/Closed** – new input methods require no changes to User.
 */
class User : public IPlayer {
public:
    /**
     * @brief Type alias for the input callback.
     *
     * The function is expected to return the Combination chosen by the
     * human player (e.g. by reading from std::cin or a GUI widget).
     */
    using InputCallback = std::function<Combination()>;

    /**
     * @brief Constructs a User with a name and an input strategy.
     * @param username   Display name (also serves as a simple ID).
     * @param inputCb    Callable that provides the user's choice.
     */
    User(const std::string& username, InputCallback inputCb);

    /** @copydoc IPlayer::getName */
    std::string getName() const override;

    /** @copydoc IPlayer::chooseHand */
    Hand chooseHand() override;

    /**
     * @brief Returns the username (alias for getName).
     * @return The username string.
     */
    std::string getUsername() const;

private:
    std::string username_;      ///< Display / identity name.
    InputCallback inputCallback_; ///< Strategy for obtaining user input.
};

#endif // USER_H
