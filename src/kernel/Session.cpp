#include "kernel/Session.h"
#include <stdexcept>

Session::Session(std::shared_ptr<IPlayer> user,
                 std::shared_ptr<IPlayer> computer,
                 int rounds)
    : user_(std::move(user))
    , computer_(std::move(computer))
    , totalRounds_(rounds)
    , userScore_(0)
    , computerScore_(0)
    , drawCount_(0)
    , running_(false)
{
    moves_.reserve(static_cast<size_t>(totalRounds_));
}

void Session::start() {
    running_ = true;
    startTime_ = std::chrono::steady_clock::now();

    while (running_ && static_cast<int>(moves_.size()) < totalRounds_) {
        playRound();
    }

    running_ = false;
    endTime_ = std::chrono::steady_clock::now();
}

void Session::stop() {
    running_ = false;
    endTime_ = std::chrono::steady_clock::now();
}

Move Session::playRound() {
    if (static_cast<int>(moves_.size()) >= totalRounds_) {
        throw std::runtime_error("All rounds have already been played.");
    }

    if (!running_) {
        running_ = true;
        startTime_ = std::chrono::steady_clock::now();
    }

    Hand userHand     = user_->chooseHand();
    Hand computerHand = computer_->chooseHand();

    Move move(userHand, computerHand);
    moves_.push_back(move);

    switch (move.getWhoWins()) {
        case MoveResult::UserWins:     ++userScore_;     break;
        case MoveResult::ComputerWins: ++computerScore_; break;
        case MoveResult::Draw:         ++drawCount_;     break;
    }

    if (roundCallback_) {
        roundCallback_(static_cast<int>(moves_.size()) - 1, move);
    }

    if (static_cast<int>(moves_.size()) >= totalRounds_) {
        running_ = false;
        endTime_ = std::chrono::steady_clock::now();
    }

    return move;
}

std::string Session::whoWins() const {
    if (userScore_ > computerScore_) {
        return user_->getName();
    }
    if (computerScore_ > userScore_) {
        return computer_->getName();
    }
    return "Draw";
}

int Session::getUserScore() const {
    return userScore_;
}

int Session::getComputerScore() const {
    return computerScore_;
}

int Session::getDrawCount() const {
    return drawCount_;
}

const std::vector<Move>& Session::getMoves() const {
    return moves_;
}

int Session::getTotalRounds() const {
    return totalRounds_;
}

int Session::getRoundsPlayed() const {
    return static_cast<int>(moves_.size());
}

bool Session::isRunning() const {
    return running_;
}

void Session::onRoundCompleted(RoundCallback cb) {
    roundCallback_ = std::move(cb);
}

double Session::getElapsedSeconds() const {
    if (running_) {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - startTime_).count();
    }
    return std::chrono::duration<double>(endTime_ - startTime_).count();
}
