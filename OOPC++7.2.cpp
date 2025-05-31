#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <random>

class Character {
public:
    std::string name;
    int health;
    int attack;
    int defense;

    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }

    void displayInfo() {
        std::cout << name << " - Health: " << health << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    bool isAlive() const {
        return health > 0;
    }
};

class Monster : public Character {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Character(n, h, a, d) {
    }
};

std::vector<Monster> monsters;
std::mutex monstersMutex;
std::mutex fightMutex;

void generateMonsters() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> healthDist(30, 70);
    std::uniform_int_distribution<> attackDist(5, 20);
    std::uniform_int_distribution<> defenseDist(2, 10);

    const std::vector<std::string> monsterNames = { "Goblin", "Orc", "Troll", "Skeleton", "Zombie" };

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::lock_guard<std::mutex> lock(monstersMutex);
        std::uniform_int_distribution<> nameDist(0, monsterNames.size() - 1);
        std::string name = monsterNames[nameDist(gen)];
        monsters.emplace_back(name, healthDist(gen), attackDist(gen), defenseDist(gen));
        std::cout << "New monster generated: " << name << std::endl;
    }
}

void fight(Character& hero) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> monsterLock(monstersMutex);
        std::lock_guard<std::mutex> fightLock(fightMutex);

        if (!hero.isAlive()) {
            std::cout << "Hero is dead! Game over." << std::endl;
            return;
        }

        if (monsters.empty()) {
            continue;
        }

        // Бой с первым монстром в списке
        Monster& monster = monsters.front();

        // Герой атакует монстра
        int damage = std::max(1, hero.attack - monster.defense);
        monster.health -= damage;
        std::cout << hero.name << " hits " << monster.name << " for " << damage << " damage!" << std::endl;

        // Проверяем, жив ли монстр
        if (!monster.isAlive()) {
            std::cout << monster.name << " died!" << std::endl;
            monsters.erase(monsters.begin());
            continue;
        }

        // Монстр атакует героя
        damage = std::max(1, monster.attack - hero.defense);
        hero.health -= damage;
        std::cout << monster.name << " hits " << hero.name << " for " << damage << " damage!" << std::endl;
    }
}

int main() {
    std::thread monsterGenerator(generateMonsters);
    monsterGenerator.detach();

    Character hero("Hero", 100, 20, 10);
    std::thread fightThread(fight, std::ref(hero));

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(monstersMutex);
        std::lock_guard<std::mutex> fightLock(fightMutex);

        hero.displayInfo();
        std::cout << "Monsters count: " << monsters.size() << std::endl;
        for (auto& monster : monsters) {
            monster.displayInfo();
        }

        if (!hero.isAlive()) {
            break;
        }
    }

    fightThread.join();
    return 0;
}