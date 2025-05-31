#ifndef _QUICK_SORT_2_HPP_
#define _QUICK_SORT_2_HPP_
#include <vector>
class QuickSort2{
public:
    void sort(std::vector<int>& nums);
private:
    int partition(std::vector<int>& nums,int low,int high);
    
    void sort(std::vector<int>& nums,int low,int high);
};

void QuickSort2::sort(std::vector<int>& nums){
    sort(nums,0,nums.size() - 1);
}

//分片方式 hoare返回右侧过来的指针right,遍历需要[low,piovt],[piovt+1,high]
int QuickSort2::partition(std::vector<int>& nums,int low,int high){
    int mid = low +(high-low)/ 2;
    int pivot = nums[mid];
    int left = low-1;
    int right = high+1;
    //快排分段及返回下标
    while(left < right){
        //从右往左找，找到小于等于中枢值的
        do{
            right--;
        }while(nums[right] > pivot);
       
        //从左往右找，找到大于等于中枢值
        do{
            left++;
        }while(nums[left] < pivot);

        //如果找到，则移动到分界区右边
        if(left < right)
        {
            std::swap(nums[left],nums[right]);
        }
    }
    return right;
}


void QuickSort2::sort(std::vector<int>& nums,int low,int high){
    if(low >= high){
        return ;
    }
    int pivot = partition(nums,low,high);
    //pivot返回为right(left >= right)
    //遍历需要[low,piovt],[piovt+1,high]
    sort(nums,low,pivot); //此处不可为pivot-1
    sort(nums,pivot+1,high);
}
#endif
