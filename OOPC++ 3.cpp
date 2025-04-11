#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;
    float weight;

public:
    Weapon(const std::string& n, int d, float w)
        : name(n), damage(d), weight(w) {
    }

    // Перегрузка оператора + (создает новое оружие с суммарным уроном)
    Weapon operator+(const Weapon& other) const {
        std::string newName = name + "+" + other.name;
        int newDamage = damage + other.damage;
        float newWeight = weight + other.weight;
        return Weapon(newName, newDamage, newWeight);
    }

    // Перегрузка оператора > (сравнение по урону)
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    // Перегрузка оператора << для вывода
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon: " << weapon.name
            << ", Damage: " << weapon.damage
            << ", Weight: " << weapon.weight << "kg";
        return os;
    }
};

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }

    // Перегрузка оператора ==
    bool operator==(const Character& other) const {
        return name == other.name && health == other.health;
    }

    // Перегрузка оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << "Character: " << character.name
            << ", HP: " << character.health
            << ", Attack: " << character.attack
            << ", Defense: " << character.defense;
        return os;
    }
};

int main() {
    // Демонстрация для класса Character
    Character hero1("Hero", 100, 20, 10);
    Character hero2("Hero", 100, 20, 10);
    Character hero3("Warrior", 150, 25, 15);

    std::cout << "=== Character Comparison ===" << std::endl;
    if (hero1 == hero2) {
        std::cout << "Hero1 and Hero2 are the same!\n";
    }
    if (!(hero1 == hero3)) {
        std::cout << "Hero1 and Hero3 are different!\n";
    }
    std::cout << hero1 << "\n\n";

    // Демонстрация для класса Weapon
    Weapon sword("Steel Sword", 15, 2.5);
    Weapon bow("Long Bow", 12, 1.2);
    Weapon axe("Battle Axe", 20, 5.0);

    std::cout << "=== Weapon Operations ===" << std::endl;
    // Создаем комбинированное оружие
    Weapon combined = sword + bow;
    std::cout << "Combined weapon: " << combined << std::endl;

    // Сравниваем оружие по урону
    std::cout << "Is axe stronger than sword? "
        << (axe > sword ? "Yes" : "No") << std::endl;
    std::cout << "Is bow stronger than sword? "
        << (bow > sword ? "Yes" : "No") << std::endl;

    return 0;
}
