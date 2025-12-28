#include <iostream>
#include <string>

class Player {
private:
    std::string name;
    int level;
    int experiencePoints;
    static const int lvlup = 100;

public:
    Player(const std::string& playerName, int initialLevel = 1)
        : name(playerName), level(initialLevel), experiencePoints(0) {
        std::cout << "Игрок " << name << " создан (уровень " << level << ")\n";
    }

    void addExperience(int points) {
        if (points <= 0) return;
        experiencePoints += points;
        std::cout << name << " получил " << points << " опыта\n";
        while (experiencePoints >= lvlup) {
            level++;
            experiencePoints -= lvlup;
            std::cout << name << " достиг уровня " << level << "!\n";
        }
    }

    int getLevel() const { return level; }
    int getExperience() const { return experiencePoints; }
    std::string getName() const { return name; }

    void showInfo() const {
        std::cout << name << ": уровень " << level << ", опыт " << experiencePoints << "/" << lvlup << "\n";
    }

    ~Player() {
        std::cout << "Игрок " << name << " удален\n";
    }
};
