#include "list.h"
template<typename T>class List
{
private:
	int _size;
	ListNodePos(T) header;
	ListNodePos(T) tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePos(T) p, int n );
public:
	List() { init(); }
	~List() { clear(); delete header; delete tailer; }
	T& operator[](Rank r)const;
	ListNodePos(T) first()const { return header->succ; }
	ListNodePos(T) last()const { return tailer->pred; }
	ListNodePos(T) find(T const& e)const { return find(e, _size, tailer); }
	ListNodePos(T) find(T const& e, int n, ListNodePos(T)p)const;
	ListNodePos(T) insertAsFirst(T const& e);
	ListNodePos(T) insertAsLast(T const& e);
	ListNodePos(T) insertA(ListNodePos(T)p, T const&e);	//当作p的前驱插入
	ListNodePos(T) insertB(ListNodePos(T)p, T const&e);	//当作p的后继插入
	T remove(ListNodePos(T) p);
	int deduplicate();
	int uniquify();

	bool empty()const{ return _size<=0;}
	Rank size()const { return _size;}
	//ListNodePos(T) insertAsPred(T const& e);
	//ListNodePos(T) insertAsSucc(T const& e);
};


template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	tailer = new ListNode<T>;
	header->succ = tailer;
	header->pred = nullptr;
	tailer->pred = header;
	tailer->succ = nullptr;
	_size = 0;
}

template<typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ);
	return pldSize;
}

template<typename T>
void List<T>::copyNodes(ListNodePos(T) p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
T& List<T>::operator[](Rank r)const
{
	ListNodePos(T) p = first();
	while (0 < r--)
		p = p->succ;
	return p->data;
}

template<typename T>
ListNodePos(T) List<T>::find(T const&e, int n, ListNodePos(T) p)const
{
	while (0 < n--)
		if (e == (p = p->pred)->data)	//因为兼容从tailer开始的，所以从p->pred开始
			return p;
	return nullptr;
}

template<typename T>
ListNodePos(T) List<T>::insertAsFirst(T const&e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePos(T) List<T>::insertAsLast(T const&e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template<typename T>
ListNodePos(T) List<T>::insertA(ListNodePos(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
ListNodePos(T) List<T>::insertB(ListNodePos(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(ListNodePos(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}


template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
		return 0;
	int oldSize = _size;
	ListNodePos(T) p = header;
	Rank r = 0;
	while (tailer != (p = p->succ))
	{
		ListNodePos(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;

}