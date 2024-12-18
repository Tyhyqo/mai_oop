#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <memory>
#include "NPC.hpp"

// Передние объявления классов NPC
class Knight;
class Druid;
class Elf;

class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;

    virtual void visitKnight(Knight& knight, std::shared_ptr<NPC> other) = 0;
    virtual void visitDruid(Druid& druid, std::shared_ptr<NPC> other) = 0;
    virtual void visitElf(Elf& elf, std::shared_ptr<NPC> other) = 0;
};

#endif // VISITOR_HPP