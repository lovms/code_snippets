import random
import sys
import numpy as np


def quicksort(array, low, high):
    if low >= high:
        return
         
#    pivot = random.randint(low, high)
#    #print('low: %s ; high: %s; pivot: %s' % (low, high, pivot))
#    if pivot > low:
#        tmp = array[low]
#        array[low] = array[pivot]
#        array[pivot] = tmp
    pivot = low
    l = low + 1
    h = high
    while l <= h:
        while l < high and array[l] <= array[pivot]:
            l += 1
        while h > pivot and array[h] >= array[pivot]:
            h -= 1
        if l < h:
            tmp = a[l]
            a[l] = a[h]
            a[h] = tmp
            l += 1
            h -= 1
    tmp = a[h]
    a[h] = a[pivot]
    a[pivot] = tmp
    pivot = h
    quicksort(array, low, pivot)
    quicksort(array, pivot + 1, high)

'''
思想就是找到一个pivot，然后通过前后遍历整个数组，将其分成两个部分：
小索引部分都是不大于pivot的；
大索引部分都是不小于pivot的。

基本的想法是通过索引low从左边找大于pivot的，通过high从右边找小于pivot的然后作交换；
pivot选择low的起始位置；
但是实际的quicksort算法使用了技巧，就是先将pivot保存起来，然后先后依次将high找到的小于pivot的数放到low,然后将low找到的大于pivot的数放到high，
最后当low==high时，再将pivot放到low索引最后的位置,从而省去了多次交换！！！

'''

def std_quicksort(array, low, high):
    if low >= high:
        return
    pivot = low
    l = low
    h = high
    pivot_data = array[l]
    while l < h:
        while l < h and array[h] >= pivot_data:
            h -= 1
        #if h != l:
        array[l] = array[h]
        while l < h and array[l] <= pivot_data:  # 本行的l < h条件不能换成 l <= high; 因为此时array[h] 其实是pivot_data，只是没有填上去。（考虑序列:48, 34, 49）
            l += 1
        if l != h:
            array[h] = array[l]
    array[l] = pivot_data  #最后h == l
    pivot = l
    std_quicksort(array, low, pivot)
    std_quicksort(array, pivot+1, high)

if __name__ == '__main__':
    a = list(np.random.randint(100, size=50))
    print(a)
    #quicksort(a, 0, len(a) - 1)
    std_quicksort(a, 0, len(a) - 1)
    print("Sorted")
    print(a)
            

