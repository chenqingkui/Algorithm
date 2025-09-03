package main 
import (
   "fmt"
   qs "quick_select/implement/implement1"
   qs2 "quick_select/implement/implement2"
)
func main(){
  fmt.Printf("%d\n",qs.FindTopKNum([]int{2,3,5,1,88,66,11,3,0},5))
  fmt.Printf("%d\n",qs2.FindTopKNum([]int{2,3,5,1,88,66,11,3,0},5))
}
