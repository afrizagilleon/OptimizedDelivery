
#include <iostream>
#include <climits>

using namespace std;

#include "graph.h"

typedef struct {
    Addr_Kota[INT_MAX] visited;
    int totalWaktu;
} kunjungan;

typedef struct{
    Addr_Jalan[INT_MAX] jalur;
    int jumlah;
} tetangga;

typedef struct {
    tempList visited;
    Addr_Kota start;
    Addr_Kota end;
    int totalWaktu;
    int pilihan;
    kunjungan[INT_MAX] daftarKunjungan;
} Dijkstra;


void init_dijkstra(Dijkstra &d, string start, string end) {
    CreateTempList(d.visited)
    Addr_Kota findStart = FindKota(d.G, start);
    Addr_Kota findEnd = FindKota(d.G, end);
    if(findStart == nullptr) {
        cout << "Kota asal tidak ditemukan" << endl;
        return;
    }
    if(findEnd == nullptr) {
        cout << "Kota tujuan tidak ditemukan" << endl;
        return;
    }
    d.start = findStart;
    d.end = findEnd;
}

tetangga getTetangga(Dijkstra &d, Addr_Kota k) {
    Addr_Jalan E = k->FirstJalan;
    tetangga t;
    t.jumlah = 0;
    while(E != nullptr) {
        t.jalur[t.jumlah] = E;
        t.jumlah++;
        E = E->NextJalan;
    }
    return t;
}

void dijkstra_search_jalur(Dijkstra &d){
    tetangga t = getTetangga(d, d.start);
    for (int i = 0; i < t.jumlah; i++)
    {
        
    }
    
}