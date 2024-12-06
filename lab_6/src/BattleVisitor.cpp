#include "BattleVisitor.hpp"
#include "NPC.hpp"
#include <cmath>
#include <algorithm>

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs, std::vector<std::shared_ptr<Observer>>& observers, float fightDistance)
    : npcs(npcs), observers(observers), fightDistance(fightDistance) {}

void BattleVisitor::notifyObservers(const std::string& message) {
    for (auto& observer : observers) {
        observer->onEvent(message);
    }
}

bool BattleVisitor::isInRange(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2) {
    float dx = npc1->getX() - npc2->getX();
    float dy = npc1->getY() - npc2->getY();
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= fightDistance;
}

void BattleVisitor::visitKnight(Knight& knight, std::shared_ptr<NPC> other) {
    if (!isInRange(std::make_shared<Knight>(knight), other)) return;

    if (other->getType() == "Elf") {
        // Knight kills Elf
        std::string message = knight.getType() + " " + knight.getName() + " убил " + other->getType() + "а " + other->getName();
        notifyObservers(message);

        // Удаляем Эльфа
        npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
            [&other](std::shared_ptr<NPC> npc) { return npc == other; }), npcs.end());
    }
}

void BattleVisitor::visitDruid(Druid& druid, std::shared_ptr<NPC> other) {
    if (!isInRange(std::make_shared<Druid>(druid), other)) return;

    if (other->getType() == "Druid") {
        // Druid kills Druid
        std::string message = druid.getType() + " " + druid.getName() + " убил " + other->getType() + "а " + other->getName();
        notifyObservers(message);

        // Удаляем другого Друида
        npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
            [&other](std::shared_ptr<NPC> npc) { return npc == other; }), npcs.end());
    }
}

void BattleVisitor::visitElf(Elf& elf, std::shared_ptr<NPC> other) {
    if (!isInRange(std::make_shared<Elf>(elf), other)) return;

    if (other->getType() == "Druid" || other->getType() == "Knight") {
        // Elf kills Druid and Knight
        std::string message = elf.getType() + " " + elf.getName() + " убил " + other->getType() + "а " + other->getName();
        notifyObservers(message);

        // Удаляем противника
        npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
            [&other](std::shared_ptr<NPC> npc) { return npc == other; }), npcs.end());
    }
}