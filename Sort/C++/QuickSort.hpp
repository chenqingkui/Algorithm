#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_
#include <vector>
#include <iostream>
class QuickSort{
public:
    void sort(std::vector<int>& nums);
private:
    int partition(std::vector<int>& nums,int low,int high);
    
    void sort(std::vector<int>& nums,int low,int high);
};

void QuickSort::sort(std::vector<int>& nums){
    int size =nums.size();
    sort(nums,0,size-1);
}
void QuickSort::sort(std::vector<int>& nums,int low,int high){
    if(low >= high){
        return ;
    }
    int pivot = partition(nums,low,high);
    sort(nums,low,pivot-1);
    sort(nums,pivot+1,high);
}
//分片后遍选择遍历[low,pivot-1],[pivot+1,high]

int QuickSort::partition(std::vector<int>& nums,int low,int high){
    int pivot = nums[low];
    int left = low;
    int right = high;
    //快排分段及返回下标
    while(left < right){
        //从右往左找，找到小于等于中枢值的
        while(left < right && nums[right] > pivot){
            right--;
        }
        //如果发现有小于中枢值的则移到分界区左边
        if(left < right)
        {
            nums[left++] = nums[right];
        }
        //从左往右找，找到大于等于中枢值
        while(left < right && nums[left] < pivot){
            left++;
        }
        //如果找到，则移动到分界区右边
        if(left < right)
        {
            nums[right--] = nums[left];
        }
    }
    //分界点置为中枢值
    nums[left] = pivot;
    return left;
}

#endif
