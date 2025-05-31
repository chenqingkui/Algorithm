#include <iostream>
#include "QuickSort.hpp"
#include "QuickSort2.hpp"
#include "HeapSort.hpp"
#include "HeapSort2.hpp"
#include <vector>

void print(std::vector<int>& nums){
  for (auto num:nums) {
     std::cout<<num;
     std::cout<<" ";
  }
  std::cout<<std::endl;
}


int main(){

    QuickSort sort;
    std::vector<int> nums = {1,98,32,53,2,0,-1,68,34,3,3,89,32,5};
    sort.sort(nums);
    print(nums);

    QuickSort2 qsort2;
    std::vector<int> nums2 = {133,985,321,513,2,0,-1,68,34,3,3,89,32,5};
    qsort2.sort(nums2);
    print(nums2);

    HeapSort hpSort;
    std::vector<int> hpSortNums = {3,2,3,1,2,4,5,5,6};
    hpSort.sort(hpSortNums);
    print(hpSortNums);
    
    HeapSort2 hpSort2;
    std::vector<int> hpSortNums2 = {3,2,1,5,6,4};
    hpSort2.sort(hpSortNums2);
    print(hpSortNums2);
    
    return 0;
}
