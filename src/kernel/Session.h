#ifndef SESSION_H
#define SESSION_H

#include "Move.h"
#include "IPlayer.h"
#include <vector>
#include <chrono>
#include <memory>
#include <functional>

/**
 * @file Session.h
 * @brief Orchestrates a complete game session of N rounds (default 10).
 *
 * The Session class is the **Façade** of the Kernel package.  It owns
 * the list of moves, keeps score, and determines the overall winner.
 * It delegates hand selection to IPlayer instances via polymorphism.
 *
 * @par Design Patterns
 * - **Façade** – single entry-point for running a game.
 * - **Observer (light)** – an optional round-completed callback lets
 *   external code (GUI or console) react without coupling.
 * - **Template Method (light)** – playRound() defines the skeleton;
 *   concrete players provide the variable step (chooseHand).
 *
 * @par SOLID
 * - **Single Responsibility** – manages session lifecycle only.
 * - **Open/Closed** – new player types plug in without changes.
 * - **Dependency Inversion** – depends on IPlayer, not concrete types.
 * - **Interface Segregation** – exposes only what consumers need.
 */
class Session {
public:
    /**
     * @brief Type alias for the round-completed notification.
     *
     * Parameters: round index (0-based), the Move just played.
     */
    using RoundCallback = std::function<void(int roundIndex, const Move& move)>;

    /** @brief Default number of rounds per session (from the UML: 10). */
    static constexpr int DEFAULT_ROUNDS = 10;

    /**
     * @brief Constructs a Session.
     * @param user     Shared pointer to the human player.
     * @param computer Shared pointer to the AI player.
     * @param rounds   Number of rounds (defaults to 10).
     */
    Session(std::shared_ptr<IPlayer> user,
            std::shared_ptr<IPlayer> computer,
            int rounds = DEFAULT_ROUNDS);

    /**
     * @brief Starts the session and plays all rounds sequentially.
     *
     * Each round:
     * 1. Both players choose a Hand.
     * 2. A Move is created and evaluated.
     * 3. The optional RoundCallback is invoked.
     */
    void start();

    /**
     * @brief Stops the session prematurely (sets running flag to false).
     */
    void stop();

    /**
     * @brief Determines the overall winner based on cumulative score.
     * @return Name of the winning player, or "Draw" if tied.
     */
    std::string whoWins() const;

    /** @brief Returns the user's total wins. */
    int getUserScore() const;

    /** @brief Returns the computer's total wins. */
    int getComputerScore() const;

    /** @brief Returns the number of draws. */
    int getDrawCount() const;

    /** @brief Returns a read-only reference to all played moves. */
    const std::vector<Move>& getMoves() const;

    /** @brief Returns the total number of rounds configured. */
    int getTotalRounds() const;

    /** @brief Returns the number of rounds played so far. */
    int getRoundsPlayed() const;

    /** @brief Returns true while the session is in progress. */
    bool isRunning() const;

    /**
     * @brief Registers a callback invoked after each round.
     * @param cb The callback function.
     */
    void onRoundCompleted(RoundCallback cb);

    /**
     * @brief Returns the wall-clock duration of the session.
     * @return Duration in seconds (0 if not yet started).
     */
    double getElapsedSeconds() const;

    /**
     * @brief Plays a single round and returns its result.
     *
     * This is useful for GUIs that drive rounds one at a time
     * instead of calling start() for the full batch.
     *
     * @return The Move that was just played.
     * @throws std::runtime_error if all rounds are already played.
     */
    Move playRound();

private:
    std::shared_ptr<IPlayer> user_;
    std::shared_ptr<IPlayer> computer_;

    std::vector<Move> moves_;  ///< Recorded moves (up to totalRounds_).
    int totalRounds_;          ///< Number of rounds to play.
    int userScore_;            ///< Cumulative user wins.
    int computerScore_;        ///< Cumulative computer wins.
    int drawCount_;            ///< Cumulative draws.
    bool running_;             ///< True while the session is in progress.

    RoundCallback roundCallback_; ///< Optional per-round notification.

    std::chrono::steady_clock::time_point startTime_;
    std::chrono::steady_clock::time_point endTime_;
};

#endif // SESSION_H
