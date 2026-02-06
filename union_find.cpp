class Solution {
    public:
        int numSimilarGroups(vector<string>& strs) {
            int n = strs.size(), ans = n;
            vector<int> parent(n, -1);
            vector<int> height(n, 0);
    
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j && isSimilar(i, j, strs)) {
                        int parentI = find(i, parent), parentJ = find(j, parent);
    
                        if (parentI != parentJ) {
                            ans--;
                            myUnion(parentI, parentJ, parent, height);
                        }
                    }
                }
            }
    
            return ans;
        }
    
        bool isSimilar(int i, int j, vector<string>& strs) {
            int count = 0;
            vector<int> difPos;
            for (int k = 0; k < strs[i].size(); k++) {
                if (strs[i][k] != strs[j][k]) {
                    count++;
                    if (count > 2) {
                        return false;
                    }
                    difPos.push_back(k);
                }
            }
    
            return count == 0 || (strs[i][difPos[0]] == strs[j][difPos[1]] && strs[j][difPos[0]] == strs[i][difPos[1]]);
        }
    
        int find(int i, vector<int>& parent) {
            int cur = i;
            while (parent[cur] != -1) {
                cur = parent[cur];
            }
    
            while (i != cur) {
                int tmp = parent[i];
                parent[i] = cur;
                i = tmp;
            }
    
            return cur;
        }
    
        void myUnion(int i, int j, vector<int>& parent, vector<int>& height) {
            if (height[i] < height[j]) {
                parent[i] = j;
            } else if (height[i] > height[j]) {
                parent[j] = i;
            } else {
                parent[j] = i;
                height[i]++;
            }
        }
    };