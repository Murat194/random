#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class FileResource {
private:
    string filename;
    bool isOpen;
public:
    FileResource(const string& name) : filename(name), isOpen(false) {}

    virtual ~FileResource() {
        if (isOpen) {
            cout << "Предупреждение: Файл '" << filename << "' был уничтожен, но оставался открытым." << endl;
        }
    }


    virtual void open() = 0;
    virtual void close() = 0;
    virtual void read() = 0;


    const string& getFilename() const { 
        return filename;
    }
    bool getIsOpen() const { 
        return isOpen; 
    }

protected:
    void setIsOpen(bool state) { isOpen = state; }
};


class TextFile : public FileResource {
public:
    TextFile(const string& name) : FileResource(name) {}

    void open() override {
        cout << "Opening TextFile: " << getFilename() << endl;
        setIsOpen(true);
    }

    void close() override {
        if (getIsOpen()) {
            cout << "Closing TextFile: " << getFilename() << endl;
            setIsOpen(false);
        }
    }

    void read() override {
        if (getIsOpen()) {
            cout << "Reading TextFile: " << getFilename() << endl;
        } else {
            cout << "Error: Cannot read TextFile " << getFilename() << ", it's not open." << endl;
        }
    }
};

class BinaryFile : public FileResource {
public:
    BinaryFile(const string& name) : FileResource(name) {}

    void open() override {
        cout << "Opening BinaryFile: " << getFilename() << endl;
        setIsOpen(true);
    }

    void close() override {
        if (getIsOpen()) {
            cout << "Closing BinaryFile: " << getFilename() << endl;
            setIsOpen(false);
        }
    }

    void read() override {
        if (getIsOpen()) {
            cout << "Reading BinaryFile: " << getFilename() << endl;
        } else {
            cout << "Error: Cannot read BinaryFile " << getFilename() << ", it's not open." << endl;
        }
    }
};

int main() {
    
    // FileResource* tf_raw = new TextFile("main.txt");
    // FileResource* bf_raw = new BinaryFile("main.bin");

    // // Помещаем указатели в вектор
    // vector<FileResource*> raw_ptrs;
    // raw_ptrs.push_back(tf_raw);
    // raw_ptrs.push_back(bf_raw);

    // // Вызываем open() и read()
    // for (auto& ptr : raw_ptrs) {
    //     ptr->open();
    //     ptr->read();
    //     //ptr->close();
    // }

    // raw_ptrs[0]->close(); // Закрываем один
    // delete bf_raw;

    // for (auto& ptr : raw_ptrs) {
    //     delete ptr;
    // }
   

    vector<unique_ptr<FileResource>> fileContainer;

    fileContainer.push_back(make_unique<TextFile>("main.py"));
    fileContainer.push_back(make_unique<BinaryFile>("main.cpp"));

    for (auto& ptr : fileContainer) {
        ptr->open();
        ptr->read();
        // ptr->close();
    }

    // fileContainer[0]->close();
    return 0;
}
