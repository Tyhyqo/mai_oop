#ifndef NPCFACTORY_HPP
#define NPCFACTORY_HPP

#include "NPC.hpp"
#include <memory>
#include <string>

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, float x, float y);
};

#endif // NPCFACTORY_HPP