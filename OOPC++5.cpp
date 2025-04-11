#include <iostream>
#include <vector>
#include <memory>

// Шаблонный класс Queue
template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    // Добавление элемента в очередь
    void push(const T& item) {
        elements.push_back(item);
    }

    // Удаление и возврат первого элемента
    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("Queue is empty!");
        }
        T first = elements.front();
        elements.erase(elements.begin());
        return first;
    }

    // Проверка на пустоту
    bool empty() const {
        return elements.empty();
    }

    // Получение размера очереди
    size_t size() const {
        return elements.size();
    }
};

// Пример класса для демонстрации работы GameManager
class Entity {
public:
    virtual void displayInfo() const = 0;
    virtual ~Entity() {}
};

class Player : public Entity {
    std::string name;
    int health;
public:
    Player(const std::string& n, int h) : name(n), health(h) {}
    void displayInfo() const override {
        std::cout << "Player: " << name << ", HP: " << health << "\n";
    }
};

class Enemy : public Entity {
    std::string name;
    std::string type;
public:
    Enemy(const std::string& n, int h, const std::string& t) : name(n), type(t) {}
    void displayInfo() const override {
        std::cout << "Enemy: " << name << ", Type: " << type << "\n";
    }
};

// Шаблонный класс GameManager (из примера)
template <typename T>
class GameManager {
private:
    std::vector<std::unique_ptr<T>> entities;

public:
    void addEntity(T* entity) {
        entities.emplace_back(entity);
    }

    void displayAll() const {
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }
};

int main() {
    // Демонстрация работы Queue с разными типами
    std::cout << "=== Queue Demonstration ===\n";

    // Очередь для целых чисел
    Queue<int> intQueue;
    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);

    std::cout << "Integer queue (" << intQueue.size() << " elements):\n";
    while (!intQueue.empty()) {
        std::cout << "Popped: " << intQueue.pop() << "\n";
    }

    // Очередь для строк
    Queue<std::string> stringQueue;
    stringQueue.push("First");
    stringQueue.push("Second");
    stringQueue.push("Third");

    std::cout << "\nString queue (" << stringQueue.size() << " elements):\n";
    while (!stringQueue.empty()) {
        std::cout << "Popped: " << stringQueue.pop() << "\n";
    }

    // Демонстрация GameManager
    std::cout << "\n=== GameManager Demonstration ===\n";
    GameManager<Entity> gameManager;
    gameManager.addEntity(new Player("Hero", 100));
    gameManager.addEntity(new Enemy("Goblin", 50, "Goblin"));
    gameManager.displayAll();

    return 0;
}
