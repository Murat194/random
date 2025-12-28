#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Vehicle {
protected:
    string type;
    int speed;
public:
    Vehicle(string t, int s) : type(t), speed(s) {}
    virtual ~Vehicle()=default;
    virtual void move() const{cout<<getType()<<" скорость: "<<getSpeed()<<endl;};
    string getType() const { return type; }
    int getSpeed() const { return speed; }
};
class Car : public Vehicle {
private:
    int passengers;
public:
    Car(string t, int s, int p) : Vehicle(t, s), passengers(p) {}
    ~Car() override {}
    
    void move() const override {
        cout<<getType()<< ",скорость: "<<getSpeed()<<", пассажиров: "<<getPassengers()<<endl;
    }
    
    int getPassengers() const { return passengers; }
};

class Boat : public Vehicle {
private:
    string name; int maxSpeed;
public:
    Boat(string n, int max) : Vehicle(n, max),name(n),maxSpeed(max) {}
    ~Boat() override {}
    void move() const override {
        cout << "Boat " << type << " sails at " << speed << " km/h" << endl;
    }
    string getName() const { return name; }
    int getMaxSpeed() const { return maxSpeed; }
};

int main() {
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Car>("Sedan", 120, 5));
    fleet.push_back(make_unique<Vehicle>("qwe", 120));
    fleet.push_back(make_unique<Boat>("Yacht", 60));
    for (auto& f: fleet) {
        f->move();
    }

}
