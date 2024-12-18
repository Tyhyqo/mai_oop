#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <memory>
#include <mutex>
#include "Observer.hpp"

class NPCVisitor;

class NPC : public std::enable_shared_from_this<NPC> {
public:
    NPC(const std::string& name, float x, float y);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    std::string getName() const;
    float getX() const;
    float getY() const;
    void setPosition(float x, float y);

    bool isAlive() const;
    void kill();

    virtual void accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) = 0;

protected:
    std::string name;
    float x;
    float y;
    bool alive;
    mutable std::mutex mtx;
};

class Knight : public NPC {
public:
    Knight(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) override;
};

class Druid : public NPC {
public:
    Druid(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor, std::shared_ptr<NPC> other) override;
};

#endif // NPC_HPP