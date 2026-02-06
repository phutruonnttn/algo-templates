class Solution {
    public:
        int maximalRectangle(vector<vector<char>>& matrix) {
            int n = matrix.size();
            int m = matrix[0].size();
            int heightOne[m + 3];
            int res = 0;
    
            for (int i = 0; i < m; i++) {
                heightOne[i] = 0;
            }
    
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (matrix[i][j] == '0') {
                        heightOne[j] = 0;
                    } else {
                        heightOne[j]++;
                    }
                }
    
                stack<int> stack1;
                int left[m + 3], right[m + 3];
                // Init left: The column stands to the left of column j, lower than column j, closest to column j
                for (int j = 0; j < m; j++) {
                    while (!stack1.empty() && heightOne[stack1.top()] >= heightOne[j]) {
                        stack1.pop();
                    }
                    if (stack1.empty()) {
                        left[j] = -1;
                    } else {
                        left[j] = stack1.top();
                    }
                    stack1.push(j);
                }
    
                // Init right: The column stands to the right of column j, lower than column j, closest to column j
                stack<int> stack2;
                for (int j = m - 1; j >= 0; j--) {
                    while (!stack2.empty() && heightOne[stack2.top()] >= heightOne[j]) {
                        stack2.pop();
                    }
                    if (stack2.empty()) {
                        right[j] = m;
                    } else {
                        right[j] = stack2.top();
                    }
                    stack2.push(j);
                }
    
                for (int j = 0; j < m; j++) {
                    res = max(res, (right[j] - left[j] - 1) * heightOne[j]);
                }
            }
            
            return res;
        }
    };