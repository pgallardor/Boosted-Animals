#include <queue>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <vector>
#define INF 1 << 15
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> pii;

pii make_double_pair(int i, int j, int k){
	pair<int, int> c = make_pair(j, k);
	return make_pair(i, c);
}

vector<pii> edges;

bool bellman_ford(int V, int s){
	int cost[1005];
	pii e_actual;
	for(int i = 0; i < 1005; i++)
		cost[i] = INF;

	cost[s] = 0;

	for (int i = 1; i < V; i++){
		for (int j = 0; j < edges.size(); j++){
			e_actual = edges[j];

			if (cost[e_actual.second.second] > cost[e_actual.second.first] + e_actual.first)
				cost[e_actual.second.second] = cost[e_actual.second.first] + e_actual.first;
		}
	}

	for (int i = 0; i < edges.size(); i++){
		e_actual = edges[i];
		if (cost[e_actual.second.second] > cost[e_actual.second.first] + e_actual.first)
			return false;
	}
	return true;
}

int main(){
	int cases;
	scanf("%d", &cases);
	while(cases--){
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < m; i++){
			int v1, v2, p;
			scanf("%d %d %d", &v1, &v2, &p);
			edges.push_back(make_double_pair(p, v1, v2));
		}
		if (bellman_ford(n, 0)) printf("not possible\n");
		else printf("possible\n");

		edges.clear();
	}
	return 0;
}