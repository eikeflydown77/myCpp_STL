//
// Created by 龚世炎 on 2021/2/10.
//
#include "List.h"

template <typename T>
void List<T> :: init() {
    header = new ListNode<T>;   //创建头哨兵节点
    trailer = new ListNode<T>;  //创建尾哨兵节点
    header -> succ = trailer; header -> pred = NULL;    //头节点互联
    trailer -> pred = header; trailer -> succ = NULL;   //尾节点互联
    _size = 0;  //规模
}

template <typename T>   //assert:r合法，即0 <= r <=_size
T& List<T> :: operator[](Rank r) const {    //虽然方便，但是效率低下
    ListNodePosi(T) p = first();    //从首节点出发
    while (0 < r--) p = p -> succ;  //顺数第r个节点
    return p -> data;   //返回目标节点的数据
}   //任一节点的秩，即是其前驱节点的总数

template <typename T>
ListNodePosi(T) List<T> :: find(T const &e, int n, ListNodePosi(T) p) const{
    while(0 < n--) {
        if (e == (p = p -> pred) -> data) { //查找p的前n个元素构成的区间，假设已经重载操作符"=="
            return p;
        }
    }
    return NULL;    //查找失败
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst ( T const& e ) {
    _size++;
    return header->insertAsSucc (e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast (T const& e) {
    _size++;
    return trailer->insertAsPred (e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAfter (ListNodePosi(T) p, T const& e) {
    _size++;
    return p->insertAsSucc (e);
}

template <typename T>
ListNodePosi(T) List<T>::insertBefore ( ListNodePosi(T) p, T const& e ){
    _size++;
    return p->insertAsPred (e);
}

template <typename T> //列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while(n--) {
        insertAsLast (p->data);  //将每一项作为最后一项插入
        p = p->succ;
    }
}

template <typename T>
List<T>::List(List<T> const &L) {
    copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> const &L, int r, int n) {
    copyNodes(L[r], n);
}

template<typename T>
T List<T>::remove(ListNodePosi(T) p) {
    T e = p->data;  //备份溢出数据，假定T可直接赋值
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size --;
    return e;
}

template<typename T>
List<T>::~List() {  //析构
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while(0 < _size) {
        remove(header -> succ);
    }
    return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2) return 0; //平凡列表自然无重复
    int oldSize = _size;    //记录原规模
    ListNodePosi(T) p = first();    //从首节点开始
    Rank r = 1;     //用于记录去重复后的秩
    while (trailer != (p = p->succ)) {  //直到p到尾哨兵
        ListNodePosi(T) q = find(p->data, r, q);    //依次遍历每个节点
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0; //平凡列表自然无重复
    int oldSize = _size;    //记录原规模
    ListNodePosi(T) p = first();    //p为各段起点，从首节点开始
    ListNodePosi(T) q;  //q为p的后继
    while (trailer != (q = p->succ)) {  //直到p到尾哨兵
        if(p->data != q->data) p = q;   //若互异，则转向下一区段
        else remove(q);
    }
    return oldSize - _size;
}

template<typename T>
ListNodePosi(T) List<T>::search(const T &e, int n, ListNodePosi(T) p) const {  //前驱查找
    while (0 < n--) {
        if ((p = (p->pred)->data) <= e) break;  //依次比较
    }
    return p;
}

template<typename T>
void List<T>::selectSort(ListNodePosi(T) p, int n) {    //对列表中起始于位置p、宽度为n的区间做选择排序
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ;  //遍历找到区间的尾节点
    while (1 < n) {     //在至少还剩两个节点之前，在待排序区间内
        insertBefore(tail,remove(selectMax(head->succ, n)));//找出最大者,将其移至无序区间末尾（作为有序区间新的首元素)
        tail = tail->pred;
        n--;
    }
}

template<typename T>    //对列表中起始于位置p、宽度为n的区间做选择排序
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) { //assert: valid(p) && rank(p) + n <= size
    ListNodePosi(T) max = p;    //暂定最大值为p
    for (ListNodePosi(T) cur = p; 1 < n; n--) {
        if((cur = cur->succ)->data >= max->data) {  //后续节点逐一与最大比较
            max = cur;  //则更新最大元素位置
        }
    }
    return max; //返回最大节点
}

template<typename T>    //对列表中起始于位置p、宽度为n的区间做选择排序
void List<T>::insertSort(ListNodePosi(T) p, int n) {
    for (int r = 0; r < n; r++) {   //r在不断增大直至n
        insertAfter(search(p->data, r, p), p->data);    //由于search接口是前驱查找，返回不大于p->data的位置
        p = p->succ;
        remove(p->pred);    //转向下一节点
    }
}









