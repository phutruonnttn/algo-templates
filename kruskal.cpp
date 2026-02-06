class Solution {
    public:
        int minCostConnectPoints(vector<vector<int>>& points) {
            int n = points.size();
            typedef pair<int, pair<int, int>> triple;
            vector<triple> adj;
            vector<int> parent(n, -1);
            vector<int> rank(n, 0);
    
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    int dis = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
    
                    adj.push_back(triple(dis, pair<int, int>(i, j)));
                }
            }
    
            sort(adj.begin(), adj.end());
    
            int ans = 0, countAdj = 0;
            for (int i = 0; i < adj.size(); i++) {
                int cost = adj[i].first;
                int u = adj[i].second.first;
                int v = adj[i].second.second;
    
                int pu = find(u, parent), pv = find(v, parent);
                if (pu != pv) {
                    ans += cost;
                    myUnion(pu, pv, parent, rank);
                    countAdj++;
                    if (countAdj == n - 1) {
                        return ans;
                    }
                }
            }
    
            return ans;
        }
    
        int find(int i, vector<int>& parent) {
            int root = i;
            while (parent[root] != -1) {
                root = parent[root];
            }
    
            while (i != root) {
                int tmp = parent[i];
                parent[i] = root;
                i = tmp;
            }
    
            return root;
        }
    
        void myUnion(int u, int v, vector<int>& parent, vector<int>& rank) {
            if (rank[u] < rank[v]) {
                parent[u] = v;
            } else if (rank[u] > rank[v]) {
                parent[v] = u;
            } else {
                parent[u] = v;
                rank[v]++;
            }
        }
    };