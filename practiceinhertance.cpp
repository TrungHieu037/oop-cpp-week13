#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. Class People (Lớp cha)
// ==========================================
class People {
private:
    string cccd;
    string name;
    string address;

public:
    // Constructor không tham số - gán giá trị mặc định
    People() {
        cccd = "000000000000";
        name = "Unknown";
        address = "Unknown";
    }

    // Constructor có tham số
    People(string c, string n, string a) {
        cccd = c;
        name = n;
        address = a;
    }

    // Getters, Setters
    string getCccd() const { return cccd; }
    string getName() const { return name; }
    string getAddress() const { return address; }

    void setCccd(string c) { cccd = c; }
    void setName(string n) { name = n; }
    void setAddress(string a) { address = a; }

    // Hàm hiển thị thông tin
    void displayInfo() const {
        cout << "CCCD: " << cccd << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
    }
};

// ==========================================
// 2. Class Student (Kế thừa từ People)
// ==========================================
class Student : public People {
private:
    string mssv;
    int yearEntrance;

public:
    // Constructor không tham số - gán giá trị mặc định
    Student() : People() {
        mssv = "N/A";
        yearEntrance = 0;
    }

    // Constructor có tham số
    Student(string c, string n, string a, string m, int y) 
        : People(c, n, a) {
        mssv = m;
        yearEntrance = y;
    }

    // Getters, Setters
    string getMssv() const { return mssv; }
    int getYearEntrance() const { return yearEntrance; }

    void setMssv(string m) { mssv = m; }
    void setYearEntrance(int y) { yearEntrance = y; }

    // Hàm hiển thị thông tin
    void displayInfo() const {
        People::displayInfo();
        cout << "MSSV: " << mssv << endl;
        cout << "YearEntrance: " << yearEntrance << endl;
    }
};

// ==========================================
// 3. Class FIEStudent (Kế thừa từ Student)
// ==========================================
class FIEStudent : public Student {
private:
    int credits;

public:
    // Constructor không tham số - gán giá trị mặc định
    FIEStudent() : Student() {
        credits = 0;
    }

    // Constructor có tham số
    FIEStudent(string c, string n, string a, string m, int y, int cr)
        : Student(c, n, a, m, y) {
        credits = cr;
    }

    // Getters, Setters
    int getCredits() const { return credits; }
    void setCredits(int cr) { credits = cr; }

    // Hàm hiển thị thông tin
    void displayInfo() const {
        Student::displayInfo();
        cout << "Credits: " << credits << endl;
    }
};

// ==========================================
// 4. Hàm main() khởi tạo và hiển thị đối tượng
// ==========================================
int main() {
    // === 1. Tạo các đối tượng People bằng các constructor khác nhau ===
    People p1; // Mặc định
    People p2("079123456789", "Nguyen Van A", "Ho Chi Minh"); // Có tham số

    // === 2. Tạo các đối tượng Student ===
    Student s1; // Mặc định (gọi People())
    Student s2("079123456789", "Tran Thi B", "Ha Noi", "SV001", 2023); // Có tham số

    // === 3. Tạo các đối tượng FIEStudent ===
    FIEStudent f1; // Mặc định (gọi Student() -> People())
    FIEStudent f2("079987654321", "Le Minh C", "Da Nang", "FIE2023001", 2023, 120); // Có tham số

    // === 4. Hiển thị thông tin các đối tượng ===
    cout << "--- Thong tin doi tuong p1 (People - mac dinh) ----" << endl;
    p1.displayInfo();
    cout << endl;

    cout << "--- Thong tin doi tuong p2 (People - co tham so) ----" << endl;
    p2.displayInfo();
    cout << endl;

    cout << "--- Thong tin doi tuong s1 (Student - mac dinh) ----" << endl;
    s1.displayInfo();
    cout << endl;

    cout << "--- Thong tin doi tuong s2 (Student - co tham so) ----" << endl;
    s2.displayInfo();
    cout << endl;

    cout << "--- Thong tin doi tuong f1 (FIEStudent - mac dinh) ----" << endl;
    f1.displayInfo();
    cout << endl;

    cout << "--- Thong tin doi tuong f2 (FIEStudent - co tham so) ----" << endl;
    f2.displayInfo();
    cout << endl;

    return 0;
}