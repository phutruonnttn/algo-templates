class Solution {
    public:
        deque<int> queueMin, queueMax;
    
        void enqueueMax(int val) {
            while (!queueMax.empty() && queueMax.front() < val) {
                queueMax.pop_front();
            }
            queueMax.push_front(val);
        }
    
        void enqueueMin(int val) {
            while (!queueMin.empty() && queueMin.front() > val) {
                queueMin.pop_front();
            }
            queueMin.push_front(val);
        }
    
        void dequeueMax(int val) {
            if (queueMax.back() == val) {
                queueMax.pop_back();
            }
        }
    
        void dequeueMin(int val) {
            if (queueMin.back() == val) {
                queueMin.pop_back();
            }
        }
    
        int getMax() {
            return queueMax.back();
        }
    
        int getMin() {
            return queueMin.back();
        }
    
        int longestSubarray(vector<int>& nums, int limit) {
            int left = 0, ans = 1, n = nums.size();
    
            for (int right = 0; right < n; right++) {
                enqueueMax(nums[right]);
                enqueueMin(nums[right]);
                while (left < right && getMax() - getMin() > limit) {
                    dequeueMax(nums[left]);
                    dequeueMin(nums[left]);
                    left++;
                }
    
                ans = max(ans, right - left + 1);
            }
    
            return ans;
        }
    };