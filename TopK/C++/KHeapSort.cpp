#include <vector>
using namespace std;
class KHeapSort{
public:
    int findTopKNum(vector<int>& nums,int k){
        kHeapSort(nums,k);
        int n = nums.size();
        return nums[n-k];
    }
private:
    void heapify(vector<int>& nums,int n,int i)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;
        if(left < n && nums[left] > nums[largest])
        {
            largest = left;
        }
        if(right < n && nums[right] > nums[largest])
        {
            largest = right;
        }
        if(largest != i)
        {
            swap(nums[largest],nums[i]);
            heapify(nums,n,largest);
        }
    }
    void kHeapSort(vector<int>& nums,int k)
    {
        int n = nums.size();
        int lastParent = n/2 -1;
        for(int i = lastParent;i >= 0;i--)
        {
            heapify(nums,n,i);
        }

        for(int i = 0;i < k;i++)
        {
            swap(nums[0],nums[n-1]);
            n--;
            heapify(nums,n,0);
        }
    }
};

int main(){
    KHeapSort kSort;
    vector<int> nums = {2,3,5,1,88,66,11,3,0}; 
    int num = kSort.findTopKNum(nums,5);	
    printf("%d\n",num);
    return 0;
}
