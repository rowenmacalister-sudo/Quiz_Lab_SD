#include <iostream>
using namespace std;

const int N = 6;
const int INF = 9999;
char nama[N] = {'A', 'B', 'C', 'D', 'E', 'F'};
int graf[N][N];

void tambahSisi(int a, int b, int bobot) {
    graf[a][b] = bobot;
    graf[b][a] = bobot;
}

void isiGraf() {
    tambahSisi(0, 1, 4);   // A-B
    tambahSisi(0, 2, 2);   // A-C
    tambahSisi(1, 2, 1);   // B-C
    tambahSisi(1, 3, 5);   // B-D
    tambahSisi(1, 4, 3);   
    tambahSisi(2, 3, 8);   
    tambahSisi(2, 4, 6);   
    tambahSisi(3, 4, 2);   
    tambahSisi(3, 5, 4);   
    tambahSisi(4, 5, 3);   
}

void tampilMatriks() {
    cout << "   ";
    for (int i = 0; i < N; i++) {
        cout << nama[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << nama[i] << "  ";
        for (int j = 0; j < N; j++) {
            cout << graf[i][j] << "  ";
        }
        cout << endl;
    }
}


void bfs(int awal) {
    bool visited[N] = {false};
    int antrean[N];
    int depan = 0;
    int belakang = 0;

    visited[awal] = true;
    antrean[belakang++] = awal;

    cout << "BFS: ";
    while (depan < belakang) {
        int u = antrean[depan++];
        cout << nama[u] << " ";

        for (int v = 0; v < N; v++) {
            if (graf[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                antrean[belakang++] = v;
            }
        }
    }
    cout << endl;
}


bool visitedDFS[N];

void dfs(int u) {
    visitedDFS[u] = true;
    cout << nama[u] << " ";

    for (int v = 0; v < N; v++) {
        if (graf[u][v] != 0 && !visitedDFS[v]) {
            dfs(v);
        }
    }
}


void dijkstra(int awal, int tujuan) {
    int jarak[N];
    int sebelum[N];
    bool selesai[N];

    for (int i = 0; i < N; i++) {
        jarak[i] = INF;
        sebelum[i] = -1;
        selesai[i] = false;
    }
    jarak[awal] = 0;

    for (int k = 0; k < N; k++) {
        // cari vertex belum selesai dengan jarak terkecil
        int u = -1;
        for (int i = 0; i < N; i++) {
            if (!selesai[i] && (u == -1 || jarak[i] < jarak[u])) {
                u = i;
            }
        }
        selesai[u] = true;

        for (int v = 0; v < N; v++) {
            if (graf[u][v] != 0 && jarak[u] + graf[u][v] < jarak[v]) {
                jarak[v] = jarak[u] + graf[u][v];
                sebelum[v] = u;
            }
        }
    }

    int rute[N];
    int n = 0;
    for (int v = tujuan; v != -1; v = sebelum[v]) {
        rute[n++] = v;
    }

    cout << "Rute: ";
    for (int i = n - 1; i >= 0; i--) {
        cout << nama[rute[i]];
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << "\nTotal jarak: " << jarak[tujuan] << endl;
}

int pilihVertex(string teks) {
    char c;
    cout << teks;
    cin >> c;

    if (c >= 'a' && c <= 'f') {
        c = c - 32;   // huruf kecil jadi besar
    }
    return c - 'A';
}

int main() {
    isiGraf();
    int pilih;

    do {
        cout << "\n=== Rute Kampus ===\n";
        cout << "1. Tampilkan adjacency matrix\n";
        cout << "2. BFS\n";
        cout << "3. DFS\n";
        cout << "4. Jarak terpendek (Dijkstra)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            tampilMatriks();
        } else if (pilih == 2) {
            bfs(pilihVertex("Vertex awal (A-F): "));
        } else if (pilih == 3) {
            for (int i = 0; i < N; i++) {
                visitedDFS[i] = false;
            }
            cout << "DFS: ";
            dfs(pilihVertex("Vertex awal (A-F): "));
            cout << endl;
        } else if (pilih == 4) {
            int awal = pilihVertex("Vertex awal (A-F): ");
            int tujuan = pilihVertex("Vertex tujuan (A-F): ");
            dijkstra(awal, tujuan);
        }
    } while (pilih != 0);

    return 0;
}