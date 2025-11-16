#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Animal {
private:
    string name;
public:
    Animal(const string& a) : name(a){};
    
    string getName() const {
        return name;
    }
    
    virtual void makeSound() const = 0; 
    
    virtual ~Animal(){
        cout << "deleted" << endl;
    }
};

class Dog: public Animal{
private:
    int age;
public:
    Dog(const std::string& name, int age) : Animal(name) { 
        this->age = age; 
    }
    
    ~Dog(){
        cout << "deleted2" << endl;
    }
    
    int getAge() const {
        return age;
    }
    
    void makeSound() const override { 
        cout << getName() << " says: Woof!" << endl; 
    }
    
    bool operator==(const Dog& other) const { 
        return getName() == other.getName() && age == other.age; 
    } 
    
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog) { 
        os << "Dog(name=\"" << dog.getName() << "\", age=" << dog.age << ")"; 
        return os; 
    }
    
};

class Cat: public Animal{
private:
    bool isLazy;
public:
    Cat(const std::string& name, bool isLazy) : Animal(name) {
        this->isLazy = isLazy;
    }
    
    bool getIsLazy() const {
        return isLazy;
    }
    
    void makeSound() const override { 
    cout << getName() << " says: Meow!" << endl; 
    } 
    
};

int main() {
    Dog d1("Rex", 3); 
    Dog d2("Rex", 3); 
    Dog d3("Max", 4); 
    std::cout << d1 << std::endl;
    std::cout << (d1 == d2) << std::endl; 
    std::cout << (d1 == d3) << std::endl; 
}
