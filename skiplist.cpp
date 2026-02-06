class Skiplist {
    public:
        class SkiplistNode {
            public:
                int val;
                SkiplistNode* prev;
                SkiplistNode* next;
                SkiplistNode* up;
                SkiplistNode* bottom;
    
                SkiplistNode(int _val) {
                    this->val = _val;
                    this->prev = nullptr;
                    this->next = nullptr;
                    this->up = nullptr;
                    this->bottom = nullptr;
                }
    
                SkiplistNode(int _val, SkiplistNode* _prev, SkiplistNode* _next, SkiplistNode* _up, SkiplistNode* _bottom) {
                    this->val = _val;
                    this->prev = _prev;
                    this->next = _next;
                    this->up = _up;
                    this->bottom = _bottom;
                }
        };
    
        SkiplistNode* root;
        int curLevel;
        const int inf = INT_MAX; 
    
        Skiplist() {
            srand(time(NULL));
            root = nullptr;
            add(-inf);
        }
    
        bool coinFlip() {
            return rand() % 2;
        }
    
        // Find a node in the lowest layer and node->val <= valTarget
        SkiplistNode* findNode(int valTarget) {
            SkiplistNode* curNode = root;
            while (curNode != nullptr) {
                while (curNode->next != nullptr && curNode->next->val <= valTarget) {
                    curNode = curNode->next;
                }
    
                if (curNode->bottom != nullptr) {
                    curNode = curNode->bottom;
                } else {
                    return curNode;
                }
            }
    
            return curNode;
        }
        
        bool search(int target) {
            if (root == nullptr) return false;
            SkiplistNode* node = findNode(target);
            return node->val == target;
        }
    
        // Insert b after a
        void insert(SkiplistNode* a, SkiplistNode* b) {
            b->next = a->next;
            if (a->next != nullptr) a->next->prev = b;
            b->prev = a;
            a->next = b;
        }
    
        void createNewLevelLayer() {
            SkiplistNode* rootNextLevel = new SkiplistNode(root->val);
            rootNextLevel->bottom = root;
            root->up = rootNextLevel;
            root = rootNextLevel;
        }
        
        void add(int num) {
            if (root == nullptr) {
                root = new SkiplistNode(num);
                curLevel = 1;
                return;
            }
    
            SkiplistNode* nodeInList = findNode(num);
            SkiplistNode* nodeNeedAdd = new SkiplistNode(num);
            insert(nodeInList, nodeNeedAdd);
    
            int iLevel = 1; // Lowest level
    
            // Insert to higher level depend on coinFlip() function
            while (coinFlip()) {
                iLevel++;
                if (iLevel > curLevel) {
                    curLevel++;
                    createNewLevelLayer();
                }
    
                while (nodeInList->up == nullptr) {
                    nodeInList = nodeInList->prev;
                }
    
                nodeInList = nodeInList->up;
    
                SkiplistNode* nodeNeedAddToThisLevel = new SkiplistNode(num);
                nodeNeedAddToThisLevel->bottom = nodeNeedAdd;
                nodeNeedAdd->up = nodeNeedAddToThisLevel;
                nodeNeedAdd = nodeNeedAddToThisLevel;
    
                insert(nodeInList, nodeNeedAdd);
            }
        }
        
        bool erase(int num) {
            SkiplistNode* nodeNeedErase = findNode(num);
            if (nodeNeedErase == nullptr || nodeNeedErase->val != num) return false;
    
            while (1) {
                nodeNeedErase->prev->next = nodeNeedErase->next;
                if (nodeNeedErase->next != nullptr) nodeNeedErase->next->prev = nodeNeedErase->prev;
    
                if (nodeNeedErase->up == nullptr) return true;
    
                nodeNeedErase = nodeNeedErase->up;
                delete nodeNeedErase->bottom;
                nodeNeedErase->bottom = nullptr;
            }
    
            return true;
        }
    };
    
    /**
     * Your Skiplist object will be instantiated and called as such:
     * Skiplist* obj = new Skiplist();
     * bool param_1 = obj->search(target);
     * obj->add(num);
     * bool param_3 = obj->erase(num);
     */