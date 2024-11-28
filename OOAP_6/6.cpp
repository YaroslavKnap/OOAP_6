#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>

// Базовий клас Будинку
class House {
protected:
    double area;
    int floors;
    std::string address;

public:
    virtual ~House() {}
    virtual std::shared_ptr<House> clone() const = 0;
    virtual void displayInfo() const = 0;
    virtual void editInfo() = 0;

    void setArea(double newArea) { area = newArea; }
    void setFloors(int newFloors) { floors = newFloors; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
};

// Клас багатоквартирного будинку
class ApartmentBuilding : public House {
    std::vector<std::string> owners;

public:
    ApartmentBuilding(double a, int f, const std::string& addr, const std::vector<std::string>& own)
        : owners(own) {
        area = a;
        floors = f;
        address = addr;
    }
    // 1
    std::shared_ptr<House> clone() const override {
        return std::make_shared<ApartmentBuilding>(*this);
    }

    void displayInfo() const override {
        std::cout << "Багатоквартирний будинок\n"
            << "Площа: " << area << " кв.м\n"
            << "Кількість поверхів: " << floors << "\n"
            << "Адреса: " << address << "\n"
            << "Власники квартир:\n";
        for (const auto& owner : owners) {
            std::cout << "- " << owner << "\n";
        }
    }

    void editInfo() override {
        std::cout << "Редагуємо багатоквартирний будинок:\n";
        std::cout << "Нова площа: ";
        std::cin >> area;
        std::cout << "Нова кількість поверхів: ";
        std::cin >> floors;
        std::cin.ignore();
        std::cout << "Нова адреса: ";
        std::getline(std::cin, address);
        owners.clear();
        int numOwners;
        std::cout << "Кількість нових власників: ";
        std::cin >> numOwners;
        std::cin.ignore();
        for (int i = 0; i < numOwners; ++i) {
            std::string owner;
            std::cout << "Власник " << i + 1 << ": ";
            std::getline(std::cin, owner);
            owners.push_back(owner);
        }
    }
};

// Клас котеджу
class Cottage : public House {
    std::string owner;

public:
    Cottage(double a, int f, const std::string& addr, const std::string& own)
        : owner(own) {
        area = a;
        floors = f;
        address = addr;
    }
    //2
    std::shared_ptr<House> clone() const override {
        return std::make_shared<Cottage>(*this);
    }

    void displayInfo() const override {
        std::cout << "Котедж\n"
            << "Площа: " << area << " кв.м\n"
            << "Кількість поверхів: " << floors << "\n"
            << "Адреса: " << address << "\n"
            << "Власник: " << owner << "\n";
    }

    void editInfo() override {
        std::cout << "Редагуємо котедж:\n";
        std::cout << "Нова площа: ";
        std::cin >> area;
        std::cout << "Нова кількість поверхів: ";
        std::cin >> floors;
        std::cin.ignore();
        std::cout << "Нова адреса: ";
        std::getline(std::cin, address);
        std::cout << "Новий власник: ";
        std::getline(std::cin, owner);
    }
};

// Контейнер будинків
class HouseManager {
    std::vector<std::shared_ptr<House>> houses;

public:
    void addHouse(const std::shared_ptr<House>& house) {
        houses.push_back(house);
    }

    void displayHouses() const {
        if (houses.empty()) {
            std::cout << "Список будинків порожній.\n";
            return;
        }
        for (size_t i = 0; i < houses.size(); ++i) {
            std::cout << "\nБудинок #" << i + 1 << ":\n";
            houses[i]->displayInfo();
        }
    }

    void editHouse(size_t index) {
        if (index >= houses.size()) {
            std::cout << "Неправильний індекс будинку.\n";
            return;
        }
        houses[index]->editInfo();
    }
};

int main() {
    setlocale(LC_ALL, "ukr");
    HouseManager manager;

    // Створення прототипів
    auto apartmentPrototype = std::make_shared<ApartmentBuilding>(
        1200.0, 10, "вул. Київська, 1", std::vector<std::string>{"Іваненко", "Петренко"});
    auto cottagePrototype = std::make_shared<Cottage>(
        250.0, 2, "вул. Львівська, 12", "Коваленко");


    // Клонування будинків
    manager.addHouse(apartmentPrototype->clone());
    manager.addHouse(cottagePrototype->clone());

    // Виведення будинків
    std::cout << "Список будинків:\n";
    manager.displayHouses();

    // Редагування будинку
    size_t index;
    std::cout << "\nВведіть індекс будинку для редагування (починаючи з 1): ";
    std::cin >> index;
    manager.editHouse(index - 1);

    // Повторний вивід
    std::cout << "\nОновлений список будинків:\n";
    manager.displayHouses();

    return 0;
}
