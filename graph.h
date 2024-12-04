#include <iostream>
#include <string>

using namespace std;

#define Null     		nullptr

//Kamus Global
typedef struct vElmt Elmt_Node;
typedef struct eElmt Elmt_Edge;
typedef Elmt_Node*   Addr_Node;
typedef Elmt_Edge*   Addr_Edge;

typedef char Infotype_Node;
typedef char Infotype_Edge;

typedef struct {
	Addr_Node Start;
} Graph;

struct vElmt {
   Infotype_Node Info;
   Addr_Node     NextNode;
   Addr_Edge     FirstEdge;
};

struct eElmt {
   Infotype_Edge Info;
   Addr_Edge     NextEdge;
};

void CreateGraph(Graph &G);
Addr_Node AlokasiNode(Infotype_Node infoNode);
Addr_Edge AlokasiEdge(Infotype_Edge infoEdge);
void AddNewNode(Graph &G, Addr_Node P);
Addr_Node FindNode(Graph G, Infotype_Node data);
void InsertLast_Edge(Graph &G,Addr_Node PNode,Addr_Edge PEdge);
void Connecting(Graph &G,Infotype_Node node1,Infotype_Node node2);
Addr_Edge FindEdge(Graph &G,Addr_Node PNode,Infotype_Node data);
void DeleteFirst_Edge(Graph &G,Addr_Node PNode,Addr_Edge &P);
void DeleteLast_Edge(Graph &G,Addr_Node PNode,Addr_Edge &P);
void DeleteAfter_Edge(Graph &G,Addr_Node PNode,Addr_Edge Prec,Addr_Edge &P);
void Delete_Edge(Graph &G,Addr_Node PNode,Addr_Edge PEdge);
void Disconnecting(Graph &G,Infotype_Node node1,Infotype_Node node2);
void Show(Graph G);


