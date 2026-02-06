class Solution {
    public:
        int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
            vector<vector<long>> d(n, vector<long>(n, INT_MAX));
    
            for (int i = 0; i < edges.size(); i++) {
                d[edges[i][0]][edges[i][1]] = edges[i][2];
                d[edges[i][1]][edges[i][0]] = edges[i][2];
            } 
    
            for (int i = 0; i < n; i++) {
                d[i][i] = 0;
            }
    
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (d[i][j] > d[i][k] + d[k][j]) {
                            d[i][j] = d[i][k] + d[k][j];
                        }
                    }
                }
            }
    
            int curMax = INT_MAX, ans;
            for (int i = 0; i < n; i++) {
                int count = 0;
                for (int j = 0; j < n; j++) {
                    if (d[i][j] <= distanceThreshold) {
                        count++;
                    }
                }
                if (curMax >= count) {
                    curMax = count;
                    ans = i;
                }
            }
    
            return ans;
        }
    };