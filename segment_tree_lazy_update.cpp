class Solution {
public:
    class SegmentTree{
        public:
            vector<int> tree, lazy;

            SegmentTree(int n) {
                tree.resize(4 * n, 0);
                lazy.resize(4 * n, 0);
            }

            void process_pending_node(int i, int left, int right) {
                if (lazy[i] != 0) {
                    tree[i] += lazy[i] * (right - left + 1);
                    if (left < right) {
                        lazy[2 * i + 1] += lazy[i];
                        lazy[2 * i + 2] += lazy[i];
                    }
                    lazy[i] = 0;
                }
            }

            void update(int i, int left, int right, int uLeft, int uRight, int inc) {
                process_pending_node(i, left, right);

                if (right < uLeft || left > uRight) {
                    return;
                }

                if (uLeft <= left && right <= uRight) {
                    lazy[i] += inc;
                    process_pending_node(i, left, right);
                    return;
                }

                int mid = (left + right) / 2;
                update(2 * i + 1,left, mid, uLeft, uRight, inc);
                update(2 * i + 2, mid + 1, right, uLeft, uRight, inc);
                tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
            }

            int query(int i, int left, int right, int qLeft, int qRight) {
                process_pending_node(i, left, right);

                if (right < qLeft || left > qRight) {
                    return 0;
                }

                if (qLeft <= left && right <= qRight) {
                    return tree[i];
                }

                int mid = (left + right) / 2;
                return query(2 * i + 1, left, mid, qLeft, qRight) + query(2 * i + 2, mid + 1, right , qLeft, qRight);
            }
    };

    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) { 
        SegmentTree* segmentTree = new SegmentTree(length);

        for (int i = 0; i < updates.size(); i++) {
            int start = updates[i][0];
            int end = updates[i][1];
            int inc = updates[i][2];

            segmentTree->update(0, 0, length - 1, start, end, inc);
        }

        vector<int> ans(length);
        for (int i = 0; i < length; i++) {
            ans[i] = segmentTree->query(0, 0, length - 1, i, i);
        }

        return ans;
    }
};
