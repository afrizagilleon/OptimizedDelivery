#include <iostream>

#include "graph.h"

using namespace std;

void CreateGraph(Graph &G) {
	G.Start=Null;
}

Addr_Kota AlokasiKota(Infotype_Kota infoKota) {
	Addr_Kota P;

    P=new Elmt_Kota;
    P->Info=infoKota;
    P->FirstJalan=Null;
    P->NextKota=Null;
    return P;
}

Addr_Jalan AlokasiJalan(Infotype_Jalan infoJalan) {
	Addr_Jalan P;

	P=new Elmt_Jalan;
	P->Info=infoJalan;
	P->NextJalan=Null;
    return P;
}

void AddNewKota(Graph &G, Addr_Kota P) {
	Addr_Kota Q;

	if (G.Start==Null){
		G.Start=P;
	}
	else {
		Q=G.Start;
		while (Q->NextKota!=Null) {
			Q=Q->NextKota;
		}
		Q->NextKota=P;
	}
}

Addr_Kota FindKota(Graph G, Infotype_Kota data) {
	Addr_Kota P;

	if (G.Start==Null) {
		return Null;
	}
	else {
		P=G.Start;
		while (P->Info!=data && P->NextKota!=Null) {
			P=P->NextKota;
		}
		if (P->Info==data) {
			return P;
		}
		else {
			return Null;
		}
	}
}

void InsertLast_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan PJalan) {
	Addr_Jalan P;

	if (PKota==Null) {
		cout<<"Kota tidak ditemukan\n";
	}
	else if (PKota->FirstJalan==Null) {
		PKota->FirstJalan=PJalan;
	}
	else {
		P=PKota->FirstJalan;
		while (P->NextJalan!=Null) {
			P=P->NextJalan;
		}
		P->NextJalan=PJalan;
	}
}

void Connecting(Graph &G,Infotype_Kota node1,Infotype_Kota node2, string namaJalan, int waktu) {
	Addr_Jalan E1,E2;
	Addr_Kota P1,P2;

	P1=FindKota(G,node1);
	P2=FindKota(G,node2);
	if (P1!=Null && P2!=Null){
		if(checkConnection(G, P1, P2)) {
			cout << "Kota " << node1 << " dan " << node2 << " sudah terhubung" << endl;
			return;
		}
		E1=AlokasiJalan({node2,namaJalan,waktu});
		InsertLast_Jalan(G,P1,E1);
		E2=AlokasiJalan({node1,namaJalan,waktu});
		InsertLast_Jalan(G,P2,E2);
	}
	else {
		cout<<"Kota asal atau tujuan tidak ditemukan\n";
	}
}

bool checkConnection(Graph G, Addr_Kota node1, Addr_Kota node2) {
	Addr_Jalan E1 = node1->FirstJalan;
	Addr_Jalan E2 = node2->FirstJalan;
	while (E1 != Null && E2 != Null) {
		if (E1->Info.kota == node2->Info && E2->Info.kota == node1->Info) {
			return true;
		}
		E1 = E1->NextJalan;
		E2 = E2->NextJalan;
	}
	return false;
}



Addr_Jalan FindJalanByKota(Graph &G,Addr_Kota PKota,Infotype_Kota data) {
	Addr_Jalan P;

	if (G.Start==Null || PKota==Null){
		return Null;
	}
	else {
		P=PKota->FirstJalan;
		while (P->Info.kota != data && P->NextJalan!=Null){
			P = P->NextJalan;
		}
		if (P->Info.kota==data) {
			return P;
		}
		else {
			return Null;
		}
	}
}

bool IsAJalanExist(Graph G, string namaJalan) {
	Addr_Kota P = G.Start;
	while (P != Null) {
		Addr_Jalan E = P->FirstJalan;
		while (E != Null) {
			if (E->Info.namaJalan == namaJalan) {
				return true;
			}
			E = E->NextJalan;
		}
		P = P->NextKota;
	}
	return false;
}


void DeleteFirst_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan &P) {
	if (G.Start==Null) {
		cout<<"Empty\n";
	}
	else {
		P = PKota->FirstJalan;
		PKota->FirstJalan=P->NextJalan;
		P->NextJalan=Null;
	}
}

void DeleteLast_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan &P) {
	Addr_Jalan Q;

	if (G.Start==Null) {
		cout<<"Empty\n";
	}
	else {
		Q=Null;
		P=PKota->FirstJalan;
		while (P->NextJalan!=Null) {
			Q=P;
			P=P->NextJalan;
		}
		Q->NextJalan=Null;
	}
}

void DeleteAfter_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan Prec,Addr_Jalan &P) {
	P=Prec->NextJalan;
	Prec->NextJalan=P->NextJalan;
	P->NextJalan=Null;
}

void Delete_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan PJalan) {
	Addr_Jalan Eout,prec;

	if (PJalan==PKota->FirstJalan) {
		DeleteFirst_Jalan(G,PKota,Eout);
	}
	else if (PJalan->NextJalan==Null){
		DeleteLast_Jalan(G,PKota,Eout);
	}
	else {
		prec=PKota->FirstJalan;
		while (prec->NextJalan!=PJalan) {
			prec=prec->NextJalan;
		}
		DeleteAfter_Jalan(G,PKota,prec,Eout);
	}
}

void Disconnecting(Graph &G,Infotype_Kota node1,Infotype_Kota node2) {
	Addr_Kota N1,N2;
	Addr_Jalan E1,E2,Eout;

	N1=FindKota(G,node1);
	N2=FindKota(G,node2);
	if (N1!=Null && N2!=Null) {
		E1=FindJalanByKota(G,N1,node2);
		E2=FindJalanByKota(G,N2,node1);
		if (E1!=Null && E2!=Null) {
			Delete_Jalan(G,N1,E1);
			Delete_Jalan(G,N2,E2);
		}
		else {
			cout<<"Jalan tidak ditemukan\n";
		}
	}
	else {
		cout<<"Kota tidak ditemukan\n";
	}
}

void DeleteKota(Graph &G, Infotype_Kota data) {
	Addr_Kota P, Prec;

	if (G.Start == Null) {
		cout << "Graf Kosong\n";
	} else {
		P = G.Start;
		if (P->Info == data) {
			while (P->FirstJalan != Null) {
				Disconnecting(G, data, P->FirstJalan->Info.kota);
			}
			G.Start = P->NextKota;
			delete P;
		} else {
			while (P->NextKota != Null && P->NextKota->Info != data) {
				P = P->NextKota;
			}
			if (P->NextKota != Null && P->NextKota->Info == data) {
				Prec = P;
				P = P->NextKota;
				while (P->FirstJalan != Null) {
					Disconnecting(G, data, P->FirstJalan->Info.kota);
				}
				Prec->NextKota = P->NextKota;
				delete P;
			} else {
				cout << "Kota tidak ditemukan\n";
			}
		}
	}
}

void Show(Graph G) {
	Addr_Kota N;
	Addr_Jalan E;

	cout<<"Graph G: \n";
	if (G.Start!=Null) {
		N=G.Start;
		while (N!=Null) {
			cout<<"<<==========================>>"<< endl;
			cout<<"Kota "<<N->Info<<" tetangganya: "<< endl;
			cout<<"=============================="<< endl;
			E=N->FirstJalan;
			while (E!=Null) {
				cout<< "Nama kota: " << E->Info.kota<<endl;
				cout<< "Nama jalan: " << E->Info.namaJalan<<endl;
				cout<< "Bobot : " << E->Info.waktu<<endl;
				E=E->NextJalan;
			}
			cout<<"<<==========================>>"<< endl;
			cout<<"\n";
			N=N->NextKota;
		}
	}
	else {
		cout<<"Graf Kosong\n";
	}
}



// SLL temporary

void CreateTempList(tempList &L){
    L.first = Null;
}

Addr_TempListElmt AlokasiTempElmt(Infotype_TempList x){
	Addr_TempListElmt p = new tempListElmt;
	p->info = x;
	p->next = Null;
	return p;
}

void InsertLast_TempList(tempList &L, Addr_TempListElmt P){
	if (L.first == Null){
		L.first = P;
	}
	else {
		Addr_TempListElmt last = L.first;
		while (last->next != Null){
			last = last->next;
		}
		last->next = P;
	}
}


void Dijkstra(Graph &G, tempList &L, string currentKota, string destinationKota, int &totalWaktu) {
    InsertLast_TempList(L, AlokasiTempElmt(currentKota));

	if(totalWaktu != 0){
	    cout << " menuju Kota " << currentKota << endl;
	}else{
		cout << "Kota " << currentKota << " adalah kota asal" << endl;
	}
    
	if (currentKota == destinationKota) {
        cout << "Kota " << currentKota << " adalah tujuan akhir" << endl;
		cout << "Total waktu tersingkat yang diperlukan: " << totalWaktu << endl;
        return;
    }
	

    Addr_Kota P = FindKota(G, currentKota);
    Addr_Jalan shortest = FindShortestNeighbour(G, P, L);
    if (shortest != nullptr) {
		cout << "Melalui jalan " << shortest->Info.namaJalan << " memakan waktu " << shortest->Info.waktu ;
        Dijkstra(G, L, shortest->Info.kota, destinationKota, totalWaktu += shortest->Info.waktu); 
    } else {
        cout << "Tidak ada jalur yang bisa dilewati dari kota " << currentKota << endl;
    }
}

/**
 * Salin isi tempList sumber (source) ke dalam tujuan (dest).
 * Sesuaikan implementasinya dengan struktur tempList Anda.
 */
void CopyTempList(const tempList &source, tempList &dest) {
    // Pastikan dest dikosongkan terlebih dahulu.
    CreateTempList(dest);

    Addr_TempListElmt p = source.first;
    while (p != nullptr) {
        InsertLast_TempList(dest, AlokasiTempElmt(p->info)); 
        p = p->next;
    }
}

/**
 * Fungsi rekursif DFS untuk mencari jalur tercepat dan mencatat rutenya.
 * - G: Graph yang menyimpan data kota dan jalan.
 * - currentKota: Kota yang sedang dikunjungi.
 * - destinationKota: Kota tujuan akhir.
 * - currentWaktu: Total waktu tempuh saat ini pada jalur yang sedang dieksplorasi.
 * - minWaktu: Variabel yang menyimpan waktu tempuh minimal dari semua rute yang valid.
 * - L: tempList untuk menandai jalur saat ini (kota-kota yang sudah dilewati).
 * - bestRoute: tempList untuk menyimpan jalur tercepat yang ditemukan sejauh ini.
 * - namaJalanTerblokir: Nama jalan yang tidak boleh dilewati.
 */
void DFSAlternativeHelper(Graph &G,
                          const string &currentKota,
                          const string &destinationKota,
                          int currentWaktu,
                          int &minWaktu,
                          tempList &L,
                          tempList &bestRoute,
                          const tempList &namaJalanTerblokir)
{
    // Jika kota saat ini sama dengan tujuan, cek apakah waktu tempuhnya lebih baik
    if (currentKota == destinationKota) {
        if (currentWaktu < minWaktu) {
            minWaktu = currentWaktu;
            // Salin jalur saat ini (L) menjadi jalur terbaik (bestRoute)
            CopyTempList(L, bestRoute);
        }
        return;
    }

    // Cari node kota saat ini
    Addr_Kota P = FindKota(G, currentKota);
    if (P == nullptr) {
        return;
    }

    // Telusuri semua jalan (edges) yang keluar dari kota saat ini
    Addr_Jalan pJalan = P->FirstJalan;
    while (pJalan != nullptr) {
        bool isBlocked = (IsAJalanBlocked(namaJalanTerblokir, pJalan->Info.namaJalan));
        bool isVisited = (HasVisited(L, pJalan->Info.kota));

        // Lanjutkan DFS jika jalan tidak diblokir dan kota tujuannya belum dikunjungi
        if (!isBlocked && !isVisited) {
            // Tandai kota tujuan jalan ini sebagai 'visited'
            InsertLast_TempList(L, AlokasiTempElmt(pJalan->Info.kota));
            cout << "Melalui jalan " << pJalan->Info.namaJalan 
                 << " menuju kota " << pJalan->Info.kota 
                 << " memakan waktu " << pJalan->Info.waktu << endl;

            // Rekursi dengan menambahkan waktu tempuh sesuai jalan yang dipilih
            DFSAlternativeHelper(G,
                                 pJalan->Info.kota,
                                 destinationKota,
                                 currentWaktu + pJalan->Info.waktu,
                                 minWaktu,
                                 L,
                                 bestRoute,
                                 namaJalanTerblokir);

            // Setelah rekursi, lakukan backtracking (hapus kota terakhir yang dimasukkan)
            DeleteLast_TempList(L);
            cout << "Kembali ke kota " << FindLastTempList(L) << endl;
        }
		
        pJalan = pJalan->NextJalan; 
    }
}

/**
 * Fungsi utama untuk memanggil DFSAlternativeHelper, menyiapkan minWaktu,
 * membuat tempList visited, dan menampilkan hasil.
 * - namaJalanTerblokir: Jalur yang tidak boleh dilewati
 */
int DFSAlternative(Graph &G,
                   const string &startKota,
                   const string &destinationKota,
                   const tempList &namaJalanTerblokir)
{
    // tempList untuk menandai kota-kota yang sudah dikunjungi pada jalur saat ini
    tempList visited;
    CreateTempList(visited);

    // tempList untuk menyimpan jalur terbaik yang ditemukan
    tempList bestRoute;
    CreateTempList(bestRoute);

    // Tandai kota awal sebagai visited
	cout << "======= Proses Pencarian =======" << endl;
	cout << "Kota " << startKota << " adalah kota asal" << endl;
    InsertLast_TempList(visited, AlokasiTempElmt(startKota));

    // Variabel untuk mencatat waktu minimum
    int minWaktu = INT_MAX;

    // Mulai DFS dari kota awal
    DFSAlternativeHelper(G,
                         startKota,
                         destinationKota,
                         0,          // currentWaktu (mulai dari 0)
                         minWaktu,
                         visited,
                         bestRoute,
                         namaJalanTerblokir);
	cout << "========= ========= =========" << endl;

    if (minWaktu == INT_MAX) {
        // Tidak ditemukan jalur yang valid
        cout << "Tidak ada jalur alternatif yang tersedia." << endl;
        return -1;
    } else {
        cout << "Jalur alternatif terbaik membutuhkan waktu: " << minWaktu << endl;

        // Baca bestRoute untuk menampilkan jalur tercepat
        cout << "Rute tercepat: ";
        Addr_TempListElmt p = bestRoute.first;
        bool firstPrint = true;
        while (p != nullptr) {
            if (!firstPrint) cout << " -> ";
            cout << p->info;
            firstPrint = false;
            p = p->next;
        }
        cout << endl;
		cout << "===============================" << endl;

        return minWaktu;
    }
}

void ShowTempList(tempList L){
	Addr_TempListElmt P = L.first;
	while(P != Null){
		cout << P->info << " ";
		P = P->next;
	}
	cout << endl;
}

void DeleteLast_TempList(tempList &L) {
	Addr_TempListElmt P = L.first;
	if (P == nullptr) {
		return;
	}

	if (P->next == nullptr) {
		delete P;
		L.first = nullptr;
		return;
	}

	while (P->next->next != nullptr) {
		P = P->next;
	}

	delete P->next;
	P->next = nullptr;
}





Addr_Jalan FindShortestNeighbour(Graph G, Addr_Kota P, tempList L) {
    Addr_Jalan E = P->FirstJalan;
    Addr_Jalan shortest = nullptr;
    while (E != nullptr) {
        if (!HasVisited(L, E->Info.kota)) {
            if (shortest == nullptr || E->Info.waktu < shortest->Info.waktu) {
                shortest = E;
            }
        }
        E = E->NextJalan;
    }
    return shortest;
}

bool HasVisited(tempList L, string kota) {
    Addr_TempListElmt P = L.first;
    while (P != nullptr) {
        if (P->info == kota) {
            return true;
        }
        P = P->next;
    }
    return false;
}

bool IsAJalanBlocked(tempList L, string jalan) {
    Addr_TempListElmt P = L.first;
    while (P != nullptr) {
        if (P->info == jalan) {
            return true;
        }
        P = P->next;
    }
    return false;
}



string FindLastTempList(tempList L){
	Addr_TempListElmt P = L.first;
	while(P->next != Null){
		P = P->next;
	}
	return P->info;
}

// debug function

void printTempList(tempList L){
	Addr_TempListElmt P = L.first;
	while(P != Null){
		cout << P->info << " ";
		P = P->next;
	}
	cout << endl;
}