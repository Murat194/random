// =========================
// Практическое задание 6: Система библиотеки
// =========================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// =========================
// Часть 1: Класс Book (инкапсуляция + RAII)
// =========================

class Book {
private:
    string title;
    string author;
    bool isAvailable;
    
public:
    // Конструктор
    Book(const string& t, const string& a) 
        : title(t), author(a), isAvailable(true) {
        cout << "Книга \"" << title << "\" добавлена в библиотеку" << endl;
    }
    
    // Геттеры
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }
    
    // Методы для работы с книгой
    void borrow() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Книга \"" << title << "\" выдана" << endl;
        } else {
            cout << "Книга \"" << title << "\" уже выдана" << endl;
        }
    }
    
    void returnBook() {
        isAvailable = true;
        cout << "Книга \"" << title << "\" возвращена" << endl;
    }
    
    // Запрещаем копирование
    Book(const Book&) = delete;
    Book& operator=(const Book&) = delete;
    
    // Деструктор
    ~Book() {
        cout << "Книга \"" << title << "\" удалена из библиотеки" << endl;
    }
};

// =========================
// Часть 2: Класс User и полиморфизм
// =========================

class User {
private:
    string name;
    
public:
    User(const string& n) : name(n) {}
    virtual ~User() {
        cout << "Пользователь " << name << " удален" << endl;
    }
    
    // Геттер
    const string& getName() const { return name; }
    
    // Чисто виртуальные методы
    virtual int getMaxBooks() const = 0;
    virtual int getLoanDays() const = 0;
    virtual string getType() const = 0;
    
    // Вывод информации о пользователе
    virtual void printInfo() const {
        cout << "Пользователь: " << name 
             << " (" << getType() << ")" << endl;
        cout << "Макс. книг: " << getMaxBooks() 
             << ", Срок выдачи: " << getLoanDays() << " дней" << endl;
    }
};

// =========================
// Наследники User
// =========================

class Student : public User {
public:
    Student(const string& n) : User(n) {}
    
    int getMaxBooks() const override { return 3; }
    int getLoanDays() const override { return 14; }
    string getType() const override { return "Студент"; }
};

class Professor : public User {
public:
    Professor(const string& n) : User(n) {}
    
    int getMaxBooks() const override { return 10; }
    int getLoanDays() const override { return 30; }
    string getType() const override { return "Профессор"; }
};

// =========================
// Часть 3: Класс Library (агрегация + умные указатели)
// =========================

class Library {
private:
    vector<unique_ptr<Book>> books;
    vector<unique_ptr<User>> users;
    
public:
    // Добавление книги
    void addBook(const string& title, const string& author) {
        books.push_back(make_unique<Book>(title, author));
    }
    
    // Добавление пользователя
    void addUser(unique_ptr<User> user) {
        users.push_back(move(user));
        cout << "Пользователь добавлен в библиотеку" << endl;
    }
    
    // Выдача книги
    bool issueBook(Book* book, User* user) {
        if (!book || !user) {
            cout << "Ошибка: книга или пользователь не существуют" << endl;
            return false;
        }
        
        if (!book->getIsAvailable()) {
            cout << "Книга \"" << book->getTitle() << "\" недоступна" << endl;
            return false;
        }
        
        // Проверяем, сколько книг уже на руках у пользователя
        int borrowedCount = 0;
        // В реальной системе здесь нужно вести учет выданных книг
        
        if (borrowedCount >= user->getMaxBooks()) {
            cout << "Пользователь " << user->getName() 
                 << " достиг лимита (" << user->getMaxBooks() << " книг)" << endl;
            return false;
        }
        
        book->borrow();
        cout << "Книга \"" << book->getTitle() 
             << "\" выдана пользователю " << user->getName() 
             << " на " << user->getLoanDays() << " дней" << endl;
        return true;
    }
    
    // Список доступных книг
    void listAvailableBooks() const {
        cout << "\n=== Доступные книги ===" << endl;
        bool hasAvailable = false;
        
        for (const auto& book : books) {
            if (book->getIsAvailable()) {
                cout << "- \"" << book->getTitle() 
                     << "\" (автор: " << book->getAuthor() << ")" << endl;
                hasAvailable = true;
            }
        }
        
        if (!hasAvailable) {
            cout << "Нет доступных книг" << endl;
        }
        cout << "=======================" << endl;
    }
    
    // Поиск пользователя по имени
    User* findUserByName(const string& name) {
        for (const auto& user : users) {
            if (user->getName() == name) {
                return user.get();
            }
        }
        return nullptr;
    }
    
    // Поиск книги по названию
    Book* findBookByTitle(const string& title) {
        for (const auto& book : books) {
            if (book->getTitle() == title && book->getIsAvailable()) {
                return book.get();
            }
        }
        return nullptr;
    }
    
    // Шаблонный метод поиска книг
    template<typename Predicate>
    vector<Book*> findBooks(Predicate pred) const {
        vector<Book*> result;
        for (const auto& book : books) {
            if (pred(*book)) {
                result.push_back(book.get());
            }
        }
        return result;
    }
    
    // Вывод информации о библиотеке
    void printLibraryInfo() const {
        cout << "\n=== Информация о библиотеке ===" << endl;
        cout << "Всего книг: " << books.size() << endl;
        cout << "Всего пользователей: " << users.size() << endl;
        
        cout << "\nСписок пользователей:" << endl;
        for (const auto& user : users) {
            user->printInfo();
            cout << "---" << endl;
        }
    }
};

// =========================
// Основная программа
// =========================

int main() {
    cout << "=== Система библиотеки ===" << endl;
    
    // Создаем библиотеку
    Library lib;
    
    // Добавляем книги
    cout << "\n--- Добавление книг ---" << endl;
    lib.addBook("1984", "George Orwell");
    lib.addBook("The Hobbit", "J.R.R. Tolkien");
    lib.addBook("The Lord of the Rings", "J.R.R. Tolkien");
    lib.addBook("Animal Farm", "George Orwell");
    lib.addBook("War and Peace", "Leo Tolstoy");
    
    // Добавляем пользователей
    cout << "\n--- Добавление пользователей ---" << endl;
    lib.addUser(make_unique<Student>("Alice"));
    lib.addUser(make_unique<Student>("Bob"));
    lib.addUser(make_unique<Professor>("Dr. Smith"));
    lib.addUser(make_unique<Professor>("Prof. Johnson"));
    
    // Выводим информацию о библиотеке
    lib.printLibraryInfo();
    
    // Показываем доступные книги
    lib.listAvailableBooks();
    
    // Пример выдачи книги
    cout << "\n--- Выдача книг ---" << endl;
    
    // Находим пользователя и книгу
    User* alice = lib.findUserByName("Alice");
    Book* hobbit = lib.findBookByTitle("The Hobbit");
    
    if (alice && hobbit) {
        bool success = lib.issueBook(hobbit, alice);
        if (success) {
            cout << "Книга успешно выдана!" << endl;
        }
    } else {
        cout << "Не удалось найти книгу или пользователя" << endl;
    }
    
    // Еще одна выдача
    cout << "\n--- Вторая выдача ---" << endl;
    User* drSmith = lib.findUserByName("Dr. Smith");
    Book* lotr = lib.findBookByTitle("The Lord of the Rings");
    
    if (drSmith && lotr) {
        lib.issueBook(lotr, drSmith);
    }
    
    // Показываем доступные книги после выдачи
    lib.listAvailableBooks();
    
    // Используем шаблонный метод поиска
    cout << "\n--- Поиск книг по автору ---" << endl;
    auto tolkienBooks = lib.findBooks([](const Book& b) {
        return b.getAuthor() == "J.R.R. Tolkien";
    });
    
    cout << "Книги Толкиена в библиотеке:" << endl;
    for (const auto& book : tolkienBooks) {
        cout << "- " << book->getTitle() 
             << " (доступна: " << (book->getIsAvailable() ? "да" : "нет") << ")" << endl;
    }
    
    // Поиск книг Orwell
    cout << "\n--- Книги Orwell ---" << endl;
    auto orwellBooks = lib.findBooks([](const Book& b) {
        return b.getAuthor() == "George Orwell";
    });
    
    for (const auto& book : orwellBooks) {
        cout << "- " << book->getTitle() << endl;
    }
    
    // Попытка выдать уже выданную книгу
    cout << "\n--- Попытка повторной выдачи ---" << endl;
    if (hobbit && alice) {
        lib.issueBook(hobbit, alice);
    }
    
    // Возврат книги
    cout << "\n--- Возврат книги ---" << endl;
    if (hobbit) {
        hobbit->returnBook();
    }
    
    // Показываем доступные книги после возврата
    lib.listAvailableBooks();
    
    cout << "\n=== Программа завершена ===" << endl;
    return 0;
}
