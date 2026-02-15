// 3721. Longest Balanced Subarray II
class Solution {
public:
    class SegmentTree{
        public:
            vector<int> treeMin, treeMax, lazy;

            SegmentTree(int n) {
                treeMin.resize(4 * n, 0);
                treeMax.resize(4 * n, 0);
                lazy.resize(4 * n, 0);
            }

            void process_pending_node(int i, int left, int right) {
                if (lazy[i] != 0) {
                    if (left < right) {
                        apply(2 * i + 1, lazy[i]);
                        apply(2 * i + 2, lazy[i]);
                    }
                    lazy[i] = 0;
                }
            }

            void apply(int i, int inc) {
                treeMin[i] += inc;
                treeMax[i] += inc;
                lazy[i] += inc;
            }

            void update(int i, int left, int right, int uLeft, int uRight, int inc) {
                process_pending_node(i, left, right);

                if (right < uLeft || left > uRight) {
                    return;
                }

                if (uLeft <= left && right <= uRight) {
                    apply(i, inc);
                    process_pending_node(i, left, right);
                    return;
                }

                int mid = (left + right) / 2;
                update(2 * i + 1,left, mid, uLeft, uRight, inc);
                update(2 * i + 2, mid + 1, right, uLeft, uRight, inc);

                treeMin[i] = min(treeMin[2 * i + 1], treeMin[2 * i + 2]);
                treeMax[i] = max(treeMax[2 * i + 1], treeMax[2 * i + 2]);
            }

            int findRightmostZero(int i, int left, int right, int qLeft, int qRight) {
                process_pending_node(i, left, right);

                if (right < qLeft || left > qRight) {
                    return -1;
                }

                if (treeMin[i] > 0 || treeMax[i] < 0) {
                    return -1;
                }

                if (left == right) {
                    return left;
                }

                int mid = (left + right) / 2;
                int res = findRightmostZero(2 * i + 2, mid + 1, right , qLeft, qRight);
                if (res != -1) return res;
                return findRightmostZero(2 * i + 1, left, mid, qLeft, qRight);
            }
    };

    int longestBalanced(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        SegmentTree* segmentTree = new SegmentTree(n);

        unordered_map<int, vector<int>> pos;
        unordered_map<int, int> curIndex;

        for (int i = 0; i < n; ++i) {
            if (!curIndex.count(nums[i])) {
                curIndex[nums[i]] = 0;
                int val = nums[i] % 2 ? 1 : -1;
                segmentTree->update(0, 0, n - 1, i, n - 1, val);
            }
            pos[nums[i]].push_back(i);
        }

        for (int i = 0; i < n; ++i) {
            int posMax = segmentTree->findRightmostZero(0, 0, n - 1, i, n - 1);
            if (posMax != -1) ans = max(ans, posMax - i + 1);

            int val = nums[i] % 2 ? 1 : -1;
            int nextIndex = ++curIndex[nums[i]];

            int nextPos = n;
            if (nextIndex < pos[nums[i]].size()) nextPos = pos[nums[i]][nextIndex];

            if (i <= nextPos - 1) {
                segmentTree->update(0, 0, n - 1, i, nextPos - 1, -val);
            }
        } 

        return ans;
    }
};
