#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

// Базовый класс Entity
class Entity {
public:
    virtual ~Entity() = default;
    virtual std::string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getLevel() const = 0;
    virtual std::string serialize() const = 0; // Сериализация в строку
};

// Класс Player
class Player : public Entity {
private:
    std::string name;
    int health;
    int level;

public:
    Player(const std::string& name, int health, int level)
        : name(name), health(health), level(level) {
    }

    std::string getName() const override { return name; }
    int getHealth() const override { return health; }
    int getLevel() const override { return level; }

    // Сериализация в строку (формат: "Player|name|health|level")
    std::string serialize() const override {
        return "Player|" + name + "|" + std::to_string(health) + "|" + std::to_string(level);
    }

    // Десериализация из строки
    static Player* deserialize(const std::string& data) {
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);
        size_t pos3 = data.find('|', pos2 + 1);

        std::string name = data.substr(pos1 + 1, pos2 - pos1 - 1);
        int health = std::stoi(data.substr(pos2 + 1, pos3 - pos2 - 1));
        int level = std::stoi(data.substr(pos3 + 1));

        return new Player(name, health, level);
    }
};

// Шаблонный класс GameManager
template <typename T>
class GameManager {
private:
    std::vector<T> entities;

public:
    void addEntity(T entity) {
        entities.push_back(entity);
    }

    void displayAll() const {
        for (const auto& entity : entities) {
            std::cout << "Name: " << entity->getName()
                << ", Health: " << entity->getHealth()
                << ", Level: " << entity->getLevel() << std::endl;
        }
    }

    const std::vector<T>& getEntities() const {
        return entities;
    }

    void clear() {
        for (auto& entity : entities) {
            delete entity;
        }
        entities.clear();
    }
};

// Функция сохранения в файл
void saveToFile(const GameManager<Entity*>& manager, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    for (const auto& entity : manager.getEntities()) {
        file << entity->serialize() << std::endl;
    }
}

// Функция загрузки из файла
void loadFromFile(GameManager<Entity*>& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    manager.clear(); // Очищаем текущие данные

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Определяем тип объекта (в данном случае только Player)
        if (line.find("Player|") == 0) {
            Entity* player = Player::deserialize(line);
            manager.addEntity(player);
        }
        // Можно добавить обработку других типов Entity
    }
}

int main() {
    GameManager<Entity*> manager;

    // Создаём несколько персонажей
    manager.addEntity(new Player("Hero", 100, 1));
    manager.addEntity(new Player("Warrior", 150, 2));
    manager.addEntity(new Player("Mage", 80, 3));

    // Сохраняем в файл
    try {
        saveToFile(manager, "game_save.txt");
        std::cout << "Data saved successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
    }

    // Загружаем из файла в новый менеджер
    GameManager<Entity*> loadedManager;
    try {
        loadFromFile(loadedManager, "game_save.txt");
        std::cout << "Data loaded successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
    }

    // Выводим загруженные данные
    loadedManager.displayAll();

    // Очищаем память
    manager.clear();
    loadedManager.clear();

    return 0;
}
