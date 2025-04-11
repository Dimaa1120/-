#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Inventory {
private:
    std::vector<std::unique_ptr<std::string>> items; // Динамический массив строк

public:
    // Добавление предмета в инвентарь
    void addItem(const std::string& item) {
        items.push_back(std::make_unique<std::string>(item));
    }

    // Вывод содержимого инвентаря
    void displayInventory() const {
        if (items.empty()) {
            std::cout << "Inventory is empty.\n";
            return;
        }

        std::cout << "=== Inventory Contents ===\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << *items[i] << "\n";
        }
    }

    // Автоматическое освобождение памяти через unique_ptr
    ~Inventory() {
        std::cout << "Inventory cleared.\n";
    }
};

int main() {
    // Создаем инвентарь
    Inventory inv;

    // Добавляем предметы
    inv.addItem("Steel Sword");
    inv.addItem("Health Potion");
    inv.addItem("Magic Ring");

    // Выводим содержимое
    inv.displayInventory();

    // Добавляем еще один предмет
    std::cout << "\nAdding new item...\n";
    inv.addItem("Ancient Scroll");
    inv.displayInventory();

    // Память автоматически освободится при выходе из области видимости
    return 0;
}


