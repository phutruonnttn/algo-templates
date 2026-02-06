class NumArray {
    public:
        class SegmentTree{
            public:
                vector<int> tree;
    
                SegmentTree(vector<int>& nums) {
                    int n = nums.size();
                    tree.resize(4 * n, 0);
                    buildTree(0, 0, n - 1, nums);
                }
    
                void buildTree(int i, int left, int right, vector<int>& nums) {
                    if (left == right) {
                        tree[i] = nums[left];
                        return;
                    }
    
                    int mid = (left + right) / 2;
                    buildTree(2 * i + 1, left, mid, nums);
                    buildTree(2 * i + 2, mid + 1, right, nums);
                    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
                }
    
                void update(int i, int left, int right, int index, int val) {
                    if (left == right) {
                        tree[i] = val;
                        return;
                    }
    
                    int mid = (left + right) / 2;
                    if (mid < index) {
                        update(2 * i + 2, mid + 1, right, index, val);
                    } else {
                        update(2 * i + 1, left, mid, index, val);
                    }
    
                    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
                }
    
                int query(int i, int left, int right, int qLeft, int qRight) {
                    if (left > qRight || right < qLeft) {
                        return 0;
                    }
    
                    if  (qLeft <= left && right <= qRight) {
                        return tree[i];
                    }
    
                    int mid = (left + right) / 2;
                    return query(2 * i + 1, left, mid, qLeft, qRight) + query(2 * i + 2, mid + 1, right, qLeft, qRight);
                }
        };
    
        int n;
        SegmentTree* segmentTree;
    
        NumArray(vector<int>& nums) {
            n = nums.size();
            segmentTree = new SegmentTree(nums);
        }
        
        void update(int index, int val) {
            segmentTree->update(0, 0, n - 1, index, val);
        }
        
        int sumRange(int left, int right) {
            return segmentTree->query(0, 0, n - 1, left, right);
        }
    };
    
    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray* obj = new NumArray(nums);
     * obj->update(index,val);
     * int param_2 = obj->sumRange(left,right);
     */