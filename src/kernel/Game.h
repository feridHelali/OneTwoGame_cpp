#ifndef GAME_H
#define GAME_H

#include "Session.h"
#include "User.h"
#include "ComputerAI.h"
#include <memory>
#include <functional>

/**
 * @file Game.h
 * @brief Top-level controller that manages game state and sessions.
 *
 * The Game class acts as a **Mediator** between the players and the
 * Session.  It owns the lifecycle: create players → run session →
 * display results → optionally replay.
 *
 * The class is intentionally GUI-agnostic: all I/O is handled through
 * injectable callbacks so the same Game instance works for console,
 * SFML, or any other front-end.
 *
 * @par Design Patterns
 * - **Mediator** – coordinates Session and IPlayer interaction.
 * - **State (light)** – tracks Running / Stopped / Finished states.
 * - **Factory Method (light)** – createSession() builds the session.
 *
 * @par SOLID
 * - **Single Responsibility** – game lifecycle management only.
 * - **Dependency Inversion** – depends on IPlayer interface.
 */

/**
 * @brief Enumerates the possible states of the Game.
 */
enum class GameState {
    Idle,     ///< Before any session starts.
    Running,  ///< A session is in progress.
    Finished  ///< The session has ended (results available).
};

/**
 * @class Game
 * @brief Manages the overall game lifecycle.
 */
class Game {
public:
    /**
     * @brief Type alias for a display/output callback.
     *
     * Used to send textual messages to the front-end (console or GUI).
     */
    using OutputCallback = std::function<void(const std::string&)>;

    /**
     * @brief Constructs a Game with the two players.
     * @param user     The human player.
     * @param computer The AI player.
     */
    Game(std::shared_ptr<IPlayer> user, std::shared_ptr<IPlayer> computer);

    /**
     * @brief Creates and starts a new Session with the configured rounds.
     * @param rounds Number of rounds (default 10).
     */
    void newSession(int rounds = Session::DEFAULT_ROUNDS);

    /**
     * @brief Plays a single round in the current session.
     * @return The Move that was just played.
     * @throws std::runtime_error if no session is active or all rounds done.
     */
    Move playSingleRound();

    /** @brief Returns the current game state. */
    GameState getState() const;

    /** @brief Returns a pointer to the current session (nullptr if none). */
    Session* getCurrentSession() const;

    /**
     * @brief Registers an output callback for textual messages.
     * @param cb The callback function.
     */
    void setOutputCallback(OutputCallback cb);

private:
    std::shared_ptr<IPlayer> user_;
    std::shared_ptr<IPlayer> computer_;
    std::unique_ptr<Session> currentSession_;
    GameState state_;
    OutputCallback outputCallback_;

    /**
     * @brief Sends a message through the output callback (if registered).
     * @param msg The message to display.
     */
    void emit(const std::string& msg);
};

#endif // GAME_H
