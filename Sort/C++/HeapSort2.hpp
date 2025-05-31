#ifndef _HEAP_SORT_2_HPP_
#define _HEAP_SORT_2_HPP_
#include <iostream>
#include <vector>

//大顶堆数组方式
class HeapSort2{
public:
    void sort(std::vector<int>& nums);
    void sort(std::vector<int>& nums,int k);
private:
    //构建大顶堆
    void buildRootMaxHeap(std::vector<int>& nums,int size,int i);
    //构建当前所有结点大顶堆
    void buildRootMaxHeap(std::vector<int>& nums,int size);
    //移除大顶堆结点
    void removeRootMaxHeap(std::vector<int>& nums,int& size);
    //获取最后一个叶子结点的索引
    int getLastLeafIndex(int size);
    //获取第一个非叶子点根结点index
    int getLastNotLeafIndex(int size);
};

//最后一个非叶子结点的树根结点
int HeapSort2::getLastNotLeafIndex(int size){
    return size / 2 -1;
}

//最后一个叶子结点
int HeapSort2::getLastLeafIndex(int size){
    return size - 1;
}


//构建大顶堆
void HeapSort2::buildRootMaxHeap(std::vector<int>& nums,int size,int i){
    //数组左子结点索引=2*i+1
    //数组右子结点索引=2*i+2
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    //判断是否左子树最大
    if(left < size && nums[left] > nums[largest]){
        largest = left;
    }
    //判断是否右子树最大
    if(right < size && nums[right] > nums[largest]){
        largest = right;
    }
    //如果左/右子树结点更大
    if(largest != i){
        //则交换值，将更大的上调
        std::swap(nums[largest],nums[i]);
        //以最大的为基准再次构建大顶堆
        buildRootMaxHeap(nums,size,largest);
    }
}

//移除堆顶结点
void HeapSort2::removeRootMaxHeap(std::vector<int> &nums,int &size){
    //移除大顶堆结点即nums[0]，放置于nums[size-1]位置, size -= 1
    std::swap(nums[0],nums[size-1]);
    //大小减1
    size -= 1;
}

//构建大顶堆
void HeapSort2::buildRootMaxHeap(std::vector<int>& nums,int size){
    //从最后一个非子结点到根结点进行遍历调整
    for(int i= getLastNotLeafIndex(size); i >= 0;i--){
        buildRootMaxHeap(nums, size,i);
    }
}

//全数组排序
void HeapSort2::sort(std::vector<int> &nums){
    //构建大顶堆
    buildRootMaxHeap(nums,nums.size());
    
    //移除再重新构建
    int heapSize = nums.size();
    for(int i = 1;i < nums.size();i++){
        //移除顶结点值
        removeRootMaxHeap(nums,heapSize);
        //子树有序，只从根调整
        buildRootMaxHeap(nums,heapSize,0);
    }
}
//最大的k个排序
void HeapSort2::sort(std::vector<int> &nums,int k){
    //构建大顶堆
    buildRootMaxHeap(nums,nums.size());

    //移除再重新构建
    int heapSize = nums.size();
    for(int i = 0;i < k;i++){
        //移除顶结点值
        removeRootMaxHeap(nums,heapSize);
        //子树有序，只从根调整
        buildRootMaxHeap(nums,heapSize,0);
    }
}
#endif
