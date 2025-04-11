
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

// Базовый класс Entity
class Entity {
public:
    virtual int getHealth() const = 0;
    virtual void displayInfo() const = 0;
    virtual ~Entity() {}
};

// Класс Player
class Player : public Entity {
    std::string name;
    int health;
    int experience;
public:
    Player(const std::string& n, int h, int exp) : name(n), health(h), experience(exp) {}
    int getHealth() const override { return health; }
    void displayInfo() const override {
        std::cout << "Player: " << name << ", HP: " << health << ", EXP: " << experience << std::endl;
    }
};

// Шаблонный класс GameManager с обработкой исключений
template <typename T>
class GameManager {
private:
    std::vector<std::unique_ptr<T>> entities;

public:
    void addEntity(T* entity) {
        if (entity->getHealth() <= 0) {
            throw std::invalid_argument("Entity has invalid health (must be positive)");
        }
        entities.emplace_back(entity);
    }

    void displayAll() const {
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }
};

// Шаблонный класс Queue с обработкой исключений
template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
    }

    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("Cannot pop from empty queue");
        }
        T first = elements.front();
        elements.erase(elements.begin());
        return first;
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    // Тестирование GameManager с исключениями
    std::cout << "=== GameManager Exception Test ===" << std::endl;
    try {
        GameManager<Entity> manager;
        manager.addEntity(new Player("Hero", -100, 0)); // Вызовет исключение
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "GameManager error: " << e.what() << std::endl;
    }

    // Тестирование Queue с исключениями
    std::cout << "\n=== Queue Exception Test ===" << std::endl;
    try {
        Queue<int> intQueue;
        intQueue.push(10);
        std::cout << "Popped: " << intQueue.pop() << std::endl;
        std::cout << "Trying to pop from empty queue..." << std::endl;
        intQueue.pop(); // Вызовет исключение
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Queue error: " << e.what() << std::endl;
    }

    // Успешный сценарий
    std::cout << "\n=== Successful Scenario ===" << std::endl;
    try {
        GameManager<Entity> manager;
        manager.addEntity(new Player("Warrior", 150, 10));
        manager.addEntity(new Player("Mage", 80, 20));
        manager.displayAll();

        Queue<std::string> stringQueue;
        stringQueue.push("First");
        stringQueue.push("Second");
        std::cout << "Popped: " << stringQueue.pop() << std::endl;
        std::cout << "Popped: " << stringQueue.pop() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
