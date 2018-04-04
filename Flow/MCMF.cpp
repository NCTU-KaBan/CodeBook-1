#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define F first
#define S second
typedef long long LL;
typedef pair<LL, LL> pLL;
const int MAXN = 300;
const int MAXM = MAXN * MAXN * 2;
const LL INF = 0x3f3f3f3f3f3f3f3f;
struct Graph{
    struct Node; struct Edge; int V;
    struct Node : vector<Edge*>{
        bool inq; Edge *pa; LL a, d;
        Node(){clear();}
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *u, *v; Edge *rev;
        LL c, f, _c; Edge(){}
        Edge(Node *u, Node *v, LL c, LL _c, Edge *rev) 
            : u(u), v(v), c(c), f(0), _c(_c), rev(rev){};
    }_memE[MAXM], *ptrE;
    Graph(int V) : V(V){
        for (int i = 0 ; i < V ; i++) *(node[i] = _memN + i) = Node();
        ptrE = _memE;
    }
    void addEdge(int u, int v, LL c, LL _c){
        node[u]->PB(new (ptrE++) Edge(node[u], node[v], c, _c, ptrE));
        node[v]->PB(new (ptrE++) Edge(node[v], node[u], 0, -_c, ptrE - 2));
    }
};
typedef Graph::Node Node;
#define qpush(s) q.push(s); s->inq = true
#define qpop(u) q.front(); q.pop(); u->inq = false
struct MCMF{
    Graph *G;
    Node **node, *s, *t;
    MCMF(Graph *G, int _s, int _t) : G(G){
        node = &G->node[0];
        s = node[_s], t = node[_t];
    }
    bool SPFA(){
        for (int i = 0 ; i < G->V ; i++) node[i]->d = INF, node[i]->inq = false;
        queue<Node*> q; qpush(s);
        s->d = 0, s->pa = NULL, s->a = INF;
        while (q.size()){
            Node *u = qpop(u);
            for (auto &e : *u){
                Node *v = e->v;
                if (e->c > e->f && v->d > u->d + e->_c){
                    v->d = u->d + e->_c;
                    v->pa = e; v->a = min(u->a, e->c - e->f);
                    if (!v->inq) qpush(v);
                }
            }
        }
        return t->d != INF;
    }
    pLL maxFlowMinCost(){
        pLL res = MP(0, 0);
        while (SPFA()){
            res.F += t->a;
            res.S += t->d * t->a;
            for (Node *u = t ; u != s ; u = u->pa->u){
                u->pa->f += t->a;
                u->pa->rev->f -= t->a;
            }
        }
        return res;
    }
};
int main(){

}