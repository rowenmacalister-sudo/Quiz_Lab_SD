#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};

struct Entri {
    int nilai;
    Mahasiswa* pemilik;
};

void tambahMahasiswa(Mahasiswa*& head, vector<Entri>& arr,
                     string nim, string nama, int nilai) {
    Mahasiswa* baru = new Mahasiswa{nim, nama, nilai, nullptr};

    if (head == nullptr) {
        head = baru;
    } else {
        Mahasiswa* bantu = head;
        while (bantu->next != nullptr) bantu = bantu->next;
        bantu->next = baru;
    }

    arr.push_back({nilai, baru});
}

void tampilkanList(Mahasiswa* head) {
    cout << "\n=== Data Mahasiswa ===\n";
    for (Mahasiswa* p = head; p != nullptr; p = p->next)
        cout << p->nim << " | " << p->nama << " | " << p->nilai << endl;
}

void tampilkanArray(const vector<Entri>& arr) {
    cout << "\n=== Nilai Terurut ===\n";
    for (const Entri& e : arr)
        cout << e.nilai << " (" << e.pemilik->nama << ")" << endl;
}

void insertionSort(vector<Entri>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        Entri key = a[i];
        int j = i - 1; 
        while (j >= 0 && a[j].nilai > key.nilai) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

Mahasiswa* cariNIM(Mahasiswa* head, string nim) {
    for (Mahasiswa* p = head; p != nullptr; p = p->next)
        if (p->nim == nim) return p;
    return nullptr;
}

int binarySearch(const vector<Entri>& a, int target) {
    int kiri = 0, kanan = (int)a.size() - 1;
    while (kiri <= kanan) {
        int mid = (kiri + kanan) / 2;
        if (a[mid].nilai == target) return mid;
        else if (a[mid].nilai < target) kiri = mid + 1;
        else kanan = mid - 1;
    }
    return -1;
}

int main() {
    Mahasiswa* head = nullptr;
    vector<Entri> arr;
    bool sudahUrut = false;

    tambahMahasiswa(head, arr, "001", "Budi", 85);
    tambahMahasiswa(head, arr, "002", "Tono", 70);
    tambahMahasiswa(head, arr, "003", "Sari", 92);

    int pilih;
    do {
        cout << "\n1. Tambah mahasiswa\n2. Tampilkan data\n"
             << "3. Urutkan nilai\n4. Cari NIM\n5. Cari nilai\n0. Keluar\nPilih: ";
        cin >> pilih;

        if (pilih == 1) {
            string nim, nama;
            int nilai;
            cout << "NIM: ";
            cin >> nim;
            cout << "Nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Nilai: ";
            cin >> nilai;
            tambahMahasiswa(head, arr, nim, nama, nilai);
            sudahUrut = false;
        }
        else if (pilih == 2) {
            tampilkanList(head);
            tampilkanArray(arr);
        }
        else if (pilih == 3) {
            insertionSort(arr);
            sudahUrut = true;
            tampilkanArray(arr);
        }
        else if (pilih == 4) {
            string nim;
            cout << "Cari NIM: ";
            cin >> nim;
            Mahasiswa* hasil = cariNIM(head, nim);
            if (hasil) cout << hasil->nim << endl << hasil->nama << endl << hasil->nilai << endl;
            else cout << "NIM tidak ditemukan\n";
        }
        else if (pilih == 5) {
            if (!sudahUrut) {
                cout << "Urutkan dulu (menu 3)" << endl;
            } else {
                int target;
                cout << "Cari nilai: ";
                cin >> target;
                int idx = binarySearch(arr, target);
                if (idx != -1) cout << "Ketemu di index " << idx << ", milik " << arr[idx].pemilik->nama << endl;
                else cout << "Nilai tidak ditemukan lohhh\n";
            }
        }
    } while (pilih != 0);

    while (head) {
        Mahasiswa* hapus = head;
        head = head->next;
        delete hapus;
    }

    return 0;
}
