#ifndef BATTLEVISITOR_HPP
#define BATTLEVISITOR_HPP

#include "Visitor.hpp"
#include "Observer.hpp"
#include <vector>
#include <memory>

class BattleVisitor : public NPCVisitor {
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs, std::vector<std::shared_ptr<Observer>>& observers, float fightDistance);
    void visitKnight(Knight& knight, std::shared_ptr<NPC> other) override;
    void visitDruid(Druid& druid, std::shared_ptr<NPC> other) override;
    void visitElf(Elf& elf, std::shared_ptr<NPC> other) override;

private:
    std::vector<std::shared_ptr<NPC>>& npcs;
    std::vector<std::shared_ptr<Observer>>& observers;
    float fightDistance;
    void notifyObservers(const std::string& message);
    bool isInRange(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2);
};

#endif // BATTLEVISITOR_HPP