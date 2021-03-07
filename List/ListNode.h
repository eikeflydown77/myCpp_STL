//
// Created by 龚世炎 on 2021/2/10.
//

#ifndef LISTNODE_H
#define LISTNODE_H

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置(ISO c++.0x, template alias)，化名

template <typename T>
struct ListNode {   //列表节点模版类（以双向链表形式实现）
    T data; //数据
    ListNodePosi(T) pred;   //前驱
    ListNodePosi(T) succ;   //后继

    //构造函数
    ListNode() {}   //针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : data(e), pred(p), succ(s) {} //默认构造器

    //操作接口
    ListNodePosi(T) insertAsPred(T const &e);   //作为前驱节点插入
    ListNodePosi(T) insertAsSucc(T const &e);     //作为后继节点插入
};

#endif //ListNode
