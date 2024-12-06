#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "NPC.hpp"
#include "NPCFactory.hpp"
#include "Serializer.hpp"
#include "BattleVisitor.hpp"
#include "Logger.hpp"

void addNPC(std::vector<std::shared_ptr<NPC>>& npcs) {
    std::string type, name;
    float x, y;

    std::cout << "Введите тип NPC (Knight, Druid, Elf): ";
    std::cin >> type;
    std::cout << "Введите уникальное имя: ";
    std::cin >> name;
    std::cout << "Введите координаты x и y (от 0 до 500): ";
    std::cin >> x >> y;

    if (x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Координаты вне допустимого диапазона!" << std::endl;
        return;
    }

    try {
        auto npc = NPCFactory::createNPC(type, name, x, y);
        npcs.push_back(npc);
        std::cout << "NPC добавлен успешно!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void printNPCs(const std::vector<std::shared_ptr<NPC>>& npcs) {
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
}

void battleMode(std::vector<std::shared_ptr<NPC>>& npcs) {
    float distance;
    std::cout << "Введите дальность боя: ";
    std::cin >> distance;

    std::vector<std::shared_ptr<Observer>> observers;
    observers.push_back(std::make_shared<FileLogger>("log.txt"));
    observers.push_back(std::make_shared<ConsoleLogger>());

    auto battleVisitor = std::make_shared<BattleVisitor>(npcs, observers, distance);

    auto npcsCopy = npcs;

    for (auto& npc : npcsCopy) {
        for (auto& other : npcsCopy) {
            if (npc != other) {
                npc->accept(*battleVisitor, other);
            }
        }
    }

    std::cout << "Бой завершен!" << std::endl;
}

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить NPC\n";
        std::cout << "2. Сохранить NPC в файл\n";
        std::cout << "3. Загрузить NPC из файла\n";
        std::cout << "4. Показать всех NPC\n";
        std::cout << "5. Запустить боевой режим\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addNPC(npcs);
                break;
            case 2:
                try {
                    Serializer::saveNPCs(npcs, "npcs.txt");
                    std::cout << "NPC сохранены в файл npcs.txt\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            case 3:
                try {
                    npcs = Serializer::loadNPCs("npcs.txt");
                    std::cout << "NPC загружены из файла npcs.txt\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            case 4:
                printNPCs(npcs);
                break;
            case 5:
                battleMode(npcs);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}