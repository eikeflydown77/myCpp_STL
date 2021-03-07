
#include "ListNode.h"

template <typename T>
ListNodePosi(T) ListNode<T> :: insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode(e, pred, this);    //创建新节点
    pred->succ = x; //前驱的后继为x
    pred = x;   //该节点的前驱设置为x
    return x;   //返回新节点的位置
}

template <typename T>
ListNodePosi(T) ListNode<T> :: insertAsSucc(T const &e) {
    ListNodePosi(T) x = new ListNode(e, this, succ);    //创建新节点
    succ->pred = x;
    succ = x;
    return x;
}