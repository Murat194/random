#include <iostream>
#include <string>
using namespace std;

class Character {
private:
    string name;
    int level;
public:
    Character(string a, int b) {
        name = a;
        level = b;
    };

    ~Character() {
        cout << "Уничтожено" << endl;
    };

    string getName() {
        return name;
    };

    int getLevel() {
        return level;
    };
    
    void setLevel(int a){
        level = a;
    };
    
};

class Player : public Character {
private:
    int experience;

public:
    Player(string a, int b) : Character(a, b) {
        experiencePoints = 0;
    };

    void addExp(int points) {
        experience += points;
        while (experience >= 100) {
            experience -= 100;
            setLevel(getLevel() + 1);
        };
    };

    ~Player() {
        cout << "Уничтожено" << endl;
    };

    int getExp() {
        return experience;
    };
};

int main() {
    Player player("Владос", 1);
    cout << "Имя: " << player.getName() << endl;
    cout << "Уровень: " << player.getLevel() << endl;
    cout << "Опыт: " << player.getExp() << endl;

    player.addExp(150);
    cout << "Уровень после опыта: " << player.getLevel() << endl;
    cout << "Очки опыта после: " << player.getExp() << endl;

}
