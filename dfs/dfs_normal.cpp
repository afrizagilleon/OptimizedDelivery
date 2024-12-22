#include <iostream>
#include <climits>
#include "../graph.h"

int DFSNormal(Graph &G,
                   const string &startKota,
                   const string &destinationKota, outputDFS &output)
{
    // tempList untuk menandai kota-kota yang sudah dikunjungi pada jalur saat ini
    tempList visited;
    CreateTempList(visited);

	output.from = startKota;
	output.destination = destinationKota;

    // tempList untuk menyimpan jalur terbaik yang ditemukan
    tempList bestRoute;
    CreateTempList(bestRoute);

    // Tandai kota awal sebagai visited
	// cout << "======= Proses Pencarian =======" << endl;
	// cout << "Kota " << startKota << " adalah kota asal" << endl;
    InsertLast_TempList(visited, AlokasiTempElmt(startKota));

    // Variabel untuk mencatat waktu minimum
    int minWaktu = INT_MAX;

    // Mulai DFS dari kota awal
    DFSNormalHelper(G,
                         startKota,
                         destinationKota,
                         0,          // currentWaktu (mulai dari 0)
                         minWaktu,
                         visited,
                         bestRoute, output);
	// cout << "========= ========= =========" << endl;

    if (minWaktu == INT_MAX) {
        // Tidak ditemukan jalur yang valid
        cout << "Tidak ada jalur alternatif yang tersedia." << endl;
        return -1;
    } else {
        // cout << "Jalur terbaik membutuhkan waktu: " << minWaktu << endl;
		output.waktu += minWaktu;

        // Baca bestRoute untuk menampilkan jalur tercepat
        // cout << "Rute tercepat: ";
        Addr_TempListElmt p = bestRoute.first;
        bool firstPrint = true;
        while (p != nullptr) {
            if (!firstPrint) output.jalur += " -> ";
            output.jalur += p->info;
            firstPrint = false;
            p = p->next;
        }
        cout << endl;
		// cout << "===============================" << endl;

        return minWaktu;
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
 */
void DFSNormalHelper(Graph &G,
                          const string &currentKota,
                          const string &destinationKota,
                          int currentWaktu,
                          int &minWaktu,
                          tempList &L,
                          tempList &bestRoute, outputDFS &output)
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
        bool isVisited = (HasVisited(L, pJalan->Info.kota));

        // Lanjutkan DFS jika jalan tidak diblokir dan kota tujuannya belum dikunjungi
        if (!isVisited) {
            // Tandai kota tujuan jalan ini sebagai 'visited'
            InsertLast_TempList(L, AlokasiTempElmt(pJalan->Info.kota));
            // cout << "Melalui jalan " << pJalan->Info.namaJalan 
            //      << " menuju kota " << pJalan->Info.kota 
            //      << " memakan waktu " << pJalan->Info.waktu << endl;

            // Rekursi dengan menambahkan waktu tempuh sesuai jalan yang dipilih
            DFSNormalHelper(G,
                                 pJalan->Info.kota,
                                 destinationKota,
                                 currentWaktu + pJalan->Info.waktu,
                                 minWaktu,
                                 L,
                                 bestRoute, output);

            // Setelah rekursi, lakukan backtracking (hapus kota terakhir yang dimasukkan)
            DeleteLast_TempList(L);
            // cout << "Kembali ke kota " << FindLastTempList(L) << endl;
        }
		
        pJalan = pJalan->NextJalan; 
    }
}