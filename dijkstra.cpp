// Dijkstra (non-negative weights)
// graph[u] = list of (v, w)
vector<long long> dijkstra(int n, vector<vector<pair<int,int>>>& graph, int src) {
    const long long INF = (1LL << 60);
    vector<long long> dist(n, INF);
    dist[src] = 0;

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue; // stale

        for (auto [v, w] : graph[u]) {
            long long nd = d + (long long)w;
            if (nd >= dist[v]) continue;
            dist[v] = nd;
            pq.push({nd, v});
        }
    }
    return dist;
}
