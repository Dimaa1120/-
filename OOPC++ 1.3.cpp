#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }

    // Виртуальный метод для атаки
    virtual void attack(Entity& target) {
        int damage = attack - target.defense;
        if (damage > 0) {
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    // Виртуальный метод для лечения
    virtual void heal(int amount) {
        health += amount;
        std::cout << name << " heals for " << amount << " HP. Current HP: " << health << std::endl;
    }

    // Виртуальный метод для вывода информации
    virtual void displayInfo() const {
        std::cout << "Entity: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    // Виртуальный деструктор
    virtual ~Entity() {
        std::cout << name << " has been destroyed.\n";
    }

    bool isAlive() const { return health > 0; }

    // Добавляем метод getName()
    const std::string& getName() const { return name; }
};

class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    void attack(Entity& target) override {
        int damage = attack - target.defense;
        if (damage > 0) {
            // 20% шанс на критический удар
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    void heal(int amount) override {
        int maxHealth = 100; // Максимальное здоровье для персонажа
        if (health + amount > maxHealth) {
            amount = maxHealth - health;
        }
        Entity::heal(amount);
    }

    void displayInfo() const override {
        std::cout << "Character: " << name << ", HP: " << health
            << "/100, Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    void attack(Entity& target) override {
        int damage = attack - target.defense;
        if (damage > 0) {
            // 30% шанс на ядовитую атаку
            if (rand() % 100 < 30) {
                damage += 5;
                std::cout << "Poisonous attack! ";
            }
            target.health -= damage;
            std::cout << name << " attacks " << target.name << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks " << target.name << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Monster: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Boss : public Monster {
private:
    bool fireAttackUsed = false;

public:
    Boss(const std::string& n, int h, int a, int d)
        : Monster(n, h, a, d) {
    }

    void attack(Entity& target) override {
        // 25% шанс использовать огненную атаку (если еще не использована)
        if (!fireAttackUsed && rand() % 100 < 25) {
            int fireDamage = 15;
            target.health -= fireDamage;
            fireAttackUsed = true;
            std::cout << name << " uses FIRE BREATH on " << target.name
                << " for " << fireDamage << " fire damage!\n";
        }
        else {
            Monster::attack(target); // Обычная атака монстра
        }
    }

    void displayInfo() const override {
        std::cout << "BOSS: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Создание объектов
    Character hero("Arthur", 100, 25, 15);
    Monster goblin("Goblin", 50, 15, 5);
    Monster orc("Orc Warrior", 80, 20, 10);
    Boss dragon("Dragon King", 200, 30, 20);

    // Массив указателей на базовый класс
    std::vector<Entity*> entities = { &hero, &goblin, &orc, &dragon };

    // Демонстрация полиморфизма
    std::cout << "=== Initial Status ===\n";
    for (auto entity : entities) {
        entity->displayInfo();
    }

    // Бой
    std::cout << "\n=== Battle Begins ===\n";

    // Персонаж атакует всех монстров
    for (size_t i = 1; i < entities.size(); ++i) {
        hero.attack(*entities[i]);
    }

    // Монстры атакуют персонажа
    for (size_t i = 1; i < entities.size(); ++i) {
        if (entities[i]->isAlive()) {
            entities[i]->attack(hero);
        }
    }

    // Персонаж лечится
    std::cout << "\n=== Healing ===\n";
    hero.heal(30);

    // Финальный статус
    std::cout << "\n=== Final Status ===\n";
    for (auto entity : entities) {
        if (entity->isAlive()) {
            entity->displayInfo();
        }
        else {
            std::cout << entity->getName() << " is dead.\n";
        }
    }

    return 0;
}