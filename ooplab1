#include <iostream>
#include <string>
#include <vector>
using namespace std;


// class Point {
// private:
//     int x;
//     int y;

// public:
//     Point(int a, int b){
//         x = a;
//         y = b;
//     }
    
//     void move(int a, int b){
//         x += a;
//         y += b;
//     }
    
//     void Display(){
//         cout << x << " " << y << endl;
//     }
    
//     void Read() {
//         int a, b;
//         cin >> a;
//         cin >> b;
//         y += a;
//         y += b;
//     }
    
//     ~Point(){}
// };

// int main() {
//     Point p(1, 2);
//     p.Display();
//     p.move(2, 2);
//     p.Display();
//     p.Read();
//     p.Display();
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Calculator {
// private:
//     double a;
//     double b;
// public:
//     Calculator(double x, double y){
//         a = x;
//         b = y;
//     }
    
//     double getSum() const {
//         return a + b;
//     }
    
//     double getMin() const {
//         return a - b;
//     }
    
//     double getMul() const {
//         return a * b;
//     }
    
//     double getDiv() const {
//         if(b != 0) {
//             return a / b;
//         } else {
//             cout << "error div 0" << endl;
//         }
//     }
    
//     void Display(){
//         cout << a << " " << b << endl;
//     }
    
//     void Read(){
//         // int x, y;
//         cin >> a;
//         cin >> b;
//         // a += x;
//         // b += y;
//     }
    
//     ~Calculator(){}
// };

// int main(){
//     Calculator a(10, 5);
//     // a.Read();
//     cout << a.getSum() << endl;
//     cout << a.getMin() << endl;
//     cout << a.getMul() << endl;
//     cout << a.getDiv() << endl;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Student {
// private:
//     string name;
//     int year;
//     double avg;
// public:
//     Student(){};
    
//     Student(string a, int b, double c){
//         name = a;
//         year = b;
//         avg = c;
//     }
    
//     void setName(string a){
//         name = a;
//     }
//     void setYear(int a){
//         year = a;
//     }
//     void setAvg(double a){
//         avg = a;
//     }
    
//     string getName(){
//         return name;
//     }
//     int getYear(){
//         return year;
//     }
//     double getAvg(){
//         return avg;
//     }
    
//     void Display(){
//         cout << "name: " << name << " year: " << year << " avg ocenka: " << avg << endl;
//     }
    
//     void Read(){
//         cin >> name;
//         cin >> year;
//         cin >> avg;
//     }
    
//     ~Student(){}
// };

// class StudentManager {
// private:
//     vector<Student> students;
// public:

//     void addStudent(Student a) {
//         students.push_back(a);
//     }
    
//     void removeStudent(int index) {
//         if (index >= 0 && index < students.size()) {
//             students.erase(students.begin() + index);
//         } else {
//             cout << "error no student" << endl;
//         }
//     }
    
//     void DisplayAll() {
//         if (students.empty()) {
//             cout << "error no students" << endl;
//         } else {
//             for (int i = 0; i < students.size(); ++i) {
//                 students[i].Display();
//             }
//         }
//     }
    
    
// };

// int main() {
//     StudentManager manager;


//     Student s1("Vlad", 19, 4.8);
//     Student s2("Nikita", 19, 3.3);
//     Student s3;
    
//     s3.Read();
    
//     manager.addStudent(s1);
//     manager.addStudent(s2);
//     manager.addStudent(s3);

//     manager.DisplayAll();
//     cout << endl << endl;
    
//     manager.removeStudent(1);
//     manager.DisplayAll();

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// class Book {
// private:
//     string name;
//     string author;
//     int year;

// public:
//     Book(){};
    
//     Book(string a, string b, int c) {
//         name = a;
//         author = b;
//         year = c;
//     }

//     string getName() { return name; }
//     string getAuthor() { return author; }
//     int getYear() { return year; }

//     void Display() const {
//         cout << "name: " << name << " author: " << author << " year: " << year << endl;
//     }

//     void Read(){
//         cin >> name;
//         cin >> author;
//         cin >> year;
//     }

//     ~Book() {}
// };

// int main() {
    
//     Book b1("Vlad", "Vladosik", 2000);
//     Book b2("Vlad", "Vladosik", 2002);
//     Book b3("Vlad", "Vladosik", 1990);
//     Book b4("Vlad", "Vladosik", 2006);
//     Book b5;
    
//     b5.Read();
//     vector<Book> books;

//     books.push_back(b1);
//     books.push_back(b2);
//     books.push_back(b3);
//     books.push_back(b4);
//     books.push_back(b5);

//     for (auto book : books) {
//         book.Display();
//     }

//     sort(books.begin(), books.end(), [](Book a, Book b) {
//         return a.getYear() < b.getYear();
//     });

//     cout << endl;

//     for (auto book : books) {
//         book.Display();
//     }

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// class BankAccount {
// private:
//     string account_number;
//     int balance;  
// public:
//     BankAccount(){};
    
//     BankAccount(string a, int b) { 
//         account_number = a;
//         if (b < 0) {
//             cout << "error" << endl;
//         } else {
//             balance = b;
//         }
//     }
    
//     void deposit(int a) {  
//         if (a > 0) {
//             balance += a;
//             cout << "dep: +" << a << endl << "balik: " << balance << endl;
//         } else {
//             cout << "error" << endl;
//         }
//     }

//     void antidep(int a) {  
//         if (a > 0 && a <= balance) {
//             balance -= a;
//             cout << "anti dep: -" << a << endl << "balik: " << balance << endl;
//         } else {
//             cout << "error" << endl;
//         }
//     }

   
//     void transfer(BankAccount& target_account, int amount) {
//         if (amount > 0 && amount <= balance) {
//             this->antidep(amount);
//             target_account.deposit(amount);
//             cout << "money:" << amount << " from " << account_number 
//                  << " to " << target_account.account_number << endl;
//         } else {
//             cout << "error" << endl;
//         }
//     }

//     void Read() {
//         cin >> account_number;
//         double temp_balance;
//         cin >> temp_balance;
//         if (temp_balance < 0) {
//             cout << "error" << endl;
//         } else {
//             balance = temp_balance;
//         }
//     }


//     void Display() const {
//         cout << "account: " << account_number << " balik: " << balance << endl;
//     }


//     double getBalance() const {
//         return balance;
//     }

//     string getAccountNumber() const {
//         return account_number;
//     }
// };

// int main() {
//     BankAccount account1("acc1", 1000.0);
//     BankAccount account2("acc2", 500.0);
//     BankAccount account3;
//     account3.Read();

//     account1.Display();
//     account2.Display();
//     account3.Display();

//     account1.deposit(200.0);

//     account2.antidep(150.0);

//     account1.transfer(account2, 300.0);

//     account1.Display();
//     account2.Display();
//     account3.Display();
// }





