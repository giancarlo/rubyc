/**
 * Array Template. 
 * 
 */

#ifndef ARRAY_H
#define ARRAY_H

template <typename T, int Size = 30000>
class Array {
	T  _static[Size];

	T* _buffer;
	T* _next;
public:
	typedef T* iterator;

	Array() : _buffer(_static), _next(_buffer) {}

	T* next()  { return _next++; }

	iterator begin() { return _buffer; }
	iterator end()   { return _next; }

	int count()  { return _next - _buffer; }
	T* push(T c) { *_next = c; return _next++; }

	void rewind(T* position) { _next = position; }

	/** 
	 * Increase the size of the array.
	 */
	void grow()
	{
		
	}

	/**
	 * Checks if the memory left is less than the minimum value
	 */
	void check()
	{
		if (count() < Size)
			grow();
	}
};

#endif
