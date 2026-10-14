#include <iostream>
#include <string>

using namespace std;

const int MAX_NHAN_VIEN = 100;

// Lớp cơ sở Nhân viên
class NhanVien {
protected:
    string maCCCD;
    string soDienThai;
    string diaChiNha;

public:
    NhanVien() : maCCCD(""), soDienThai(""), diaChiNha("") {}
    NhanVien(string cccd, string sdt, string diaChi) 
        : maCCCD(cccd), soDienThai(sdt), diaChiNha(diaChi) {}

    virtual ~NhanVien() {}

    virtual void xuatThongTin() const {
        cout << "[+] CCCD    : " << maCCCD << endl;
        cout << "[+] SDT     : " << soDienThai << endl;
        cout << "[+] Dia Chi : " << diaChiNha << endl;
    }

    virtual double tinhThuNhap() const { return 0.0; }
    virtual int dinhDanhLoai() const { return 0; } // 0: Base, 1: Theo gio, 2: Theo thang

    string getCCCD() const { return maCCCD; }
    string getSDT() const { return soDienThai; }
    string getDiaChi() const { return diaChiNha; }

    void setCCCD(const string& cccd) { maCCCD = cccd; }
    void setSDT(const string& sdt) { soDienThai = sdt; }
    void setDiaChi(const string& diaChi) { diaChiNha = diaChi; }
};

// Lớp Nhân viên làm theo giờ
class NhanVienTheoGio : public NhanVien {
private:
    int gioLamViec;
    double mucLuongGio;

public:
    NhanVienTheoGio() : NhanVien(), gioLamViec(0), mucLuongGio(0.0) {}
    NhanVienTheoGio(string cccd, string sdt, string diaChi, int soGio, double donGia)
        : NhanVien(cccd, sdt, diaChi), gioLamViec(soGio), mucLuongGio(donGia) {}

    double tinhThuNhap() const override {
        return gioLamViec * mucLuongGio;
    }

    void xuatThongTin() const override {
        NhanVien::xuatThongTin();
        cout << "[+] So Gio  : " << gioLamViec << " gio" << endl;
        cout << "[+] Don Gia : " << mucLuongGio << " VND/gio" << endl;
        cout << "[=] Luong   : " << tinhThuNhap() << " VND" << endl;
    }

    int dinhDanhLoai() const override { return 1; }

    int getGioLamViec() const { return gioLamViec; }
    double getMucLuongGio() const { return mucLuongGio; }
    void setGioLamViec(int g) { gioLamViec = g; }
    void setMucLuongGio(double dg) { mucLuongGio = dg; }
};

// Lớp Nhân viên làm theo tháng
class NhanVienTheoThang : public NhanVien {
private:
    double luongCoSo;
    double phuCapNganh;
    double heSoThuongCoDinh;

public:
    NhanVienTheoThang() : NhanVien(), luongCoSo(0.0), phuCapNganh(0.0), heSoThuongCoDinh(0.0) {}
    NhanVienTheoThang(string cccd, string sdt, string diaChi, double lcb, double pc, double hs)
        : NhanVien(cccd, sdt, diaChi), luongCoSo(lcb), phuCapNganh(pc), heSoThuongCoDinh(hs) {}

    double tinhThuNhap() const override {
        return luongCoSo + phuCapNganh + (luongCoSo * heSoThuongCoDinh);
    }

    void xuatThongTin() const override {
        NhanVien::xuatThongTin();
        cout << "[+] Luong Co So : " << luongCoSo << " VND" << endl;
        cout << "[+] Phu Cap     : " << phuCapNganh << " VND" << endl;
        cout << "[+] HS Thuong   : " << heSoThuongCoDinh << endl;
        cout << "[=] Luong       : " << tinhThuNhap() << " VND" << endl;
    }

    int dinhDanhLoai() const override { return 2; }

    double getLuongCoSo() const { return luongCoSo; }
    double getPhuCapNganh() const { return phuCapNganh; }
    double getHeSoThuongCoDinh() const { return heSoThuongCoDinh; }
};

// =========================================================
// STRUCT QUẢN LÝ XỬ LÝ DANH SÁCH (TẠO NÉT KHÁC BIỆT CHUYÊN NGHIỆP)
// =========================================================
struct QuanLyNhanVien {

    static double tinhTongNganSach(NhanVien* ds[], int sl) {
        double tong = 0;
        for (int i = 0; i < sl; ++i) {
            tong += ds[i]->tinhThuNhap();
        }
        return tong;
    }

    static int timIndexCaoNhat(NhanVien* ds[], int sl) {
        if (sl <= 0) return -1;
        int maxIdx = 0;
        for (int i = 1; i < sl; ++i) {
            if (ds[i]->tinhThuNhap() > ds[maxIdx]->tinhThuNhap()) {
                maxIdx = i;
            }
        }
        return maxIdx;
    }

    static int timIndexThapNhat(NhanVien* ds[], int sl) {
        if (sl <= 0) return -1;
        int minIdx = 0;
        for (int i = 1; i < sl; ++i) {
            if (ds[i]->tinhThuNhap() < ds[minIdx]->tinhThuNhap()) {
                minIdx = i;
            }
        }
        return minIdx;
    }

    static void thongKePhanLoai(NhanVien* ds[], int sl, int& soTheoGio, int& soTheoThang) {
        soTheoGio = 0;
        soTheoThang = 0;
        for (int i = 0; i < sl; ++i) {
            if (ds[i]->dinhDanhLoai() == 1) soTheoGio++;
            else if (ds[i]->dinhDanhLoai() == 2) soTheoThang++;
        }
    }

    static void traCuuTheoMucLuong(NhanVien* ds[], int sl, double nguongMoTa) {
        bool timThay = false;
        for (int i = 0; i < sl; ++i) {
            if (ds[i]->tinhThuNhap() > nguongMoTa) {
                ds[i]->xuatThongTin();
                cout << "-------------------------------------------" << endl;
                timThay = true;
            }
        }
        if (!timThay) cout << "-> Khong co nhan vien nao dat muc luong tren." << endl;
    }

    // Sắp xếp giảm dần bằng Thuật toán Insertion Sort (Khác hẳn Bubble/Selection Sort)
    static void sapXepThuNhapGiamDan(NhanVien* ds[], int sl) {
        for (int i = 1; i < sl; ++i) {
            NhanVien* key = ds[i];
            int j = i - 1;
            while (j >= 0 && ds[j]->tinhThuNhap() < key->tinhThuNhap()) {
                ds[j + 1] = ds[j];
                j = j - 1;
            }
            ds[j + 1] = key;
        }
    }
};

// ================= HÀM MAIN =================
int main() {
    // Khởi tạo các nhân viên lẻ
    NhanVien nvGoc("079123456789", "0901234567", "TP. Ho Chi Minh");
    NhanVienTheoGio nvGio1("079876543210", "0908765432", "Ha Noi