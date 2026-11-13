#include <iostream>
#include <string>
using namespace std;

const int UKURAN = 20;

long long nim[UKURAN];
string nama[UKURAN];
int status[UKURAN];   // 0 = kosong, 1 = terisi, 2 = sudah dihapus

int hash1(long long key) {
    return key % 20;
}

int hash2(long long key) {
    return 19 - (key % 19);
}

// mengembalikan indeks data, atau -1 jika tidak ada
int cari(long long key) {
    for (int i = 0; i < UKURAN; i++) {
        int idx = (hash1(key) + i * hash2(key)) % UKURAN;

        if (status[idx] == 0) {
            return -1;
        }
        if (status[idx] == 1 && nim[idx] == key) {
            return idx;
        }
    }
    return -1;
}

void insert(long long key, string nm) {
    if (cari(key) != -1) {
        cout << "NIM " << key << " sudah ada\n";
        return;
    }

    for (int i = 0; i < UKURAN; i++) {
        int idx = (hash1(key) + i * hash2(key)) % UKURAN;

        if (status[idx] != 1) {
            nim[idx] = key;
            nama[idx] = nm;
            status[idx] = 1;

            cout << "Insert " << key << " di indeks " << idx;
            if (i > 0) {
                cout << " (collision " << i << " kali)";
            }
            cout << endl;
            return;
        }
    }
    cout << "Insert " << key << " gagal, tidak ada slot yang dapat dijangkau\n";
}

void search(long long key) {
    int idx = cari(key);

    if (idx == -1) {
        cout << "NIM " << key << " tidak ditemukan\n";
    } else {
        cout << "NIM " << key << " ditemukan di indeks " << idx
             << ", nama: " << nama[idx] << endl;
    }
}

void remove(long long key) {
    int idx = cari(key);

    if (idx == -1) {
        cout << "NIM " << key << " tidak ditemukan\n";
        return;
    }

    status[idx] = 2;
    cout << "NIM " << key << " dihapus dari indeks " << idx << endl;
}

void display() {
    for (int i = 0; i < UKURAN; i++) {
        cout << i << "\t";

        if (status[i] == 1) {
            cout << nim[i] << "\t" << nama[i];
        } else if (status[i] == 2) {
            cout << "(dihapus)";
        } else {
            cout << "-";
        }
        cout << endl;
    }
}

void dataUji() {
    insert(2511001, "Andi");
    insert(2511021, "Budi");
    insert(2511041, "Citra");
    insert(2511002, "Dewi");
    insert(2511022, "Eko");
    insert(2511005, "Fitri");
    insert(2511015, "Gilang");
    insert(2511035, "Hana");
    insert(2511007, "Indra");
    insert(2511010, "Joko");
    insert(2511030, "Kiki");
    insert(2511011, "Lina");
    insert(2411019, "Maya");
    insert(2411003, "Nanda");
    insert(2411018, "Omar");
}

int main() {
    int pilih;
    long long key;
    string nm;

    do {
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "4. Display\n";
        cout << "5. Isi 15 data uji\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            cout << "NIM  : ";
            cin >> key;
            cout << "Nama : ";
            cin.ignore();
            getline(cin, nm);
            insert(key, nm);
        } else if (pilih == 2) {
            cout << "NIM: ";
            cin >> key;
            search(key);
        } else if (pilih == 3) {
            cout << "NIM: ";
            cin >> key;
            remove(key);
        } else if (pilih == 4) {
            display();
        } else if (pilih == 5) {
            dataUji();
        }
    } while (pilih != 0);

    return 0;
}