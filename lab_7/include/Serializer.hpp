#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <vector>
#include <memory>
#include "NPC.hpp"

class Serializer {
public:
    static void saveNPCs(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename);
    static std::vector<std::shared_ptr<NPC>> loadNPCs(const std::string& filename);
};

#endif // SERIALIZER_HPP