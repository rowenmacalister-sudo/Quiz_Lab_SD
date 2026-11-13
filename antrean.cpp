#include <iostream>
#include <string>
using namespace std;


struct NodeQ {
    string nama;
    NodeQ* next;
};
NodeQ* depan = NULL;
NodeQ* belakang = NULL;

void enqueue() {
    NodeQ* baru = new NodeQ;
    cout << "Nama mahasiswa: "; 
    cin >> baru -> nama;
    baru->next = NULL;
    if (depan == NULL) 
        depan = belakang = baru;
    else { 
        belakang->next = baru;
        belakang = baru; 
    }
    cout << "Masuk antrean\n";
}

void dequeue() {
    if(depan == NULL){ 
        cout << "Antrean kosong\n"; 
        return; 
    }
    NodeQ* hapus = depan;
    cout << hapus->nama << " dilayani\n";
    depan = depan->next;
    if(depan == NULL) 
        belakang = NULL;
    delete hapus;
}

void tampilAntrean() {
    if (depan == NULL) { 
        cout << "Antrean kosong\n"; 
        return; 
    }
    cout << "Antrean: ";
    for (NodeQ* p = depan; p != NULL; p = p->next) 
        cout << p->nama << "  \n";
}


struct NodeS {
    string nama;
    int idBuku;
    NodeS* next;
};
NodeS* top = NULL;

void push() {
    NodeS* baru = new NodeS;
    cout << "Nama pengembali: ";
    cin >> baru -> nama;
    cout << "ID buku: ";
    cin >> baru->idBuku;
    baru->next = top;
    top = baru;
    cout << "Pengembalian dicatat\n";
}

void tampilRiwayat() {
    if (top == NULL) {
        cout << "Riwayat kosong\n";
        return; 
    }
    cout << "Riwayat pengembalian (terbaru di atas):\n";
    for (NodeS* p = top; p != NULL; p = p->next)
        cout <<  p->nama << " mengembalikan buku " << p->idBuku << endl;
}


struct NodeT {
    int id;
    NodeT* kiri;
    NodeT* kanan;
};
NodeT* root = NULL;

NodeT* insertBST(NodeT* node, int id) {
    if (node == NULL) {
        NodeT* baru = new NodeT;
        baru->id = id;
        baru->kiri = baru->kanan = NULL;
        return baru;
    }
    if (id < node->id) 
        node->kiri = insertBST(node->kiri, id);
    else if (id > node->id) 
        node->kanan = insertBST(node->kanan, id);
    else 
        cout << "ID sudah ada\n";
    return node;
}

bool cariBST(NodeT* node, int id) {
    if (node == NULL) 
        return false;
    if (id == node->id) 
        return true;
    if (id < node->id) 
        return cariBST(node->kiri, id);
    return cariBST(node->kanan, id);
}

void preOrder(NodeT* n){ 
    if(n){
        cout << n->id << " "; 
        preOrder(n->kiri);
        preOrder(n->kanan); 
    }
}

void inOrder(NodeT* n){ 
    if(n){
        inOrder(n->kiri);
        cout << n->id << " ";
        inOrder(n->kanan);
    }
}

void postOrder(NodeT* n){
    if(n){
        postOrder(n->kiri);
        postOrder(n->kanan);
        cout << n->id << " ";
    }
}

int main() {
    int pilih, id;
    do {cout << "1. Tambah ID buku\n";
        cout << "2. Cari ID buku\n";
        cout << "3. Tampilkan traversal BST\n";
        cout << "4. Tambah antrean peminjam\n";
        cout << "5. Layani antrean\n";
        cout << "6. Tampilkan antrean\n";
        cout << "7. Kembalikan buku\n";
        cout << "8. Tampilkan riwayat pengembalian\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pilih;

        if (pilih == 1) {
            cout << "ID buku: "; 
            cin >> id;
            root = insertBST(root, id);
        } else if (pilih == 2) {
            cout << "ID buku: "; 
            cin >> id;
            if (cariBST(root, id)) 
                cout << "Buku ditemukan\n";
            else 
                cout << "Buku tidak ditemukan\n";
        } else if (pilih == 3) {
            cout << "Pre-Order : "; 
            preOrder(root); cout << endl;
            cout << "In-Order  : "; 
            inOrder(root); cout << endl;
            cout << "Post-Order: "; 
            postOrder(root); cout << endl;
        } else if (pilih == 4) 
            enqueue();
        else if (pilih == 5) 
            dequeue();
        else if (pilih == 6) 
            tampilAntrean();
        else if (pilih == 7) 
            push();
        else if (pilih == 8) 
            tampilRiwayat();
    } while (pilih != 0);
    return 0;
}