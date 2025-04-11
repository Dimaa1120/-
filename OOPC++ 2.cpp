#include <iostream>
#include <string>
#include <vector>

class Weapon {
private:
    std::string name;
    int damage;
    float weight;

public:
    // Конструктор
    Weapon(const std::string& n, int d, float w)
        : name(n), damage(d), weight(w) {
        std::cout << "Weapon " << name << " created!\n";
    }

    // Деструктор
    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed!\n";
    }

    // Метод для вывода информации
    void displayInfo() const {
        std::cout << "Weapon: " << name
            << ", Damage: " << damage
            << ", Weight: " << weight << " kg\n";
    }
};

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    Weapon* weapon;  // Персонаж может держать оружие

public:
    // Конструктор
    Character(const std::string& n, int h, int a, int d, Weapon* w = nullptr)
        : name(n), health(h), attack(a), defense(d), weapon(w) {
        std::cout << "Character " << name << " created!\n";
    }

    // Деструктор
    ~Character() {
        std::cout << "Character " << name << " destroyed!\n";
        if (weapon) {
            delete weapon;  // Удаляем оружие при уничтожении персонажа
        }
    }

    void displayInfo() const {
        std::cout << "Character: " << name
            << ", HP: " << health
            << ", Attack: " << attack
            << ", Defense: " << defense << "\n";
        if (weapon) {
            weapon->displayInfo();
        }
    }

    // Метод для смены оружия
    void equipWeapon(Weapon* newWeapon) {
        if (weapon) {
            delete weapon;
        }
        weapon = newWeapon;
    }
};

class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    // Конструктор
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Monster " << name << " created!\n";
    }

    // Деструктор
    ~Monster() {
        std::cout << "Monster " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Monster: " << name
            << ", HP: " << health
            << ", Attack: " << attack
            << ", Defense: " << defense << "\n";
    }
};

int main() {
    // Создаем оружие
    Weapon* sword = new Weapon("Steel Sword", 15, 2.5);
    Weapon* axe = new Weapon("Battle Axe", 20, 5.0);
    Weapon* bow = new Weapon("Long Bow", 12, 1.2);

    // Создаем персонажей и монстров
    Character hero("Hero", 100, 20, 10, sword);
    Monster goblin("Goblin", 50, 15, 5);
    Monster dragon("Dragon", 200, 30, 20);

    // Выводим информацию
    std::cout << "\n=== Character Info ===\n";
    hero.displayInfo();

    std::cout << "\n=== Monster Info ===\n";
    goblin.displayInfo();
    dragon.displayInfo();

    // Меняем оружие героя
    std::cout << "\n=== Changing Weapon ===\n";
    hero.equipWeapon(axe);
    hero.displayInfo();

    // Оружие автоматически уничтожится при уничтожении персонажа
    std::cout << "\n=== End of Scope ===\n";

    return 0;
}

