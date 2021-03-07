//
// Created by 龚世炎 on 2021/2/10.
//

#ifndef LIST_H
#define LIST_H

#include "ListNode.h"

template <typename T>
class List {
private:
    int _size;     //规模
    ListNodePosi(T) header;     //头哨兵
    ListNodePosi(T) trailer;    //尾哨兵

protected:
    void init();  //列表创建时的初始化
    int clear();  //清除所有节点
    void copyNodes(ListNodePosi(T) p, int n); //复制列表中自位置p起的n项
    ListNodePosi(T) merge(ListNodePosi(T), int, List<T> &,ListNodePosi(T), int);  //归并
    void mergeSort(ListNodePosi(T), int);   //对从p开始连续的n个节点归并排序
    void selectSort(ListNodePosi(T), int);   //对从p开始连续的n个节点选择排序
    void insertSort(ListNodePosi(T), int);  //对从p开始的连续的n个节点插入排序
    void radixSort(ListNodePosi(T), int );  //对从p开始的连续n个节点基数排序

public:
    //构造函数
    List() {init();}    //默认
    List(List<T> const &L);  //整体复制列表L
    List(List<T> const &L, Rank r, int n);  //复制列表L中自第r项起的n项
    List(ListNodePosi(T) p, int n);  //复制列表中自位置p起的第n项

    //析构函数
    ~List();    //释放（包含头、尾哨兵在内的）所有节点

    //只读访问接口
    Rank size() const {return _size;}   //规模
    bool empty() const {return _size < 0;}    //判空
    T& operator[](Rank r) const;    //重载[]，使其支持循序访问
    ListNodePosi(T) first() const {return header->succ;}    //首节点位置
    ListNodePosi(T) last() const {return trailer->pred;}    //末节点位置
    bool valid(ListNodePosi(T) p) { //判断节点是否合法
        return p && (trailer != p) && (header != p);    //不是头尾节点且不为NULL
    }
    ListNodePosi(T) find(T const &e) const{ //无序列表查找
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;   //无序区间查找
    ListNodePosi(T) search(T const &e) const{  //有序列表查找
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const; //有序区间查找
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);    //在p及其n-1个后继中选出最大者
    ListNodePosi(T) selectMax() {return selectMax(header->succ, _size);} //整体最大值

    //可写访问接口
    ListNodePosi(T) insertAsFirst(T const &e);   //将e作为首节点插入
    ListNodePosi(T) insertAsLast(T const &e);   //将e作为末节点插入
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);    //将e作为p的前驱节点插入
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);    //将e作为p的后继节点插入
    T remove(ListNodePosi(T) p);    //删除合法位置p处的节点，返回被删除节点
    void merge(List<T> &L) {merge(header->succ, _size, L, L.header->succ, L._size);}    //全列表归并
    void sort(ListNodePosi(T) p, int n);    //列表区间排序
    void sort() {sort(first(), _size);} //列表整体排序
    int deduplicate();  //无序去重
    int uniquify(); //无序去重
    void reverse(); //前后倒置
    //遍历
    void traverse(void(*) (T&));    //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template<typename VST> //操作器
    void traverse(VST &);   //遍历，依次实施visit操作（函数对象，可全局修改）
};

#endif
