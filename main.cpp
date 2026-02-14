/**
 * @file main.cpp
 * @brief Console entry-point for the Rock-Scissors-Paper game.
 *
 * This file wires together the Kernel classes and provides a
 * text-based front-end.  When the SFML GUI is ready, a separate
 * `src/gui/main_gui.cpp` entry-point will reuse the same Kernel
 * through the Game / Session API.
 */

#include "kernel/Game.h"
#include "kernel/User.h"
#include "kernel/ComputerAI.h"

#include <iostream>
#include <limits>
#include <string>
#include <memory>

/**
 * @brief Reads a valid Combination choice from the console.
 * @return The Combination selected by the human player.
 *
 * Keeps prompting until the user enters 1, 2, or 3.
 */
static Combination readUserChoice() {
    int choice = 0;
    while (true) {
        std::cout << "  Choose: 1) Rock  2) Scissors  3) Paper  > ";
        if (std::cin >> choice && choice >= 1 && choice <= 3) {
            break;
        }
        std::cout << "  Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return static_cast<Combination>(choice - 1);
}

int main() {
    std::cout << "\n"
              << "  =============================================\n"
              << "       Rock - Scissors - Paper   (Console)\n"
              << "  =============================================\n\n";

    // ── Ask for player name ────────────────────────────────────────
    std::string username;
    std::cout << "  Enter your name: ";
    std::getline(std::cin, username);
    if (username.empty()) {
        username = "Player";
    }

    // ── Create players (Dependency Injection) ──────────────────────
    auto user     = std::make_shared<User>(username, readUserChoice);
    auto computer = std::make_shared<ComputerAI>();

    // ── Create Game and wire console output ────────────────────────
    Game game(user, computer);
    game.setOutputCallback([](const std::string& msg) {
        std::cout << "  " << msg << "\n";
    });

    // ── Game loop: play sessions until the user quits ──────────────
    std::string again = "y";
    while (again == "y" || again == "Y") {
        game.newSession();  // default 10 rounds

        while (game.getState() == GameState::Running) {
            game.playSingleRound();
        }

        std::cout << "\n  Play again? (y/n): ";
        std::cin >> again;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\n  Thanks for playing, " << username << "! Goodbye.\n\n";
    return 0;
}
