#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
#define INF 20000
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, pair<int, int> > pii;

pii make_double_pair(int i, int j, int k){
	pair<int, int> c = make_pair(j, k);
	return make_pair(i, c);
}

int grid[1000][1000], cost[1000][1000];
bool visited[1000][1000];

bool may_visit(int xx, int yy, int acost, int n, int m){
	if (xx >= 0 && yy >= 0 && xx < n && yy < m && !visited[xx][yy] && acost + grid[xx][yy] < cost[xx][yy])
		return true;

	return false;
}

void update_and_push(priority_queue<pii> &q, int acost, int xx, int yy){
	cost[xx][yy] = acost + grid[xx][yy];
	q.push(make_double_pair(-cost[xx][yy], xx, yy));
}

int dijkstra(int n, int m){
	priority_queue<pii> pq;

	cost[0][0] = grid[0][0];
	pq.push(make_double_pair(-cost[0][0], 0, 0));

	while(!pq.empty() && !visited[n-1][m-1]){
		pii front = pq.top(); pq.pop();
		int act_cost = -front.first, x = front.second.first, y = front.second.second;
		visited[x][y] = true;

		if (may_visit(x-1, y, act_cost, n, m))
			update_and_push(pq, act_cost, x-1, y);

		if (may_visit(x+1, y, act_cost, n, m))
			update_and_push(pq, act_cost, x+1, y);

		if (may_visit(x, y-1, act_cost, n, m))
			update_and_push(pq, act_cost, x, y-1);

		if (may_visit(x, y+1, act_cost, n, m))
			update_and_push(pq, act_cost, x, y+1);
	}

	return cost[n-1][m-1];
}

int main(){
	int cases, n, m;
	scanf("%d", &cases);
	
	while(cases--){
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				scanf("%d", &grid[i][j]);
			}
		}

		memset(cost, INF, sizeof(cost));
		memset(visited, false, sizeof(visited));
		printf("%d\n", dijkstra(n, m));
	}
	
	return 0;
}

