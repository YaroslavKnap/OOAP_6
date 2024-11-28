#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>

// ������� ���� �������
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

// ���� ����������������� �������
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
        std::cout << "���������������� �������\n"
            << "�����: " << area << " ��.�\n"
            << "ʳ������ ��������: " << floors << "\n"
            << "������: " << address << "\n"
            << "�������� �������:\n";
        for (const auto& owner : owners) {
            std::cout << "- " << owner << "\n";
        }
    }

    void editInfo() override {
        std::cout << "�������� ���������������� �������:\n";
        std::cout << "���� �����: ";
        std::cin >> area;
        std::cout << "���� ������� ��������: ";
        std::cin >> floors;
        std::cin.ignore();
        std::cout << "���� ������: ";
        std::getline(std::cin, address);
        owners.clear();
        int numOwners;
        std::cout << "ʳ������ ����� ��������: ";
        std::cin >> numOwners;
        std::cin.ignore();
        for (int i = 0; i < numOwners; ++i) {
            std::string owner;
            std::cout << "������� " << i + 1 << ": ";
            std::getline(std::cin, owner);
            owners.push_back(owner);
        }
    }
};

// ���� �������
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
        std::cout << "������\n"
            << "�����: " << area << " ��.�\n"
            << "ʳ������ ��������: " << floors << "\n"
            << "������: " << address << "\n"
            << "�������: " << owner << "\n";
    }

    void editInfo() override {
        std::cout << "�������� ������:\n";
        std::cout << "���� �����: ";
        std::cin >> area;
        std::cout << "���� ������� ��������: ";
        std::cin >> floors;
        std::cin.ignore();
        std::cout << "���� ������: ";
        std::getline(std::cin, address);
        std::cout << "����� �������: ";
        std::getline(std::cin, owner);
    }
};

// ��������� �������
class HouseManager {
    std::vector<std::shared_ptr<House>> houses;

public:
    void addHouse(const std::shared_ptr<House>& house) {
        houses.push_back(house);
    }

    void displayHouses() const {
        if (houses.empty()) {
            std::cout << "������ ������� �������.\n";
            return;
        }
        for (size_t i = 0; i < houses.size(); ++i) {
            std::cout << "\n������� #" << i + 1 << ":\n";
            houses[i]->displayInfo();
        }
    }

    void editHouse(size_t index) {
        if (index >= houses.size()) {
            std::cout << "������������ ������ �������.\n";
            return;
        }
        houses[index]->editInfo();
    }
};

int main() {
    setlocale(LC_ALL, "ukr");
    HouseManager manager;

    // ��������� ���������
    auto apartmentPrototype = std::make_shared<ApartmentBuilding>(
        1200.0, 10, "���. �������, 1", std::vector<std::string>{"��������", "��������"});
    auto cottagePrototype = std::make_shared<Cottage>(
        250.0, 2, "���. ��������, 12", "���������");


    // ���������� �������
    manager.addHouse(apartmentPrototype->clone());
    manager.addHouse(cottagePrototype->clone());

    // ��������� �������
    std::cout << "������ �������:\n";
    manager.displayHouses();

    // ����������� �������
    size_t index;
    std::cout << "\n������ ������ ������� ��� ����������� (��������� � 1): ";
    std::cin >> index;
    manager.editHouse(index - 1);

    // ��������� ����
    std::cout << "\n��������� ������ �������:\n";
    manager.displayHouses();

    return 0;
}
