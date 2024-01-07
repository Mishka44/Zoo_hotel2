#include <set>
#include <iostream>
#include<unordered_set>
#include<Windows.h>
#include<fstream>

class Animal {
public:

    Animal(std::string new_name, int new_age, std::string new_type) :name(new_name),
        age(new_age), type_of_animal(new_type) {}


    std::string Get_name() {
        return this->name;
    }
    void Set_name(std::string new_name) {
        this->name = new_name;
    }

    int Get_age() {
        return this->age;
    }
    void Set_name(int new_age) {
        this->age = new_age;
    }
    std::string Get_type() {
        return this->type_of_animal;
    }
    void Set_type(std::string new_type) {
        this->type_of_animal = new_type;
    }

    //virtual void Sound() =0;

private:
    std::string name;
    int age;
    std::string type_of_animal; //конкретно класс животного(как в систематике)


};


class Zoo_hostel {
public:
    Zoo_hostel() = default;


    void Add_Animal(Animal* obj) {
        if (zoo.find(obj) == zoo.end()) {
            this->zoo.insert(obj);
            std::cout << "Новое животное добавлено!" << "\n";
        }
        else {
            std::cout << "Ошибка, животное уже есть в базе:(" << "\n";
        }
    }

    void Show() {
        std::cout << "Текущие посетители гостиницы: " << "\n";
        for (auto& i : this->zoo) {
            std::cout << i->Get_name() << ", " << i->Get_age() << ", " << i->Get_type() << "\n";
        }
    }

    void Search_by_name(std::string name_) {
        for (auto& j : zoo)
        {
            std::cout << "Поиск по имени: '" << name_ << " Итог:\n";
            if (j->Get_name() == name_)
            {
                std::cout << j->Get_name() << ", " << j->Get_age() << ", " << j->Get_type() << "\n";
            }
            else {
                std::cout << "Данного животного по имени в списке найдено не было:(";
            }

        }
    }
    void Search_by_type(std::string type) {
        for (auto& el : zoo)
        {
            std::cout << "Поиск по классу животного: '" << type << " Итог:\n";
            if (el->Get_type() == type)
            {
                std::cout << el->Get_name() << ", " << el->Get_age() << ", " << el->Get_type() << "\n";
                
            }
            else {
                std::cout << "Данного животного по классу в списке найдено не было:(";
            }

        }
    }
    void Search_by_age(int age) {
        for (auto& el : zoo)
        {
            std::cout << "Поиск по возрасту животного: '" << age << " Итог:\n";
            if (el->Get_age() == age)
            {
                std::cout << el->Get_name() << ", " << el->Get_age() << ", " << el->Get_type() << "\n";
            }
            else {
                std::cout << "Данного животного по возрасту в списке найдено не было:(";
            }

        }
    }

    void Delete(Animal* obj) {

        auto tmp = zoo.find(obj);
        zoo.erase(tmp);

    }
    std::set<Animal*> Get_base() {
        return this->zoo;
    }

    /*void Search_and_Delete(std::string name, int age, std::string type) {
        Animal tmp(name, age, type);
        for (auto& i : this->zoo) {
            if (tmp.Get_name() == i->Get_name() && tmp.Get_age()
                == i->Get_age() && tmp.Get_type() == i->Get_type()) {
                Delete(i);
            }
        }
    }*/ // не получилось



private:
    std::set<Animal*> zoo;
};

class Work_with_file {
public:
    Work_with_file(Zoo_hostel* zoo_for_save) :zoo_Base(zoo_for_save) {}

    void Save() {
        
        this->File.open("zoo.txt", std::ios::app);
        if (!File.is_open()) {
            std::cout << "Error\n";
        }
        else
        {
            for (auto& i : zoo_Base->Get_base()) {
                File << i->Get_name() << ", " << i->Get_age() << ", " << i->Get_type() << "\n";
            }
        }
        File.close();
    }
    void Clear() {
        File.open("zoo.txt", std::ofstream::out | std::ofstream::trunc);
        File.close();
    }



private:
    Zoo_hostel* zoo_Base;
    std::fstream File;
};



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    Zoo_hostel zoo;
    Work_with_file file(&zoo);
    std::string name, type;
    int age;
    int choice;


    std::cout << "добро пожаловать в гостиницу для животных!";
    do {
        file.Clear();
        std::cout << "Выберите дейтсвие : \n1 - добавть новое животное\n2 - удалить животное " << 
           "\n" << "3 - показать список гостящих в гостинице\n4 - уйти\n"
            << "\nВведите номер желаемого действия: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::cout << "Для добавления нового животного введите его имя: ";
            std::cin >> name;
            std::cout << "Введите класс животного: ";
            std::cin >> type;
            std::cout << "Введите возраст животного: ";
            std::cin >> age;
            Animal animal(name, age, type);
            zoo.Add_Animal(&animal);
            file.Save();
        }
        else if (choice == 2)
        {
            std::cout << "Чтобы найти животное, нужно ввести его данные: " << "\n";
            std::cout << "Имя животного:";
            std::cin >> name;
            std::cout << "\n" << "Класс животного: ";
            std::cin >> type;
            std::cout << "Возраст животного: ";
            std::cin >> age;
            Animal tmp(name, age, type);
            //zoo.Delete(&tmp);
            file.Clear();
            file.Save();
        }
        else if (choice == 3) {
            zoo.Show();
        }

    } while (choice != 4);
    //Animal lion("Simba", 3, "Mammal");
    //Animal Fish("Nemo", 2, "Fish");
    //Zoo_hostel Zoo;
    //Zoo.Add_Animal(&lion);
    //Zoo.Add_Animal(&Fish);
    ////Zoo.Delete(&Fish);
    ////Zoo.Search_and_Delete("Simba", 3, "Mammal");
    //Zoo.Show();

}
