//
// Created by val on 3/19/25.
//

#include "slot_machine.hpp"

#include "config_values.hpp"

void SlotMachine::Machine::initWinningLines() {
    size_t middlePos = Config::DISPLAYED_SYMBOL_AMOUNT / 2;
    winningLines.emplace_back(middlePos);
    winningLines.emplace_back(std::vector<size_t>({middlePos, middlePos+1, middlePos-1}));
}

SlotMachine::Machine::Machine(const sf::FloatRect &bounds, size_t reelCount) : reels(reelCount), bounds(bounds) {
    initWinningLines();
}

int SlotMachine::Machine::calculateWin() {
    //The current pos is the top-most rendered
    //Win is calculated based on amount of symbols encountered, but only if symbol is encountered at least reels.size()/2
    //Only combination of at least 2 same symbols is scored
    int res = 0;
    for (auto& line: winningLines) { res+=line.calculateWin(reels); }
    return res;
}

void SlotMachine::Machine::drawMachineBorder(sf::RenderTarget &target) {
    sf::RectangleShape machineBorder(bounds.size);
    machineBorder.setPosition(bounds.position);
    machineBorder.setFillColor(sf::Color::Transparent);
    machineBorder.setOutlineColor(sf::Color::Black);
    machineBorder.setOutlineThickness(1.f);
    target.draw(machineBorder);
}

void SlotMachine::Machine::drawWinningBorder(sf::RenderTarget &target) {
    sf::RectangleShape winningBorder({bounds.size.x, Config::SYMBOL_SIZE});
    winningBorder.setPosition({bounds.position.x, bounds.position.y+winningPos*Config::SYMBOL_SIZE});
    winningBorder.setFillColor(sf::Color::Transparent);
    winningBorder.setOutlineColor(sf::Color::Black);
    winningBorder.setOutlineThickness(3.f);
    target.draw(winningBorder);
}

void SlotMachine::Machine::render(sf::RenderTarget &target) {
    const sf::View originalView = target.getView();
    sf::View machineView(bounds);
    machineView.setViewport({
            {bounds.position.x/target.getSize().x, bounds.position.y/target.getSize().y},
        {machineView.getSize().x / target.getSize().x, machineView.getSize().y / target.getSize().y}
    });
    target.setView(machineView);
    slotView.render(target, reels);
    for (auto& line: winningLines) {line.draw(target, reels);}
    target.setView(originalView);
    drawMachineBorder(target);
    drawWinningBorder(target);
}

void SlotMachine::Machine::update(float deltaTime) {
    for (auto &reel: reels) {
        reel.update(deltaTime);
    }
}
