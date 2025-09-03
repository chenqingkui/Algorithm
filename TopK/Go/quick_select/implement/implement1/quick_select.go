package implement1
import (
)
func FindTopKNum(nums []int, k int) int {
    return quickSelect(&nums,k)
}

func quickSelect(nums *[]int,k int) int {
    n := len(*nums)
    low := 0
    high := n - 1
    pivot := -1
    for {
        pivot = quickPartition(nums,low,high)
        if pivot == n - k{
            return (*nums)[pivot]
        }else if pivot < n - k {
            low = pivot+1
        }else{
            high = pivot-1
        }
    }
    return (*nums)[pivot]
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

