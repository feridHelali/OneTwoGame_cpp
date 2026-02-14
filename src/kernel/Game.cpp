#include "kernel/Game.h"
#include <stdexcept>
#include <sstream>

Game::Game(std::shared_ptr<IPlayer> user, std::shared_ptr<IPlayer> computer)
    : user_(std::move(user))
    , computer_(std::move(computer))
    , state_(GameState::Idle)
{}

void Game::newSession(int rounds) {
    currentSession_ = std::make_unique<Session>(user_, computer_, rounds);
    state_ = GameState::Running;

    emit("=== New Session (" + std::to_string(rounds) + " rounds) ===");

    // Wire per-round callback to the output
    currentSession_->onRoundCompleted(
        [this](int idx, const Move& move) {
            std::ostringstream oss;
            oss << "Round " << (idx + 1) << ": "
                << combinationToString(move.getUserHand().getCombination())
                << " vs "
                << combinationToString(move.getComputerHand().getCombination())
                << " -> " << moveResultToString(move.getWhoWins());
            emit(oss.str());
        });
}

Move Game::playSingleRound() {
    if (!currentSession_ || state_ != GameState::Running) {
        throw std::runtime_error("No active session.");
    }

    Move move = currentSession_->playRound();

    if (!currentSession_->isRunning()) {
        state_ = GameState::Finished;

        std::ostringstream oss;
        oss << "\n=== Session Over ===\n"
            << user_->getName()     << ": " << currentSession_->getUserScore()     << " wins\n"
            << computer_->getName() << ": " << currentSession_->getComputerScore() << " wins\n"
            << "Draws: " << currentSession_->getDrawCount() << "\n"
            << "Winner: " << currentSession_->whoWins();
        emit(oss.str());
    }

    return move;
}

GameState Game::getState() const {
    return state_;
}

Session* Game::getCurrentSession() const {
    return currentSession_.get();
}

void Game::setOutputCallback(OutputCallback cb) {
    outputCallback_ = std::move(cb);
}

void Game::emit(const std::string& msg) {
    if (outputCallback_) {
        outputCallback_(msg);
    }
}
