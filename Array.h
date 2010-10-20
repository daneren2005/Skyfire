#ifndef _ARRAY_H
#define	_ARRAY_H

template <class T>
class Array
{
public:
	Array();
	Array(unsigned long size);
	Array(const Array& orig);
	~Array();

	virtual T& operator[](unsigned col);
	virtual const T& operator[](unsigned col) const; 

	long size();
protected:
	T* array;
	unsigned long _size;
};

template <class T>
Array<T>::Array()
{
	_size = 1;
	array = new T[_size];
}

template <class T>
Array<T>::Array(unsigned long size)
{
	_size = size;
	array = new T[_size];
}

template <class T>
Array<T>::Array(const Array<T> &orig)
{
	_size = orig._size;
	array = new T[_size];
	for(int i = 0; i < _size; i++)
	{
		array[i] = orig.array[i];
	}
}

template <class T>
Array<T>::~Array()
{
	// TODO: figure out why this is crashing
	//delete[] array;
}

template <class T>
T& Array<T>::operator[](unsigned col)
{
	if(col >= _size)
	{
		// TODO: break
	}
	else
	{
		return array[col];
	}
}

template <class T>
const T& Array<T>::operator[](unsigned col) const
{
	if(col >= _size)
	{
		// TODO: break
	}
	else
	{
		return array[col];
	}
}

template <class T>
long Array<T>::size()
{
	return _size;
}

#endif
