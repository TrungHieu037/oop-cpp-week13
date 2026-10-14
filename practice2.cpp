#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string cccd;
    string sdt;
    string address;
public:
    // Constructor không tham số - gán giá trị mặc địn
    Employee() {
        cccd ="";
        sdt ="";
        address = "";
    }
    // Constructor có tham số
    Employee(string c, string p, string a) {
        cccd = c;
        sdt = p;
        address = a;
    }
    // getters
    string getCCCD() const { return cccd; }
    string getSDT() const { return sdt; }
    string getAddress() const { return address; }
    // setters
    void setCCCD(string c) { cccd =c; }
    void setSSDT(string p) { sdt= p;}
    void setAddress(string a) { address = a; }
};

class HourlyEmployee : public Employee {
private:
    int soGioLamViec;
    double donGia;
public:
    // Constructor không tham số
    HourlyEmployee(): Employee() {
        soGioLamViec = 0;
        donGia = 0.0;
    }
    // Constructor có tham số
    HourlyEmployee(string c, string p, string a,
    int soGio, double dg)
    : Employee(c, p, a) {
        soGioLamViec = soGio;
        donGia = dg;
    }
    // getters
    int getSoGioLamViec() const { return soGioLamViec; }
    double getDonGia() const { return donGia; }
    // setters
    void setSoGioLamViec(int g) { soGioLamViec = g; }
    void setDonGia(double dg) { donGia = dg; }
};

class MonthlyEmployee : public Employee {
private:
    double luongCoBan;
    double phuCap;
    double heSoThuong;
public:
// Constructor không tham số
    MonthlyEmployee() : Employee(){
    luongCoBan= 0.0;
    phuCap = 0.0;
    heSoThuong = 0.0;
    }
    // Constructor có tham số
    MonthlyEmployee(string c, string p, string a,
                    double lcb, double pc, double hs)
    // gọi constructor lớp cha
        : Employee(c, p, a) {
        luongCoBan = lcb;
        phuCap = pc;
        heSoThuong = hs;
        }
    // getters
    double getLuongCoBan() const {return luongCoBan; }
    double getPhuCap() const { return phuCap; }
    double getHeSoThuong() const { return heSoThuong; }
    // setters (tương tự)
    void setLuongCoBan(int g) { luongCoBan = g; }
    void setPhuCap(double dg) { phuCap = dg; }
    void setHeSoThuong(double dg) { heSoThuong = dg; }
};

int main() {
    // Tạo đối tương Employee (mặc định)
    Employee e1;
    // Tạo đổi tương HourlyEmployee (có tham số)
    HourlyEmployee h1("079123456789", "0901002003", "Ha Noi", 160, 50000);
    // Tạo đối tương MonthlyEmployee (có tham số)
    MonthlyEmployee m1("079987654321", "0903004005", "Da Nang", 15000000, 2000000, 1.2);
    // Hiển thị thông tin (ví dụ)
    cout << " --- Employee e1 --- " << endl;
    cout << "CCCD: " << e1.getCCCD() << endl;
    cout << "SDT: " << e1.getSDT() << endl;
    cout << "Address: " << e1.getAddress() << endl << endl;
    // (tương tự hiển thị cho h1 và m1)
    return 0;
}