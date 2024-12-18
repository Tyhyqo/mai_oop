#ifndef NPC_FACTORY_HPP
#define NPC_FACTORY_HPP

#include <memory>
#include <vector>
#include "NPC.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, float x, float y);
};

#endif // NPC_FACTORY_HPP