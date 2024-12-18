#include "Serializer.hpp"
#include "NPCFactory.hpp"
#include <fstream>
#include <stdexcept>

void Serializer::saveNPCs(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file for saving");
    }
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
        }
    }
}

std::vector<std::shared_ptr<NPC>> Serializer::loadNPCs(const std::string& filename) {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file for loading");
    }

    std::string type, name;
    float x, y;
    while (file >> type >> name >> x >> y) {
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    }

    return npcs;
}