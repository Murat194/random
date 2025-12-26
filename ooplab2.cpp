/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #1
#include <iostream>
using namespace std;

class Room {
protected:
    double length, width, height;
public:
    Room(double l = 0, double w = 0, double h = 0){
        length = l;
        width = w;
        height = h;
    }
    
    void Read() {
        cout << "Введите длину, ширину, высоту: ";
        cin >> length >> width >> height;
    }
    void Display() {
        cout << "Комната: " << length << "x" << width << "x" << height << endl;
    }
    double getArea() {
        return length * width;
    }
};

class OfficeSpace : public Room {
private:
    int roomCount;
    double paintPerSqM;
public:
    OfficeSpace(double l = 0, double w = 0, double h = 0, int rc = 1, double ppm = 1) : Room(l, w, h){
            roomCount = rc;
            paintPerSqM = ppm;
        }
    void Read() {
        Room::Read();
        cout << "Введите кол-во комнат и расход краски на 1 м2: ";
        cin >> roomCount >> paintPerSqM;
    }
    void Display() {
        Room::Display();
        cout << "Комнат: " << roomCount << ", расход краски: " << paintPerSqM << " л/м2" << endl;
    }
    double getPaintNeeded() {
        return roomCount * getArea() * paintPerSqM;
    }
};

int main() {
    
    OfficeSpace office;
    office.Read();
    office.Display();
    cout << "Нужно краски: " << office.getPaintNeeded() << " л" << endl;
    
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #2

#include <iostream>
#include <cmath>
using namespace std;

class Vector {
protected:
    double x1, y1, x2, y2;
public:
    Vector(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}
    void Read() {
        cout << "Введите x1, y1, x2, y2: ";
        cin >> x1 >> y1 >> x2 >> y2;
    }
    void Display() {
        cout << "Вектор: (" << x1 << "," << y1 << ") -> (" << x2 << "," << y2 << ")" << endl;
    }
    double getLength() {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
};

class TwoVectors : public Vector {
private:
    double x3, y3, x4, y4;
public:
    TwoVectors(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0, double a = 0, double b = 0)
        : Vector(x1, y1, x2, y2) {
        x3 = x1 + a;
        y3 = y1 - b;
        x4 = x2 + a;
        y4 = y2 - b;
    }
    void Read() {
        Vector::Read();
        double a, b;
        cout << "Введите смещение a и b: ";
        cin >> a >> b;
        x3 = x1 + a; y3 = y1 - b;
        x4 = x2 + a; y4 = y2 - b;
    }
    void Display() {
        Vector::Display();
        cout << "Второй вектор: (" << x3 << "," << y3 << ") -> (" << x4 << "," << y4 << ")" << endl;
    }
    double getParallelogramArea() {
        return abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    }
};

int main() {
    TwoVectors vecs;
    vecs.Read();
    vecs.Display();
    cout << "Площадь параллелограмма: " << vecs.getParallelogramArea() << endl;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #3

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SalesData {
protected:
    vector<double> sales;
public:
    void Read() {
        int n;
        cout << "Введите количество дней: ";
        cin >> n;
        sales.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "День " << i + 1 << ": ";
            cin >> sales[i];
        }
    }
    void Display() {
        for (int i = 0; i < sales.size(); i++)
            cout << "День " << i + 1 << ": " << sales[i] << endl;
    }
    double getTotal() {
        double sum = 0;
        for (double s : sales) sum += s;
        return sum;
    }
};

class AnalyzedSalesData : public SalesData {
public:
    double getMaxSale() {
        if (sales.empty()) return 0;
        return *max_element(sales.begin(), sales.end());
    }
};

int main() {
    AnalyzedSalesData data;
    data.Read();
    data.Display();
    cout << "Общая сумма: " << data.getTotal() << endl;
    cout << "Максимальная продажа: " << data.getMaxSale() << endl;
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #4

#include <iostream>
using namespace std;

class Matrix {
protected:
    int rows, cols;
    double** data;
public:
    Matrix(int r = 1, int c = 1) : rows(r), cols(c) {
        data = new double*[rows];
        for (int i = 0; i < rows; i++)
            data[i] = new double[cols]{0};
    }
    void Read() {
        cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> data[i][j];
    }
    void Display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }
};

class SquareMatrix : public Matrix {
public:
    SquareMatrix(int n = 1) : Matrix(n, n) {}
    double getDeterminant() {
        if (rows != cols) return 0;
        // Простой случай для 2x2
        if (rows == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        // Для n>2 можно реализовать рекурсивно (опущено для краткости)
        return 0;
    }
};

int main() {
    SquareMatrix m(2);
    m.Read();
    m.Display();
    cout << "Определитель: " << m.getDeterminant() << endl;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// #5

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class SubstringSearcher {
protected:
    string mainStr;
public:
    void Read() {
        cout << "Введите основную строку: ";
        getline(cin, mainStr);
    }
    int findSubstring(const string& sub) {
        size_t pos = mainStr.find(sub);
        return (pos != string::npos) ? pos : -1;
    }
};

class UniqueCharacterCounter {
protected:
    string mainStr;
public:
    void Read() {
        cout << "Введите строку для подсчета уникальных символов: ";
        getline(cin, mainStr);
    }
    int countUniqueChars() {
        unordered_set<char> chars(mainStr.begin(), mainStr.end());
        return chars.size();
    }
};

class StringProcessor : public SubstringSearcher, public UniqueCharacterCounter {
public:
    void Read() {
        SubstringSearcher::Read();
        UniqueCharacterCounter::Read();
    }
};

int main() {
    StringProcessor sp;
    sp.Read();
    string sub;
    cout << "Введите подстроку для поиска: ";
    getline(cin, sub);
    cout << "Индекс подстроки: " << sp.findSubstring(sub) << endl;
    cout << "Уникальных символов: " << sp.countUniqueChars() << endl;
    return 0;
}
