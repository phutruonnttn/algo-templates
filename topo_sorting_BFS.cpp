class Solution {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<int> adj[numCourses];
            vector<int> degree(numCourses, 0);
            vector<bool> mark(numCourses, false);
            vector<int> ans;
            deque<int> myDeque;
    
            for (int i = 0; i < prerequisites.size(); i++) {
                adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
                degree[prerequisites[i][0]]++;
            }
    
            for (int i = 0; i < degree.size(); i++) {
                if (degree[i] == 0) {
                    myDeque.push_back(i);
                }
            }
    
            while (!myDeque.empty()) {
                int j = myDeque.front();
                myDeque.pop_front();
                ans.push_back(j);
                mark[j] = true;
    
                for (int k = 0; k < adj[j].size(); k++) {
                    int v = adj[j][k];
                    
                    if (!mark[v]) {
                        degree[v]--;
                       
                        if (degree[v] == 0) {
                            myDeque.push_back(v);
                        }
                    } 
                }
            }
    
            return ans.size() == numCourses ? ans : vector<int>();
        }
    };