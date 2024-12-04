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
		E1=AlokasiJalan({node1,namaJalan,waktu});
		InsertLast_Jalan(G,P1,E1);
		E2=AlokasiJalan({node1,namaJalan,waktu});
		InsertLast_Jalan(G,P2,E2);
	}
	else {
		cout<<"Kota tidak ditemukan\n";
	}
}

Addr_Jalan FindJalan(Graph &G,Addr_Kota PKota,Infotype_Kota data) {
	Addr_Jalan P;

	if (G.Start==Null || PKota==Null){
		return Null;
	}
	else {
		P=PKota->FirstJalan;
		while (P->Info.kota!=data && P->NextJalan!=Null){
			P=P->NextJalan;
		}
		if (P->Info.kota==data) {
			return P;
		}
		else {
			return Null;
		}
	}
}

void DeleteFirst_Jalan(Graph &G,Addr_Kota PKota,Addr_Jalan &P) {
	if (G.Start==Null) {
		cout<<"Empty\n";
	}
	else {
		P=PKota->FirstJalan;
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
		E1=FindJalan(G,N1,node2);
		E2=FindJalan(G,N2,node1);
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

void Show(Graph G) {
	Addr_Kota N;
	Addr_Jalan E;

	cout<<"Graph G: \n";
	if (G.Start!=Null) {
		N=G.Start;
		while (N!=Null) {
			cout<<"Kota "<<N->Info<<" tetangganya: ";
			E=N->FirstJalan;
			while (E!=Null) {
				cout<< "Nama kota: " << E->Info.kota<<endl;
				cout<< "Nama jalan: " << E->Info.namaJalan<<endl;
				cout<< "Bobot : " << E->Info.waktu<<endl;
				E=E->NextJalan;
			}
			cout<<"\n";
			N=N->NextKota;
		}
	}
	else {
		cout<<"Graf Kosong\n";
	}
}



