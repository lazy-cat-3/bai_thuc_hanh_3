#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int suc_chua_toi_da;
    int so_xe_trong_bai;
    phuong_tien**xe;

public:
    bai_xe();
    bai_xe(int ma, char kt);
    bai_xe(const bai_xe& p);
    ~bai_xe();
    bai_xe& operator=(const bai_xe& p);
    void thay_doi_kt(int suc_chua_moi);
    bool them(const phuong_tien& v);
    bool xoa(int vID);
    void liet_ke_loai(string loai, int& dem) const;
    void thong_ke_phi(int& tong_xe, double& tong_phi) const;
};
bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), suc_chua_toi_da(1), so_xe_trong_bai(0){
	xe = new phuong_tien*[suc_chua_toi_da];
	xe[0]= nullptr;
	}
bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe_trong_bai(0){
	suc_chua_toi_da= (kich_thuoc=='S')?1:(kich_thuoc=='M')?2:3;
	xe = new phuong_tien*[suc_chua_toi_da];
	for(int i=0;i<suc_chua_toi_da;i++){
		xe[i]=nullptr;
	}
}
bai_xe::bai_xe(const bai_xe& p){
	ma_bai=p.ma_bai;
	kich_thuoc=p.kich_thuoc;
	suc_chua_toi_da = p.suc_chua_toi_da;
	so_xe_trong_bai=p.so_xe_trong_bai;
	xe = new phuong_tien*[suc_chua_toi_da];
	for(int i=0;i<suc_chua_toi_da;i++){
		if(i<so_xe_trong_bai&& p.xe[i]!=nullptr){
			xe[i]=new phuong_tien(*p.xe[i]);
		}
		else{
			xe[i]=nullptr;
		}
	}
}
bai_xe::~bai_xe(){
	for(int i=0;i<suc_chua_toi_da;i++){
		delete xe[i];
	}
	delete[] xe;
}
bai_xe& bai_xe::operator=(const bai_xe& p){
	if(this==&p) return*this;
	for(int i=0;i<suc_chua_toi_da;i++){
		delete xe[i];
	}
	delete[] xe;
	ma_bai = p.ma_bai;
    kich_thuoc = p.kich_thuoc;
    suc_chua_toi_da = p.suc_chua_toi_da;
    so_xe_trong_bai = p.so_xe_trong_bai;

    xe = new phuong_tien*[suc_chua_toi_da];
    for (int i = 0; i < suc_chua_toi_da; i++) {
        if (i < so_xe_trong_bai && p.xe[i] != nullptr) {
            xe[i] = new phuong_tien(*p.xe[i]);
        } else {
            xe[i] = nullptr;
        }
    }
    return *this;
}
void bai_xe::thay_doi_kt(int suc_chua_moi) {
    if (suc_chua_moi <= 0) suc_chua_moi = 1;
    phuong_tien** mang_moi = new phuong_tien*[suc_chua_moi];
    for (int i = 0; i < suc_chua_moi; i++) {
        if (i < so_xe_trong_bai) {
            mang_moi[i] = xe[i];
        } else {
            mang_moi[i] = nullptr;
        }
    }
    delete[] xe;
    xe = mang_moi;
    suc_chua_toi_da = suc_chua_moi;
}

int bai_xe::lay_ma() const {
    return ma_bai;
}
bool bai_xe::them(const phuong_tien& v) {
    if (so_xe_trong_bai == suc_chua_toi_da) {
        thay_doi_kt(suc_chua_toi_da * 2);
    }
    xe[so_xe_trong_bai] = new phuong_tien(v);
    so_xe_trong_bai++;
    return true;
}
bool bai_xe::xoa(int ma_xe) {
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != nullptr && xe[i]->lay_ma_xe() == ma_xe) {
            delete xe[i];
            for (int j = i; j < so_xe_trong_bai - 1; j++) {
                xe[j] = xe[j + 1];
            }
            xe[so_xe_trong_bai - 1] = nullptr;
            so_xe_trong_bai--;
            return true;
        }
    }
    return false;
}
bool bai_xe::chua(int ma_xe) const {
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != nullptr && xe[i]->lay_ma_xe() == ma_xe) {
            return true;
        }
    }
    return false;
}
void bai_xe::liet_ke_loai(string loai, int& dem) const {
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != NULL && xe[i]->lay_loai_xe() == loai) {
            cout << "  [Bai " << ma_bai << "] ";
            xe[i]->hien_thi();
            dem++;
        }
    }
}
void bai_xe::thong_ke_phi(int& tong_xe, double& tong_phi) const {
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != NULL) {
            tong_xe++;
            tong_phi += xe[i]->tinh_phi();
        }
    }
}
void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe_trong_bai << "/" << suc_chua_toi_da << " xe\n";
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != nullptr) {
            xe[i]->hien_thi();
        }
    }
}
bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;
    for (int i = 0; i < so_xe_trong_bai; i++) {
        if (xe[i] != nullptr && xe[i]->lay_loai_xe() == loai) {
            ++dem;
            tong += xe[i]->tinh_phi();
        }
    }
    return dem > 0;
}

class SystemInterface {
private:
    int suc_chua_bai;
    int so_luong_bai;
    bai_xe**ds_bai;
    int tim_bai(int ma_bai) const;
public:
    he_thong();                        
    ~he_thong();                        
    void resizeSystem(int newCapacity); 
    void runMenu();
};

SystemInterface::SystemInterface(){
	suc_chua_bai=5;
	so_bai_hien_tai=0;
	ds_bai = new bai_xe[suc_chua_bai];
	for(int i=0;i<suc_chua_bai;i++){
		ds_bai[i]= NULL;
	}
}
he_thong::~he_thong() {
    if (ds_bai != NULL) {
        for (int i = 0; i < suc_chua_bai; i++) {
            delete ds_bai[i]; 
        }
        delete[] ds_bai;
        ds_bai = NULL;
    }
}
void he_thong::resizeSystem(int newCapacity) {
    bai_xe** mang_moi = new bai_xe*[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        if (i < so_bai_hien_tai) {
            mang_moi[i] = ds_bai[i];
        } else {
            mang_moi[i] = NULL;
        }
    }
    delete[] ds_bai;
    ds_bai = mang_moi;
    suc_chua_bai = newCapacity;
}
int he_thong::tim_bai(int ma_bai) const {
    for (int i = 0; i < so_bai_hien_tai; i++) {
        if (ds_bai[i] != NULL && ds_bai[i]->lay_ma() == ma_bai) {
            return i;
        }
    }
    return -1;
}
void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        switch(chon){
        	case 1:{
        		int ma; char kt;
            cout << "Ma bai: "; cin >> ma;
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            if (!co1)      { bai1 = bai_xe(ma, kt); co1 = true; }
            else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
            else           { bai3 = bai_xe(ma, kt); co3 = true; }
            cout << "Da tao bai " << ma << "\n";
            break;
        }
        	case 2:{
            int ma, gio, tg; string loai;
            cout << "Ma xe: "; cin >> ma;
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            cout << "Gio vao (0-23): "; cin >> gio;
            cout << "Thoi luong (1-23): "; cin >> tg;
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            if (co1 && !ok) ok = bai1.them(v);
            if (co2 && !ok) ok = bai2.them(v);
            if (co3 && !ok) ok = bai3.them(v);
            if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else    cout << "Tat ca bai da day!\n";
            break;}
        	case 3 {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) {
                if (co2) { bai1 = bai2; if (co3) { bai2 = bai3; co3 = false; } else co2 = false; }
                else co1 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co2 && bai2.lay_ma() == ma) {
                if (co3) { bai2 = bai3; co3 = false; } else co2 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co3 && bai3.lay_ma() == ma) {
                co3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            break;
        }
        	case 4: {
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            bool ok = false;
            if (co1 && !ok) ok = bai1.xoa(ma);
            if (co2 && !ok) ok = bai2.xoa(ma);
            if (co3 && !ok) ok = bai3.xoa(ma);
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }
        	case 5: {
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();
            break;
        }
        	case 6: {
            int ma;
            cout << "Ma bai: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) bai1.hien_thi();
            else if (co2 && bai2.lay_ma() == ma) bai2.hien_thi();
            else if (co3 && bai3.lay_ma() == ma) bai3.hien_thi();
            break;
        }
        	case 7: {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            int dem; double tong;
            if (co1 && bai1.co_loai(loai, dem, tong)) bai1.hien_thi();
            if (co2 && bai2.co_loai(loai, dem, tong)) bai2.hien_thi();
            if (co3 && bai3.co_loai(loai, dem, tong)) bai3.hien_thi();
            break;
        }
        	case 8: {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                int d; double s;
                if (co1) { bai1.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co2) { bai2.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co3) { bai3.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            break;
        }
        case 9: break;
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
