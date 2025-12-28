///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #1
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Radio {
private:
    double freq;
public:
    float getFreq() const { return freq; }
    void setfreq(int a) {
        freq = a;
        cout << "New freq = " << freq << " Hz"<<endl;
    }
    void setfreq(float f, int a) {
        freq = f * (pow(10, a));
        cout << "New freq = " << freq << " Hz"<<endl;
    }
    void setfreq(int f, string b) {
        int a = 0;
        if (b == "HZ" || b == "ГЦ") {
            a = 0;
        } else if (b == "KHZ" || b == "KГЦ") {
            a = 3;
        } else if (b == "MHZ" || b == "MГЦ") {
            a = 6;
        } else if (b == "GHZ" || b == "ГГЦ") {
            a = 9;
        }
        freq = f * (pow(10, a));
        cout << "New freq = " << freq << " Hz"<<endl;
    }
    ~Radio() {}
};
int main() {
    Radio europe;
    europe.setfreq(7);
    europe.setfreq(7, 2);
    europe.setfreq(7, "KHZ");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #2

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Money {
private:
    int rub;
    int kop;
    void normal() {
        if (kop >= 100) {kop -= 100; rub += 1;}
        else if (kop < 0) {kop += 100; rub -= 1;}
    }
public:
    Money(int a = 0, int b = 0) : rub(a), kop(b) {
        normal();
    }
    int getRub() const { return rub; }
    int getKop() const { return kop; }
    void setRubles(int r) { 
        rub = r; 
        normal();
    }
    void setKop(int k) { 
        kop = k; 
        normal();
    }
    Money operator+(const Money& other) const {
        return Money(rub + other.rub, kop + other.kop);
    }
    Money operator-(const Money& other) const {
        return Money(rub - other.rub, kop - other.kop);
    }
    friend ostream& operator<<(ostream& os, const Money& m) {
        os << m.rub << "." << m.kop << " py6."<<endl;
        return os;
    }
    ~Money() {}
};

int main() {
    Money aa(120, 10);
    Money bb(110, 100);
    Money cc = aa - bb; cout << cc;
    Money dd = aa + bb; cout << dd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #3

#include <iostream>
using namespace std;
class Clock {
private:
    int hours;
    int minutes;
    int seconds;
    void normal() {
        while (hours >= 24) { hours -= 24; }
        while (minutes >= 60) { minutes -= 60; hours += 1; }
        while (seconds >= 60) { seconds -= 60; minutes += 1; }
    }
public:
    Clock(int a = 0, int b = 0, int c = 0) : hours(a), minutes(b), seconds(c) {
        normal();
    }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
    void setHours(int h) { 
        hours = h; 
        normal();
    }
    void setMinutes(int m) { 
        minutes = m; 
        normal();
    }
    void setSeconds(int s) { 
        seconds = s; 
        normal();
    }
    friend Clock operator+(const Clock& c, int secs);
    friend Clock operator-(const Clock& c, int secs);
    friend ostream& operator<<(ostream& os, const Clock& m) {
        os << m.hours << ":" << m.minutes << ":" << m.seconds << endl;
        return os;
    }
    ~Clock() {}
};
Clock operator+(const Clock& c, int secs) { return Clock(c.hours, c.minutes, c.seconds + secs);
}
Clock operator-(const Clock& c, int secs) { return Clock(c.hours, c.minutes, c.seconds - secs);
}
int main() {
    Clock cc(13, 61, 185); cout << cc;
    Clock dd = cc + 1000; cout << dd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #4

#include <iostream>
#include <cmath>
using namespace std;
class Shape {
public:
    virtual double getArea() const = 0;
    virtual ~Shape() {} 
};
class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double s1, double s2, double s3) : a(s1), b(s2), c(s3) {}
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    void setA(double newA) { a = newA; }
    void setB(double newB) { b = newB; }
    void setC(double newC) { c = newC; }
    
    double getArea() const override {
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    ~Triangle() {}
};
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
    double getArea() const override {
        return width * height;
    }
    ~Rectangle() {}
};
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }
    double getArea() const override {
        return M_PI * radius * radius;
    }
    ~Circle() {}
};
int main() {
    Triangle triangle(3.0, 4.0, 5.0);
    Rectangle rectangle(5.0, 6.0);
    Circle circle(2.5);
    cout << triangle.getArea() << endl;
    cout << rectangle.getArea() << endl;
    cout << circle.getArea() << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #5



#include <iostream>
#include <vector>
#include <string>

using namespace std;
class MenuItem {
public:
    virtual double getitemcost() const = 0;
    virtual ~MenuItem() {}  
};
class Drink : public MenuItem {
private:
    int cost;
public:
    Drink(int c) : cost(c) {}
    int getCost() const { return cost; }
    void setCost(int c) { cost = c; }
    double getitemcost() const override {
        return cost;
    }
    ~Drink() {}
};
class Pizza : public MenuItem {
private:
    int cost;
public:
    Pizza(int c) : cost(c) {}
    int getCost() const { return cost; }
    void setCost(int c) { cost = c; }
    double getitemcost() const override {
        return cost;
    }
    ~Pizza() {}
};
class Salad : public MenuItem {
private:
    int cost;
public:
    Salad(int c) : cost(c) {}
    int getCost() const { return cost; }
    void setCost(int c) { cost = c; }
    double getitemcost() const override {
        return cost;
    }
    ~Salad() {}
};
class Order {
private:
    vector<MenuItem*> items;
public:
    const vector<MenuItem*>& getItems() const { return items; }
    void addItem(MenuItem* item) {
        items.push_back(item);
    }
    double gettotalcost() const {
        double total = 0;
        for (auto item : items) {
            total += item->getitemcost();
        }
        return total;
    }
    ~Order() {
    }
};
int main() {
    Drink cola(120.0);
    Drink juice(50.0);
    Pizza pepperoni(750.0);
    Pizza margherita(650.0);
    Salad caesar(400.0);
    Order order;
    order.addItem(&cola);
    order.addItem(&juice);
    order.addItem(&pepperoni);
    order.addItem(&caesar);
    cout << "Общая стоимость заказа: " << order.gettotalcost() << " руб."
    << endl;
}
