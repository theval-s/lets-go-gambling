//
// Created by val on 3/18/25.
//

#include <SFML/Graphics.hpp>
#include "state_machine.hpp"

#include "game.hpp"

////////////////////////////////////////////////////////
// StartState
////////////////////////////////////////////////////////
void StartState::initializeStartState() {
}

void StartState::update(float deltaTime, SlotMachine::Machine &slots) {
}

void StartState::handleInput(SlotMachine::Machine &slots) {
    if (game->isPlayButtonClicked()) {
        //TODO: implement balance? freespins???
        game->changeState(std::make_unique<SpinState>(game, slots));
    }
}


////////////////////////////////////////////////////////
// SpinState
////////////////////////////////////////////////////////


void SpinState::update(float deltaTime, SlotMachine::Machine &slots) {
    slots.update(deltaTime);
    if (spinTimer.getElapsedTime().asSeconds() > spinDuration || !isSpinning) slots.stopSpinning();
    if (!slots.isAnySpinning()) {
        game->changeState(std::make_unique<ResultState>(game, slots));
    }
}

void SpinState::handleInput(SlotMachine::Machine &slots) {
    if (game->isStopButtonClicked()) {
        isSpinning = false;
        slots.stopSpinning();
    }
}


////////////////////////////////////////////////////////
// EndState
////////////////////////////////////////////////////////

ResultState::ResultState(Game *game, SlotMachine::Machine &slots) : game(game) {
    winValue = slots.calculateWin();
    game->addScore(winValue);
}


void ResultState::update(float deltaTime, SlotMachine::Machine &slots) {
}

void ResultState::handleInput(SlotMachine::Machine &slots) {
    if (Config::REGENERATE_SLOTS) slots.regenerateReels();
    slots.disableWinState();
    if (game->isPlayButtonClicked()) {
        game->changeState(std::make_unique<SpinState>(game,slots));
    }
    else game->changeState(std::make_unique<StartState>(game));
}
