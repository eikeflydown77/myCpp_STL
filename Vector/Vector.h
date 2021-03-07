//
// Created by 龚世炎 on 2021/1/19.
//

#ifndef VECTOR_H
#define VECTOR_H
#include "Fib.h"

typedef int Rank; //秩
#define DEFAULT_CAPACITY 3  //默认初始容量（实际应用中可以设置更大）

template<typename T> class Vector { //向量模版类
protected:
    Rank _size; //规模
    int _capacity;  //容量
    T *_elem;   //向量所在，指针，指向数据区首地址
    void copyFrom(T const *A, Rank lo, Rank hi); //复制
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时缩容
    Rank bubble(Rank lo, Rank hi);  //扫描交换
    void bubbleSort();  //起泡排序算法
    Rank max(Rank lo, Rank hi);  //选取最大元素
    void selectionSort(Rank lo, Rank hi);   //选择排序
    void merge(Rank lo, Rank mi, Rank hi);  //归并算法
    void mergeSort(Rank lo, Rank hi);   //归并排序
    void heapSort(Rank lo, Rank hi);    //堆排序
    Rank partition(Rank lo, Rank hi);   //轴点构造算法
    void quickSort(Rank lo, Rank hi);   //快速排序
    void shellSort(Rank lo, Rank hi);   //希尔排序
public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {  //容量为c、规模为s、所有元素初始为v
        _elem = new T[_capacity = c];      //申请初始容量的内存空间，并返回指针
        for (_size = 0; _size < s; _elem[_size ++] = v);    //为vector中每个元素赋值，每赋值依次_size增大
    }
    Vector(T const *A, Rank n) {copyFrom(A, 0, n);}  //复制构造，作用于数组，整体复制
    Vector(T const *A, Rank lo, Rank hi) {copyFrom(A, lo, hi);}     //复制构造，作用于数组，区间复制
    Vector(Vector<T> const &V) {copyFrom(V._elem, 0, V._size);}  //复制构造，作用于向量，整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) {copyFrom(V._elem, lo, hi);}  //复制构造，作用于向量，区间复制

    //析构函数
    ~Vector() {delete[] _elem;}

    //只读访问接口
    Rank size() const {return _size;} //返回规模
    bool empty() const {return  !_size;}    //判空，为0则为空返回1
    Rank find(T const &e) const {return find(e, 0, _size);}   //无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const;  //无序向量区间查找
    Rank search(T const &e) const {return search(e, 0, _size);}   //有序向量整体查找
    Rank search(T const &e, Rank lo, Rank hi) const;    //有序向量区间查找
    int disordered() const;

    //可写访问接口
    T & operator[](Rank r);  //重载下标操作符
    const T & operator[](Rank r) const; //仅限用于右值，即只读的重载版本
    Vector<T> & operator=(Vector<T> const &);//重载赋值操作符，以便于直接克隆
    T remove(Rank r);   //删除秩为r的元素，返回该元素
    int remove(Rank lo, Rank hi);   //删除秩在区间[lo, hi)之内的元素，返回删除元素的个数
    Rank insert(Rank r, T const &e);    //插入元素
    Rank insert(T const &e);    //默认插入到最后
    void sort(Rank lo, Rank hi);    //对[lo, hi)排序
    void sort() {sort(0, _size);}   //对整体排序
    void unsort(Rank lo, Rank hi);  //对[lo, hi)置乱
    void unsort() {unsort(0, _size);}  //对[lo, hi)排序
    int deduplicate();  //无序去重
    int uniquify(); //有序去重
    void traverse(void (*)(T &));    //遍历（使用函数指针，只读或局部修改）
    template<typename VST> void traverse(VST &); //遍历（使用函数对象，全局修改）
};
#endif //Vector
