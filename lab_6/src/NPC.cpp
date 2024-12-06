#include "NPC.hpp"
#include "Visitor.hpp"

NPC::NPC(const std::string& name, float x, float y)
    : name(name), x(x), y(y) {}

std::string NPC::getName() const {
    return name;
}

float NPC::getX() const {
    return x;
}

float NPC::getY() const {
    return y;
}

void NPC::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

Knight::Knight(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Knight::getType() const {
    return "Knight";
}

void Knight::accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visitKnight(*this, other);
}

Druid::Druid(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Druid::getType() const {
    return "Druid";
}

void Druid::accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visitDruid(*this, other);
}

Elf::Elf(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Elf::getType() const {
    return "Elf";
}

void Elf::accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visitElf(*this, other);
}