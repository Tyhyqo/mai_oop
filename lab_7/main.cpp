#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>
#include "NPC.hpp"
#include "NPCFactory.hpp"
#include "Serializer.hpp"
#include "BattleVisitor.hpp"
#include "FileLogger.hpp"
#include "ConsoleLogger.hpp"

// Константы карты
const float MAP_WIDTH = 100.0f;
const float MAP_HEIGHT = 100.0f;

// Мьютексы для синхронизации
std::mutex npc_mtx;
std::mutex cout_mtx;

// Функция для генерации случайных чисел
float getRandomFloat(float min, float max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

// Функция для генерации случайных NPC
std::vector<std::shared_ptr<NPC>> generateRandomNPCs(int count) {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::string> types = {"Knight", "Druid", "Elf"};
    for (int i = 0; i < count; ++i) {
        std::string type = types[getRandomFloat(0, types.size())];
        std::string name = type + "_" + std::to_string(i+1);
        float x = getRandomFloat(0, MAP_WIDTH);
        float y = getRandomFloat(0, MAP_HEIGHT);
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    }
    return npcs;
}

int main() {
    // Создание NPC
    std::vector<std::shared_ptr<NPC>> npcs = generateRandomNPCs(50);

    // Создание наблюдателей
    std::vector<std::shared_ptr<Observer>> observers;
    observers.push_back(std::make_shared<FileLogger>("log.txt"));
    observers.push_back(std::make_shared<ConsoleLogger>());

    // Создание BattleVisitor
    float fightDistance = 10.0f;
    BattleVisitor battleVisitor(npcs, observers, fightDistance);

    // Флаг завершения игры
    bool gameOver = false;

    // Поток передвижения NPC
    std::thread movementThread([&]() {
        while (!gameOver) {
            {
                std::lock_guard<std::mutex> lock(npc_mtx);
                for (auto& npc : npcs) {
                    if (!npc->isAlive()) continue;

                    // Получение типа NPC для определения шага
                    std::string type = npc->getType();
                    float moveDistance = 0.0f;
                    if (type == "Knight") moveDistance = 30.0f;
                    else if (type == "Druid") moveDistance = 10.0f;
                    else if (type == "Elf") moveDistance = 10.0f;

                    // Генерация случайного направления
                    float angle = getRandomFloat(0, 2 * 3.14159265f);
                    float dx = moveDistance * std::cos(angle);
                    float dy = moveDistance * std::sin(angle);

                    float new_x = npc->getX() + dx;
                    float new_y = npc->getY() + dy;

                    // Проверка границ карты
                    if (new_x < 0) new_x = 0;
                    if (new_x > MAP_WIDTH) new_x = MAP_WIDTH;
                    if (new_y < 0) new_y = 0;
                    if (new_y > MAP_HEIGHT) new_y = MAP_HEIGHT;

                    npc->setPosition(new_x, new_y);
                }

                // Проверка на расстояние для боя
                for (size_t i = 0; i < npcs.size(); ++i) {
                    for (size_t j = i + 1; j < npcs.size(); ++j) {
                        auto npc1 = npcs[i];
                        auto npc2 = npcs[j];
                        if (!npc1->isAlive() || !npc2->isAlive()) continue;

                        float dx = npc1->getX() - npc2->getX();
                        float dy = npc1->getY() - npc2->getY();
                        float distance = std::sqrt(dx * dx + dy * dy);

                        // Таблица убиваемости
                        bool canBattle = false;
                        if (npc1->getType() == "Knight" && npc2->getType() == "Elf" && distance <= 10.0f)
                            canBattle = true;
                        if (npc1->getType() == "Elf" && (npc2->getType() == "Druid" || npc2->getType() == "Knight") && distance <= 50.0f)
                            canBattle = true;
                        if (npc1->getType() == "Druid" && npc2->getType() == "Druid" && distance <= 10.0f)
                            canBattle = true;

                        if (canBattle) {
                            // Инициировать бой
                            npc1->accept(battleVisitor, npc2);
                        }
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Поток боя
    std::thread battleThread([&]() {
        while (!gameOver) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Основной поток печатает карту каждую секунду
    std::thread printThread([&]() {
        while (!gameOver) {
            {
                std::lock_guard<std::mutex> lock(cout_mtx);
                std::cout << "----- Карта NPC -----" << std::endl;
                std::lock_guard<std::mutex> lock_npc(npc_mtx);
                for (const auto& npc : npcs) {
                    if (npc->isAlive()) {
                        std::cout << npc->getType() << " " << npc->getName()
                                  << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
                    }
                }
                std::cout << "----------------------" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    // Таймер игры на 30 секунд
    std::this_thread::sleep_for(std::chrono::seconds(30));
    gameOver = true;

    // Ожидание завершения потоков
    if (movementThread.joinable()) movementThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printThread.joinable()) printThread.join();

    // Вывод списка выживших
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "\nСписок выживших NPC:" << std::endl;
        std::lock_guard<std::mutex> lock_npc(npc_mtx);
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getName()
                          << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
            }
        }
    }

    return 0;
}