//
// Created by val on 3/18/25.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "config_values.hpp"
#include "slot_machine.hpp"

/// Interface for states
class IState {
public:
    virtual ~IState() = default;

    virtual void update(float deltaTime, SlotMachine::Machine &slots) = 0;

    virtual void handleInput(SlotMachine::Machine &slots) = 0;
};

class StateMachine {
private:
    std::unique_ptr<IState> currentState;

public:
    StateMachine() : currentState(nullptr) {
    }

    void changeState(std::unique_ptr<IState> newState) {
        currentState = std::move(newState);
    }

    void update(float deltaTime, SlotMachine::Machine &slots) { currentState->update(deltaTime, slots); }
    void handleInput(SlotMachine::Machine &slots) { currentState->handleInput(slots); }
};

class Game; //forward decl
class StartState : public IState {
private:
    Game *game;

    void initializeStartState();

public:
    StartState() = delete;

    explicit StartState(Game *game) : game(game) {
        initializeStartState();
    }

    void update(float deltaTime, SlotMachine::Machine &slots) override;

    void handleInput(SlotMachine::Machine &slots) override;
};

class SpinState : public IState {
private:
    Game *game;
    sf::Clock spinTimer;
    float spinDuration = Config::DEFAULT_SPIN_DURATION;
    bool isSpinning = true;

public:
    SpinState() = delete;

    explicit SpinState(Game *game, SlotMachine::Machine &slots) : game(game) {
        spinTimer.restart();
        slots.spin(spinDuration);
    }

    explicit SpinState(Game *game, SlotMachine::Machine &slots, float duration) : game(game), spinDuration(duration) {
        spinTimer.restart();
        slots.spin(spinDuration);
    }

    void update(float deltaTime, SlotMachine::Machine &slots) override;

    void handleInput(SlotMachine::Machine &slots) override;
};

class ResultState : public IState {
    Game *game;
    int winValue = 0;

public:
    ResultState() = delete;

    explicit ResultState(Game *game, SlotMachine::Machine &slots);

    void update(float deltaTime, SlotMachine::Machine &slots) override;

    void handleInput(SlotMachine::Machine &slots) override;
};
