typedef int Rank;
#define DEFAULT_CAPACITY 3
template <typename T>class Vector
{
protected:
	Rank _size;
	int _capacity;
	T* _elem;
	void copyfrom(T const *A, Rank lo, Rank hi);
	void expand();
	void shrink();
public:
	Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	~Vector(){delete []_elem;}
	Vector<T> & operator=(Vector<T> const&);
	Rank size() const { return _size; }
	bool empty()const { return !_size; }
	T& operator[](Rank r)const { return _elem[r]; }
	Rank find(T const&, Rank lo, Rank hi)const;
	Rank insert(Rank r, T const& e);
	int remove(Rank lo, Rank hi);
	int remove(Rank r);
	int deduplicate();
	Rank search(T const&, Rank lo, Rank hi)const;
	int uniquify();
	//T shrink();
private:

};
//template <typename T>
//Vector::Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
//{
//	_elem = new T[_capacity = c];
//	for (_size = 0; _size < s; _elem[_size++] = v);
//}

//template <typename T>
//Vector::~Vector()
//{
//	delete[]_elem;
//}

template <typename T>
void Vector<T>::copyfrom(T const* a, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = a[lo++];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
		delete[]_elem;
	copyfrom(V._elem, 0, V.size());
	return *this;
}

template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;

}

template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)
		return;
	if (_size << 2 > _capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;
}

template <typename T>
Rank Vector<T>::find(T const&e, Rank lo, Rank hi)const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
		return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template <typename T>
int Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T>
int Vector<T>::deduplicate()
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - 1;
}

template <typename T>
Rank Vector<T>::search(T const&e, Rank lo, Rank hi)const
{
	return binsearch(_elem, e, lo, hi);
}
template <typename T> static Rank binsearch(T*a, T const& e, Rank lo, Rank hi)
{
	while (1<hi-lo)
	{
		Rank mi=(lo + hi) >> 2;
		(e < a[mi]) ? hi = mi : lo = mi;
	}
	return (e == a[lo]) ? lo : -1;
}