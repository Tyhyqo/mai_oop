#ifndef BATTLE_VISITOR_HPP
#define BATTLE_VISITOR_HPP

#include <memory>
#include <vector>
#include "Visitor.hpp"
#include "Observer.hpp"
class NPC;
class Knight;
class Druid;
class Elf;

class BattleVisitor : public NPCVisitor {
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs,
                 std::vector<std::shared_ptr<Observer>>& observers,
                 float fightDistance);
    virtual ~BattleVisitor();

    void visitKnight(Knight& knight, std::shared_ptr<NPC> other) override;
    void visitDruid(Druid& druid, std::shared_ptr<NPC> other) override;
    void visitElf(Elf& elf, std::shared_ptr<NPC> other) override;

private:
    std::vector<std::shared_ptr<NPC>>& npcs_;
    std::vector<std::shared_ptr<Observer>>& observers_;
    float fightDistance_;

    void notifyObservers(const std::string& message);
    bool isInRange(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2);
};

#endif // BATTLE_VISITOR_HPP