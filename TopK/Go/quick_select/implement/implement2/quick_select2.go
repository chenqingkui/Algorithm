package implement2
import (
)
func FindTopKNum(nums []int, k int) int {
    return quickSelect(&nums,0,len(nums)-1,k)
}

func quickSelect(nums *[]int,low int,high int,k int) int { 
    pivot := quickPartition(nums,low,high)
    if pivot == high +1 - k{
        return (*nums)[pivot]
    }else if pivot < high + 1 - k {
        return quickSelect(nums,pivot+1,high,k)
    }else{
        return quickSelect(nums,low,pivot-1,k - (high+1-pivot))
    }
}

func quickPartition(nums *[]int, low int,high int) int {
    mid := low + (high-low)/2
    (*nums)[low],(*nums)[mid] = (*nums)[mid],(*nums)[low]
    pivot := (*nums)[low]
    for low < high {
        for low < high && (*nums)[high] >= pivot {
            high--
        }
        if low < high {
            (*nums)[low],(*nums)[high] = (*nums)[high],(*nums)[low]
        }
        for low < high && (*nums)[low] <= pivot {
            low++
        }
        if low < high {
            (*nums)[low],(*nums)[high] = (*nums)[high],(*nums)[low]
        }
    }
    (*nums)[low] = pivot 
    return low 
}
