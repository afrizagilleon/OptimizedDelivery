#include <iostream>
#include <string>

using namespace std;

#define Null     		nullptr

typedef struct kotaElmt Elmt_Kota;
typedef struct jalanElmt Elmt_Jalan;
typedef Elmt_Kota*   Addr_Kota;
typedef Elmt_Jalan*   Addr_Jalan;

typedef string Infotype_Kota;
typedef struct {
   string kota;
   string namaJalan;
   int waktu;
} Infotype_Jalan;

typedef struct {
	Addr_Kota Start;
} Graph;

struct kotaElmt {
   Infotype_Kota Info;
   Addr_Kota     NextKota;
   Addr_Jalan     FirstJalan;
};

struct jalanElmt {
   Infotype_Jalan Info;
   Addr_Jalan     NextJalan;
};

// SLL temporary
typedef struct tempListElmt* Addr_TempListElmt;
typedef string Infotype_TempList;

struct tempListElmt {
    Infotype_TempList info;
    Addr_TempListElmt next;
};

struct tempList{
    Addr_TempListElmt first;
};

void CreateTempList(tempList &L);
Addr_TempListElmt AlokasiTempElmt(Infotype_TempList x);
void InsertLast_TempList(tempList &L, Addr_TempListElmt P);



void CreateGraph(Graph &G);
Addr_Kota AlokasiKota(Infotype_Kota infoKota);
Addr_Jalan AlokasiJalan(Infotype_Jalan infoJalan);
void AddNewKota(Graph &G, Addr_Kota P);
Addr_Kota FindKota(Graph G, Infotype_Kota data);
void InsertLast_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan PJalan);
void Connecting(Graph &G,Infotype_Kota node1,Infotype_Kota node2, string namaJalan, int waktu);
Addr_Jalan FindJalan(Graph &G,Addr_Kota PKota,Infotype_Kota data);
void DeleteFirst_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan &P);
void DeleteLast_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan &P);
void DeleteAfter_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan Prec,Addr_Jalan &P);
void Delete_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan PJalan);
void Disconnecting(Graph &G,Infotype_Kota node1,Infotype_Kota node2);
void Show(Graph G);


