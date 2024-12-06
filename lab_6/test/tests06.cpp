#include <gtest/gtest.h>
#include "../include/NPC.hpp"
#include "../include/NPCFactory.hpp"
#include "../include/Serializer.hpp"
#include "../include/BattleVisitor.hpp"
#include "../include/Logger.hpp"
#include <sstream>
#include <fstream>

// Test fixture
class NPCTest : public ::testing::Test {
protected:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
    
    void SetUp() override {
        observers.push_back(std::make_shared<ConsoleLogger>());
    }
};

// NPC Creation Tests
TEST_F(NPCTest, CreateKnight) {
    auto knight = NPCFactory::createNPC("Knight", "Arthur", 100, 100);
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(knight->getName(), "Arthur");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 100);
}

TEST_F(NPCTest, CreateDruid) {
    auto druid = NPCFactory::createNPC("Druid", "Merlin", 200, 200);
    EXPECT_EQ(druid->getType(), "Druid");
    EXPECT_EQ(druid->getName(), "Merlin");
    EXPECT_EQ(druid->getX(), 200);
    EXPECT_EQ(druid->getY(), 200);
}

TEST_F(NPCTest, CreateElf) {
    auto elf = NPCFactory::createNPC("Elf", "Legolas", 300, 300);
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getName(), "Legolas");
    EXPECT_EQ(elf->getX(), 300);
    EXPECT_EQ(elf->getY(), 300);
}

// Factory Invalid Input Test
TEST_F(NPCTest, InvalidNPCType) {
    EXPECT_THROW(NPCFactory::createNPC("Invalid", "Test", 0, 0), std::invalid_argument);
}

// Serialization Tests
TEST_F(NPCTest, SerializationDeserialization) {
    std::vector<std::shared_ptr<NPC>> original_npcs;
    original_npcs.push_back(NPCFactory::createNPC("Knight", "K1", 10, 10));
    original_npcs.push_back(NPCFactory::createNPC("Druid", "D1", 20, 20));

    std::string filename = "test_save.txt";
    Serializer::saveNPCs(original_npcs, filename);
    auto loaded_npcs = Serializer::loadNPCs(filename);

    EXPECT_EQ(original_npcs.size(), loaded_npcs.size());
    for (size_t i = 0; i < original_npcs.size(); ++i) {
        EXPECT_EQ(original_npcs[i]->getType(), loaded_npcs[i]->getType());
        EXPECT_EQ(original_npcs[i]->getName(), loaded_npcs[i]->getName());
        EXPECT_EQ(original_npcs[i]->getX(), loaded_npcs[i]->getX());
        EXPECT_EQ(original_npcs[i]->getY(), loaded_npcs[i]->getY());
    }
}

// Battle Tests
class MockObserver : public Observer {
public:
    std::vector<std::string> messages;
    void onEvent(const std::string& message) override {
        messages.push_back(message);
    }
};

TEST_F(NPCTest, BattleTest) {
    // Create NPCs
    auto knight = NPCFactory::createNPC("Knight", "Arthur", 0, 0);
    auto elf = NPCFactory::createNPC("Elf", "Legolas", 1, 1);
    npcs = {knight, elf};
    
    // Create mock observer
    auto mockObserver = std::make_shared<MockObserver>();
    observers.push_back(mockObserver);
    
    // Create battle visitor
    float fightDistance = 10.0f;
    auto battleVisitor = BattleVisitor(npcs, observers, fightDistance);
    
    // Simulate battle
    knight->accept(battleVisitor, elf);
    
    // Verify battle occurred (check if any messages were logged)
    EXPECT_GT(mockObserver->messages.size(), 0);
}

// Logger Tests
TEST_F(NPCTest, FileLoggerTest) {
    std::string logFile = "test_log.txt";
    auto fileLogger = std::make_shared<FileLogger>(logFile);
    
    std::string testMessage = "Test battle message";
    fileLogger->onEvent(testMessage);
    
    // Read file content
    std::ifstream file(logFile);
    std::string line;
    std::getline(file, line);
    
    EXPECT_EQ(line, testMessage);
    
    // Cleanup
    file.close();
    std::remove(logFile.c_str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}