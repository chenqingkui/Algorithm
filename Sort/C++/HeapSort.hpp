#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_
#include <vector>
#include <iostream>
//完全二叉树构建堆
class HeapSort {
public:
    //树结点
    struct TreeNode{
        int val {0};
        TreeNode* left {nullptr};
        TreeNode* right {nullptr};
        TreeNode* parent {nullptr};
    };
public:
    //全排序
    void sort(std::vector<int>& nums);
    //部分排序，查找最大的k个
    void sort(std::vector<int> &nums,int k);
public:
    //构建完全二叉树
    TreeNode* buildFullTree(std::vector<int>& nums,std::vector<TreeNode*>& treeNodes){
        if(nums.size() == 0){
           return nullptr;
        }
        TreeNode* root = new TreeNode();
        root->val = nums[0];
        //记录结点到数组，便于快速查找最后一个结点
        treeNodes[0] = root;
        //构建左子树
        TreeNode* left = buildTree(nums,root,treeNodes,1,0);
        root->left = left;
        //构建右子树
        TreeNode* right = buildTree(nums,root,treeNodes,1,1);
        root->right = right;
        return root;
    }
private:
    //计算索引(通过树的深度及对应层的结点编号，编号每一层均从0开始)
    int calcNumIndex(int height,int count){
       int index =0;
       //每一层结点数量为2^height
       for(int i = 0;i < height;i++){
           index += pow(2,i);
       }
       //增加上对应层的结点数量
       index += count;
       return index;
    }
    //构建树
    TreeNode* buildTree(std::vector<int>& nums,TreeNode* parent,std::vector<TreeNode*>& treeNodes,int height,int count){
      
       int index = calcNumIndex(height,count);
       //索引超界舍弃
       if(index >= nums.size())
       {
           return nullptr;
       }

       TreeNode* node = new TreeNode();
       node->parent = parent;
       //结点数线为nums对应值
       node->val = nums[index];
       //记录结点信息
       treeNodes[index] = node;
       //结点构建左子树，子树深度增加1，结点号为上一级结点号*2
       node->left = buildTree(nums,node,treeNodes,height+1,2*count);
       
       //结点构建右子树，子树深度增加1，结点号为上一级结点号*2+1
       node->right = buildTree(nums,node,treeNodes,height+1,2*count+1);
       //返回结点
       return node;
    }
    //构建大顶堆，首次构建大顶堆时先构建子树
    void buildRootMaxHeap(TreeNode* root,bool buildTree);
    //删除大顶堆结点
    TreeNode* removeHeapRoot(TreeNode* root,std::vector<TreeNode*>& treeNodes,int size);
    //查找最下一层级最后一个叶子结点
    TreeNode* findLastLeafNode(TreeNode* root);
    //最找最下一层级最后一个叶子结点
    TreeNode* findLastLeafNode(TreeNode* root,int maxHeight,int height);
    //查找第一个叶子结点
    TreeNode* findFirstLeafNode(TreeNode* root);
    //计算从结点开始的深度
    int calcHeight(TreeNode* root);

};
//排序
void HeapSort::sort(std::vector<int> &nums){
    //记录结点信息
    std::vector<TreeNode*> treeNodes(nums.size());
    //构建完全二叉树
    TreeNode* root = buildFullTree(nums,treeNodes);
    TreeNode* node = root;
    if(node == nullptr){
        return ;
    }
    //首次构建大顶堆
    buildRootMaxHeap(node,true);
    //注意最后一个不遍历，由于treeNodes[0]结点在第一次删除大顶堆结点时已经被删除，避免访问空指针
    for(int i = 0;i < nums.size()-1;i++){
        //大顶堆结点值放置置在数组最末尾处
        nums[nums.size()-1-i] = node->val;
        //记录待删除结点
        TreeNode* toRemove = node;
        //移除大顶堆结点，同时将树最后一个结点提取上来，放置到顶结点，重新构建顺序(选取树最后一个结点对完全二叉树关系影响最小)，更新父子结点关系
        node = removeHeapRoot(node,treeNodes,nums.size()-i);
        //释放被删除结点内存
        delete toRemove;
    }
    //最后一个大顶堆结点(最小)放在数组头部
    if(node != nullptr){
        nums[0] = node->val;
    }
    
    int nStop = 2;
}
//遍历查找前k大
void HeapSort::sort(std::vector<int> &nums,int k){
    std::vector<TreeNode*> treeNodes(nums.size());
    //构建完全二叉树
    TreeNode* root = buildFullTree(nums,treeNodes);
    TreeNode* node = root;
    if(node == nullptr){
        return ;
    }
    //构建大顶堆
    buildRootMaxHeap(node,true);
    //遍历前k-1个，避免k=nums.size,导致访问最后一个结点时置空关系使用到被删除的treeNodes[0]
    for(int i = 0;i < k-1 ;i++){
        //大顶堆结点放置在数组结尾处
        nums[nums.size()-1-i] = node->val;
        TreeNode* toRemove = node;
        //移除大顶堆结点，同时将树最后一个结点提取上来，放置到顶结点，重新构建顺序(选取树最后一个结点对完全二叉树关系影响最小)，更新父子结点关系
        node = removeHeapRoot(node,treeNodes,nums.size()-i);
        //释放被删除结点内存
        delete toRemove;
    }
    //第k大元素更新到数组尾部，数组末尾的k个有序
    if(node != nullptr){
        nums[nums.size()-k] = node->val;
    }

}
//构建大顶堆
void HeapSort::buildRootMaxHeap(TreeNode* root,bool buildTree){
    if(root == nullptr){
        return ;
    }
    int max = 0;
    int maxValue = root->val;
    TreeNode* left = root->left;
    if(left != nullptr){
        //如果预先构建左子树，先递归构建左子树
        if(buildTree){
            buildRootMaxHeap(left,buildTree);
        }
        //比较左子树的顶和当前最大值比较
        if(left->val > maxValue){
            max = 1;
            maxValue = left->val;
        }
    }

    TreeNode* right = root->right;
    if(right != nullptr){
         //如果预先构建右子树，先递归构建右子树
        if(buildTree){
            buildRootMaxHeap(right,buildTree);
        }
        //比较右子树的顶和当前最大值比较
        if(right->val > maxValue){
            max = 2;
            maxValue = right->val;
        }

    }
    //左子树，重新构建大顶堆，不预先构建左子树
    if(max == 1){
        if(left != nullptr){
            //交换数据
            std::swap(root->val,left->val);
            //构建大顶堆
            buildRootMaxHeap(left,buildTree);
        }
    //右子树，重新构建大顶堆，不预先构建右子树
    }else if(max == 2){
        if(right != nullptr){
            //交换数据
            std::swap(root->val,right->val);
            //构建大顶堆
            buildRootMaxHeap(right,buildTree);
        }
    }
}
//计算深度
int HeapSort::calcHeight(TreeNode* root){
    TreeNode* node = root;
    if(root == nullptr){
        return 0;
    }
    int height = 0;
    //一直左结点遍历，完全二叉树，左侧子树深度大
    while(node->left != nullptr)
    {
        node = node->left;
        height += 1;
    }
    return height;
}
//查找首个叶子结点
HeapSort::TreeNode* HeapSort::findFirstLeafNode(TreeNode* root)
{
    if(root == nullptr){
        return nullptr;
    }
    TreeNode* node = root;
    while(node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}
//查找最后一个叶子结点
HeapSort::TreeNode* HeapSort::findLastLeafNode(TreeNode* root,int maxHeight,int height)
{
    TreeNode* node = root;
    if(node == nullptr){
        return nullptr;
    }
    if(node->left == nullptr && node->right == nullptr && height == maxHeight){
        return node;
    }
    if(node->right != nullptr)
    {
        //优先递归遍历右子树
        TreeNode*  last = findLastLeafNode(node->right, maxHeight, height+1);
        if(last != nullptr){
            return last;
        }
    }
    if(node->left != nullptr){
        //右子树遍历未找到则再遍历左子树
        TreeNode* last = findLastLeafNode(node->left,maxHeight,height+1);
        if(last != nullptr){
            return last;
        }
    }
    return nullptr;
}
//查找最后一个叶子结点
HeapSort::TreeNode* HeapSort::findLastLeafNode(TreeNode* root)
{
    if(root == nullptr){
        return nullptr;
    }
    int maxHeight = calcHeight(root);
    return findLastLeafNode(root,maxHeight,0);
}

HeapSort::TreeNode*  HeapSort::removeHeapRoot(TreeNode* root,std::vector<TreeNode*>& treeNodes,int size){
    if(root == nullptr){
        return nullptr;
    }
    //数据量大时查最后一个叶子结点效率太低，容易超时
    // TreeNode* lastLeafNode =  findLastLeafNode(root);
    //采用空间换时间，记录构建完全二杈树结点信息，通过数组及大顶堆顶结点移除后的size查找新的即将调整为顶结点的结点
    TreeNode* lastLeafNode =  treeNodes[size-1];
    if(lastLeafNode == nullptr){
        return nullptr;
    }
    //处理最后一个叶子结点的父子结点关系
    if(lastLeafNode->parent != nullptr)
    {
        //判断是左子树或右子树
        if(lastLeafNode->parent->left == lastLeafNode){
            lastLeafNode->parent->left = nullptr;
        }else if(lastLeafNode->parent->right == lastLeafNode){
            lastLeafNode->parent->right = nullptr;
        }
        lastLeafNode->parent = nullptr;
    }
    //新的顶结点子结点分别指向既有顶结点的父子结点
    lastLeafNode->left = root->left;
    if(root->left != nullptr){
        root->left->parent = lastLeafNode;
    }
    lastLeafNode->right = root->right;
    if(root->right != nullptr){
        root->right->parent = lastLeafNode;
    }
    //重新构建新的大顶堆，从顶结点开始，不需要预先构建左右子树
    buildRootMaxHeap(lastLeafNode,false);
    //返回叶子结点
    return lastLeafNode;
}
#endif
