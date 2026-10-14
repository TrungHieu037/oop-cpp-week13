#include <iostream>
#include <string>
#include <vector>

#define MAX 100

using namespace std;

class Employee {
protected:
    string cccd;      // CCCD
    string sdt;       // Số điện thoại
    string address;   // Địa chỉ
public:
    Employee() {
        cccd = "";
        sdt = "";
        address = "";
    }
    Employee(string c, string s, string a) {
        cccd = c;
        sdt = s;
        address = a;
    }

    void displayInfo() const {
        cout << "CCCD: " << cccd << endl;
        cout << "SDT: " << sdt << endl;
        cout << "Address: " << address << endl;
    }

    string getCCCD() const { return cccd; }
    string getSDT() const { return sdt; }
    string getAddress() const { return address; }

    void setCCCD(string c) { cccd = c; }
    void setSDT(string s) { sdt = s; }
    void setAddress(string a) { address = a; }
};

class HourlyEmployee : public Employee {
private:
    int soGioLamViec;   // số giờ làm việc
    double donGia;      // đơn giá (vnd/giờ)
public:
    HourlyEmployee() : Employee() {
        soGioLamViec = 0;
        donGia = 0;
    }
    HourlyEmployee(string c, string s, string a, int soGio, double dg)
        : Employee(c, s, a) {
        soGioLamViec = soGio;
        donGia = dg;
    }

    void displayInfo() const {
        Employee::displayInfo();   // gọi hàm lớp cha
        cout << "So gio lam viec: " << soGioLamViec << endl;
        cout << "Don gia: " << donGia << endl;
        cout << "Luong: " << tinhLuong() << endl;
    }
    double tinhLuong() const { return soGioLamViec * donGia; }

    int getSoGioLamViec() const { return soGioLamViec; }
    double getDonGia() const { return donGia; }
    void setSoGioLamViec(int g) { soGioLamViec = g; }
    void setDonGia(double dg) { donGia = dg; }
};

class MonthlyEmployee : public Employee {
private:
    double luongCoBan;   // lương cơ bản
    double phuCap;       // phụ cấp
    double heSoThuong;   // hệ số thưởng
public:
    MonthlyEmployee() : Employee() {
        luongCoBan = 0;
        phuCap = 0;
        heSoThuong = 0;
    }
    MonthlyEmployee(string c, string s, string a, double lcb, double pc, double hs)
        : Employee(c, s, a) {
        luongCoBan = lcb;
        phuCap = pc;
        heSoThuong = hs;
    }

    void displayInfo() const {
        Employee::displayInfo();   // gọi hàm lớp cha
        cout << "Luong co ban: " << luongCoBan << endl;
        cout << "Phu cap: " << phuCap << endl;
        cout << "He so thuong: " << heSoThuong << endl;
        cout << "Luong: " << tinhLuong() << endl;
    }
    double tinhLuong() const { return luongCoBan + phuCap + luongCoBan * heSoThuong; }

    double getLuongCoBan() const { return luongCoBan; }
    double getPhuCap() const { return phuCap; }
    double getHeSoThuong() const { return heSoThuong; }
    void setLuongCoBan(double lcb) { luongCoBan = lcb; }
    void setPhuCap(double pc) { phuCap = pc; }
    void setHeSoThuong(double hs) { heSoThuong = hs; }
};

// Tính lương theo loại (l = 1: Hourly, l = 2: Monthly)
double luong(Employee* p, int l) {
    if (l == 1) return static_cast<HourlyEmployee*>(p)->tinhLuong();
    return static_cast<MonthlyEmployee*>(p)->tinhLuong();
}

// Hiển thị thông tin theo loại
void hienThi(Employee* p, int l) {
    if (l == 1) static_cast<HourlyEmployee*>(p)->displayInfo();
    else static_cast<MonthlyEmployee*>(p)->displayInfo();
}

double tongQuyLuong(Employee* ds[], int loai[], int n) {
    double tong = 0;
    for (int i = 0; i < n; i++)
        tong += luong(ds[i], loai[i]);
    return tong;
}

int timMax(Employee* ds[], int loai[], int n) {
    int vt = 0;
    for (int i = 1; i < n; i++)
        if (luong(ds[i], loai[i]) > luong(ds[vt], loai[vt])) vt = i;
    return vt;
}

int timMin(Employee* ds[], int loai[], int n) {
    int vt = 0;
    for (int i = 1; i < n; i++)
        if (luong(ds[i], loai[i]) < luong(ds[vt], loai[vt])) vt = i;
    return vt;
}

void demTheoLoai(int loai[], int n, int &demHourly, int &demMonthly) {
    demHourly = 0;
    demMonthly = 0;
    for (int i = 0; i < n; i++) {
        if (loai[i] == 1) demHourly++;
        else demMonthly++;
    }
}

void locLuongLonHon(Employee* ds[], int loai[], int n, double nguong) {
    bool co = false;
    for (int i = 0; i < n; i++) {
        if (luong(ds[i], loai[i]) > nguong) {
            hienThi(ds[i], loai[i]);
            cout << endl;
            co = true;
        }
    }
    if (!co) cout << "Khong co nhan vien nao." << endl;
}

void sapXepGiamDan(Employee* ds[], int loai[], int n) {
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++) {
            if (luong(ds[i], loai[i]) < luong(ds[j], loai[j])) {
                Employee* tamP = ds[i];
                ds[i] = ds[j];
                ds[j] = tamP;

                int tamL = loai[i];
                loai[i] = loai[j];
                loai[j] = tamL;
            }
        }
    }
}

int main() {

    Employee e1("079123456789", "Nguyen Van A", "Ho Chi Minh");
    HourlyEmployee h1("079876543210", "Tran Thi B", "Ha Noi", 160, 50000);
    MonthlyEmployee m1("079987654321", "Le Minh C", "Da Nang", 15000000, 2000000, 1.2);

    cout << "--- Thong tin Employee ---" << endl;
    e1.displayInfo();
    cout << "\n--- Thong tin HourlyEmployee ---" << endl;
    h1.displayInfo();
    cout << "\n--- Thong tin MonthlyEmployee ---" << endl;
    m1.displayInfo();

    HourlyEmployee h2("079111111111", "Pham Van D", "Hue", 100, 60000);
    MonthlyEmployee m2("079222222222", "Do Thi E", "Can Tho", 8000000, 1000000, 0.5);

    Employee* ds[MAX];
    int loai[MAX];   // 1: Hourly, 2: Monthly
    int n = 0;
    ds[n] = &h1; loai[n] = 1; n++;
    ds[n] = &m1; loai[n] = 2; n++;
    ds[n] = &h2; loai[n] = 1; n++;
    ds[n] = &m2; loai[n] = 2; n++;

    cout << "\nTong quy luong: " << tongQuyLuong(ds, loai, n) << endl;

    int vtMax = timMax(ds, loai, n);
    int vtMin = timMin(ds, loai, n);
    cout << "\n--- Nhan vien luong cao nhat ---" << endl;
    hienThi(ds[vtMax], loai[vtMax]);
    cout << "\n--- Nhan vien luong thap nhat ---" << endl;
    hienThi(ds[vtMin], loai[vtMin]);

    int dh, dm;
    demTheoLoai(loai, n, dh, dm);
    cout << "\nSo HourlyEmployee: " << dh << endl;
    cout << "So MonthlyEmployee: " << dm << endl;

    double nguong;
    cout << "\nNhap nguong luong: ";
    cin >> nguong;
    locLuongLonHon(ds, loai, n, nguong);

    sapXepGiamDan(ds, loai, n);
    cout << "\n--- Danh sach sau khi sap xep giam dan ---" << endl;
    for (int i = 0; i < n; i++) {
        hienThi(ds[i], loai[i]);
        cout << endl;
    }
    
    return 0;
}