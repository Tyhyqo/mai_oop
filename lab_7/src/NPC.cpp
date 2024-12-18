#include "NPC.hpp"
#include "BattleVisitor.hpp"

NPC::NPC(const std::string& name, float x, float y)
    : name(name), x(x), y(y), alive(true) {}

std::string NPC::getName() const {
    std::lock_guard<std::mutex> lock(mtx);
    return name;
}

float NPC::getX() const {
    std::lock_guard<std::mutex> lock(mtx);
    return x;
}

float NPC::getY() const {
    std::lock_guard<std::mutex> lock(mtx);
    return y;
}

void NPC::setPosition(float new_x, float new_y) {
    std::lock_guard<std::mutex> lock(mtx);
    x = new_x;
    y = new_y;
}

bool NPC::isAlive() const {
    std::lock_guard<std::mutex> lock(mtx);
    return alive;
}

void NPC::kill() {
    std::lock_guard<std::mutex> lock(mtx);
    alive = false;
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