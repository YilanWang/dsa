#pragma once
typedef int Rank;
#define ListNodePos(T) ListNode<T>*

template<typename T>struct ListNode
{
	T data;
	ListNodePos(T) pred;
	ListNodePos(T) succ;
	ListNode() {}
	ListNode(T e, ListNodePos(T) p = nullptr, ListNodePos(T) s = nullptr) :data(e), pred(p), succ(s) {}

	//api
	ListNodePos(T) insertAsPred(T const& e);
	ListNodePos(T) insertAsSucc(T const& e);
};

template<typename T>
ListNodePos(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePos(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
ListNodePos(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePos(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}