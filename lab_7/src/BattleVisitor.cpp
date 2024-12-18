#include "BattleVisitor.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <mutex>

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs,
                             std::vector<std::shared_ptr<Observer>>& observers,
                             float fightDistance)
    : npcs_(npcs), observers_(observers), fightDistance_(fightDistance) {}

BattleVisitor::~BattleVisitor() {}

// Метод уведомления наблюдателей
void BattleVisitor::notifyObservers(const std::string& message) {
    for (const auto& observer : observers_) {
        observer->onEvent(message);
    }
}

// Метод проверки расстояния между двумя NPC
bool BattleVisitor::isInRange(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2) {
    float dx = npc1->getX() - npc2->getX();
    float dy = npc1->getY() - npc2->getY();
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= fightDistance_;
}

// Реализация боя между Рыцарём и Эльфом
void BattleVisitor::visitKnight(Knight& knight, std::shared_ptr<NPC> other) {
    if (!isInRange(knight.shared_from_this(), other)) return;

    if (other->getType() == "Elf") {
        // Инициация боя
        notifyObservers(knight.getType() + " " + knight.getName() + " вступил в бой с " + other->getType() + " " + other->getName());

        // Логика боя
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);

        int attack = dist(gen);
        int defense = dist(gen);

        if (attack > defense) {
            other->kill();
            notifyObservers(other->getType() + " " + other->getName() + " был убит!");
        } else {
            notifyObservers(other->getType() + " " + other->getName() + " успешно защищался!");
        }
    }
}

// Реализация боя между Друидом и Друидом
void BattleVisitor::visitDruid(Druid& druid, std::shared_ptr<NPC> other) {
    if (!isInRange(druid.shared_from_this(), other)) return;

    if (other->getType() == "Druid") {
        // Инициация боя
        notifyObservers(druid.getType() + " " + druid.getName() + " вступил в бой с " + other->getType() + " " + other->getName());

        // Логика боя
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);

        int attack = dist(gen);
        int defense = dist(gen);

        if (attack > defense) {
            other->kill();
            notifyObservers(other->getType() + " " + other->getName() + " был убит!");
        } else {
            notifyObservers(other->getType() + " " + other->getName() + " успешно защищался!");
        }
    }
}

// Реализация боя между Эльфом и Друидом или Рыцарём
void BattleVisitor::visitElf(Elf& elf, std::shared_ptr<NPC> other) {
    if (!isInRange(elf.shared_from_this(), other)) return;

    if (other->getType() == "Druid" || other->getType() == "Knight") {
        // Инициация боя
        notifyObservers(elf.getType() + " " + elf.getName() + " вступил в бой с " + other->getType() + " " + other->getName());

        // Логика боя
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);

        int attack = dist(gen);
        int defense = dist(gen);

        if (attack > defense) {
            other->kill();
            notifyObservers(other->getType() + " " + other->getName() + " был убит!");
        } else {
            notifyObservers(other->getType() + " " + other->getName() + " успешно защищался!");
        }
    }
}