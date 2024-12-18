#include "NPCFactory.hpp"
#include "NPC.hpp"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, float x, float y) {
    if (type == "Knight") {
        return std::make_shared<Knight>(name, x, y);
    } else if (type == "Druid") {
        return std::make_shared<Druid>(name, x, y);
    } else if (type == "Elf") {
        return std::make_shared<Elf>(name, x, y);
    } else {
        throw std::invalid_argument("Неизвестный тип NPC: " + type);
    }
}