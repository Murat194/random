#include <iostream>
#include <vector>
#include <string>

using namespace std;

// =========================
// Задание 1: Ассоциация
// =========================

class Author {
public:
    string name;
};

class Book {
public:
    string title;
    Author* author;

    void printInfo() {
        cout << "Книга: " << title << endl;
        if (author != nullptr) {
            cout << "Автор: " << author->name << endl;
        } else {
            cout << "Автор: неизвестен" << endl;
        }
        cout << "-------------------" << endl;
    }
};

// =========================
// Задание 2: Агрегация
// =========================

class Student {
public:
    string name;
    int year;
};

class Group {
public:
    string title;
    vector<Student*> students;

    void addStudent(Student* s) {
        students.push_back(s);
    }

    void printGroup() {
        cout << "Группа: " << title << endl;
        cout << "Студенты: " << endl;
        for (const auto& student : students) {
            cout << " - " << student->name << " (курс " << student->year << ")" << endl;
        }
        cout << "===================" << endl;
    }
};

// =========================
// Задание 3: Композиция
// =========================

class Room {
public:
    string name;
    double area;
};

class House {
public:
    string address;
    vector<Room> rooms;

    void addRoom(const string& name, double area) {
        Room r;
        r.name = name;
        r.area = area;
        rooms.push_back(r);
    }

    double totalArea() {
        double total = 0;
        for (const auto& room : rooms) {
            total += room.area;
        }
        return total;
    }

    void printInfo() {
        cout << "Дом по адресу: " << address << endl;
        cout << "Комнаты: " << endl;
        for (const auto& room : rooms) {
            cout << " - " << room.name << " (площадь: " << room.area << " кв.м)" << endl;
        }
        cout << "===================" << endl;
    }
};

int main() {
    // =========================
    // Задание 1: Ассоциация
    // =========================
    cout << "=== Задание 1: Ассоциация ===" << endl;

    Author a1, a2;
    a1.name = "Лев Толстой";
    a2.name = "Федор Достоевский";

    Book b1, b2, b3;
    b1.title = "Война и мир";
    b1.author = &a1;

    b2.title = "Преступление и наказание";
    b2.author = &a2;

    b3.title = "Анна Каренина";
    b3.author = &a1;

    b1.printInfo();
    b2.printInfo();
    b3.printInfo();

    // =========================
    // Задание 2: Агрегация
    // =========================
    cout << "=== Задание 2: Агрегация ===" << endl;

    Student s1, s2, s3;
    s1.name = "Иван Иванов";
    s1.year = 2;
    s2.name = "Мария Петрова";
    s2.year = 3;
    s3.name = "Алексей Сидоров";
    s3.year = 1;

    Group g;
    g.title = "ПИ-2023";
    g.addStudent(&s1);
    g.addStudent(&s2);
    g.addStudent(&s3);

    g.printGroup();

    // =========================
    // Задание 3: Композиция
    // =========================
    cout << "=== Задание 3: Композиция ===" << endl;

    House h;
    cout << "Введите адрес дома: ";
    getline(cin, h.address);

    h.addRoom("Гостиная", 25.5);
    h.addRoom("Спальня", 18.0);
    h.addRoom("Кухня", 12.0);
    h.addRoom("Ванная", 8.5);

    h.printInfo();
    cout << "Общая площадь: " << h.totalArea() << " кв.м" << endl;

    return 0;
}
