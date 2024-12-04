#include <iostream>


#include "graph.h"

using namespace std;

void CreateGraph(Graph &G) {
	G.Start=Null;
}

Addr_Node AlokasiNode(Infotype_Node infoNode) {
	Addr_Node P;

    P=new Elmt_Node;
    P->Info=infoNode;
    P->FirstEdge=Null;
    P->NextNode=Null;
    return P;
}

Addr_Edge AlokasiEdge(Infotype_Edge infoEdge) {
	Addr_Edge P;

	P=new Elmt_Edge;
	P->Info=infoEdge;
	P->NextEdge=Null;
    return P;
}

void AddNewNode(Graph &G, Addr_Node P) {
	Addr_Node Q;

	if (G.Start==Null){
		G.Start=P;
	}
	else {
		Q=G.Start;
		while (Q->NextNode!=Null) {
			Q=Q->NextNode;
		}
		Q->NextNode=P;
	}
}

Addr_Node FindNode(Graph G, Infotype_Node data) {
	Addr_Node P;

	if (G.Start==Null) {
		return Null;
	}
	else {
		P=G.Start;
		while (P->Info!=data && P->NextNode!=Null) {
			P=P->NextNode;
		}
		if (P->Info==data) {
			return P;
		}
		else {
			return Null;
		}
	}
}

void InsertLast_Edge(Graph &G,Addr_Node PNode,Addr_Edge PEdge) {
	Addr_Edge P;

	if (PNode==Null) {
		cout<<"Node tidak ditemukan\n";
	}
	else if (PNode->FirstEdge==Null) {
		PNode->FirstEdge=PEdge;
	}
	else {
		P=PNode->FirstEdge;
		while (P->NextEdge!=Null) {
			P=P->NextEdge;
		}
		P->NextEdge=PEdge;
	}
}

void Connecting(Graph &G,Infotype_Node node1,Infotype_Node node2) {
	Addr_Edge E1,E2;
	Addr_Node P1,P2;

	P1=FindNode(G,node1);
	P2=FindNode(G,node2);
	if (P1!=Null && P2!=Null){
		E1=AlokasiEdge(node2);
		InsertLast_Edge(G,P1,E1);
		E2=AlokasiEdge(node1);
		InsertLast_Edge(G,P2,E2);
	}
	else {
		cout<<"Node tidak ditemukan\n";
	}
}

Addr_Edge FindEdge(Graph &G,Addr_Node PNode,Infotype_Node data) {
	Addr_Edge P;

	if (G.Start==Null || PNode==Null){
		return Null;
	}
	else {
		P=PNode->FirstEdge;
		while (P->Info!=data && P->NextEdge!=Null){
			P=P->NextEdge;
		}
		if (P->Info==data) {
			return P;
		}
		else {
			return Null;
		}
	}
}

void DeleteFirst_Edge(Graph &G,Addr_Node PNode,Addr_Edge &P) {
	if (G.Start==Null) {
		cout<<"Empty\n";
	}
	else {
		P=PNode->FirstEdge;
		PNode->FirstEdge=P->NextEdge;
		P->NextEdge=Null;
	}
}

void DeleteLast_Edge(Graph &G,Addr_Node PNode,Addr_Edge &P) {
	Addr_Edge Q;

	if (G.Start==Null) {
		cout<<"Empty\n";
	}
	else {
		Q=Null;
		P=PNode->FirstEdge;
		while (P->NextEdge!=Null) {
			Q=P;
			P=P->NextEdge;
		}
		Q->NextEdge=Null;
	}
}

void DeleteAfter_Edge(Graph &G,Addr_Node PNode,Addr_Edge Prec,Addr_Edge &P) {
	P=Prec->NextEdge;
	Prec->NextEdge=P->NextEdge;
	P->NextEdge=Null;
}

void Delete_Edge(Graph &G,Addr_Node PNode,Addr_Edge PEdge) {
	Addr_Edge Eout,prec;

	if (PEdge==PNode->FirstEdge) {
		DeleteFirst_Edge(G,PNode,Eout);
	}
	else if (PEdge->NextEdge==Null){
		DeleteLast_Edge(G,PNode,Eout);
	}
	else {
		prec=PNode->FirstEdge;
		while (prec->NextEdge!=PEdge) {
			prec=prec->NextEdge;
		}
		DeleteAfter_Edge(G,PNode,prec,Eout);
	}
}

void Disconnecting(Graph &G,Infotype_Node node1,Infotype_Node node2) {
	Addr_Node N1,N2;
	Addr_Edge E1,E2,Eout;

	N1=FindNode(G,node1);
	N2=FindNode(G,node2);
	if (N1!=Null && N2!=Null) {
		E1=FindEdge(G,N1,node2);
		E2=FindEdge(G,N2,node1);
		if (E1!=Null && E2!=Null) {
			Delete_Edge(G,N1,E1);
			Delete_Edge(G,N2,E2);
		}
		else {
			cout<<"Edge tidak ditemukan\n";
		}
	}
	else {
		cout<<"Node tidak ditemukan\n";
	}
}

void Show(Graph G) {
	Addr_Node N;
	Addr_Edge E;

	cout<<"Graph G: \n";
	if (G.Start!=Null) {
		N=G.Start;
		while (N!=Null) {
			cout<<"Node "<<N->Info<<" tetangganya: ";
			E=N->FirstEdge;
			while (E!=Null) {
				cout<< E->Info<<" ";
				E=E->NextEdge;
			}
			cout<<"\n";
			N=N->NextNode;
		}
	}
	else {
		cout<<"Graf Kosong\n";
	}
}



