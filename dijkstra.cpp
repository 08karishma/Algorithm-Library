int dijkstra(){
	int vis[n];
	memset(vis, 0, sizeof vis);
	int dis[n];
	for(int i=0; i<n; i++) dis[i]=INF;
	dis[s]=0;
	priority_queue<pair<int,int>> q;
	q.push({0, s});
	while(!q.empty()){
		pair<int,int> p = q.top();
		q.pop();
		int u=p.s;
		if(vis[u]) continue;
		vis[u]=1;
		if(u==d) return -p.f;
		for(int v=0; v<n; v++){
			if(graph[u][v]==INF) continue;
			if(!vis[v] && dis[v] > dis[u]+graph[u][v]){
				dis[v] = dis[u]+graph[u][v];
				q.push({-dis[v], v});
			}
		}
	}
	return dis[d];
}
