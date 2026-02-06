class Solution {
    public:
        vector<vector<int>> adj;
        vector<bool> mark;
        vector<bool> cycleDetected;
    
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            adj.resize(numCourses);
            mark.resize(numCourses, false);
            cycleDetected.resize(numCourses, false);
            vector<int> ans;
    
            for (int i = 0; i < prerequisites.size(); i++) {
                adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
            }
    
            for (int i = 0; i < numCourses; i++) {
                if (!mark[i]) {
                    if (!dfs(i, ans)) {
                        return {};
                    }
                }
            }
    
            reverse(ans.begin(), ans.end());
            return ans;
        }
    
        bool dfs(int i, vector<int>& ans) {
            if (cycleDetected[i]) return false;
            if (mark[i]) return true;
    
            cycleDetected[i] = true;
            for (int j = 0; j < adj[i].size(); j++) {
                int v = adj[i][j];
                if (!mark[v]) {
                    if (!dfs(v, ans)) {
                        return false;
                    }
                    
                }
            }
    
            ans.push_back(i);
            cycleDetected[i] = false;
            mark[i] = true;
    
            return true;
        }
    };