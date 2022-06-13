#include "Vector.h"
#include <iostream>
#include <cstddef>


Vector::Vector(const Value* rawArray, const size_t size, float coef) 
	: _multiplicativeCoef(coef), _size(size), _capacity(_size)
{
	if (_capacity == 0)
	{
		return;
	}

	else
	{
		_data = new Value[_capacity];
		
		for (auto i = 0; i < _capacity; i++)
		{
			_data[i] = rawArray[i];
		}
	}
}

Vector::Vector(const Vector& other)
{
	_size = other.size();
	_capacity = other.size();
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = new Value[_capacity];

	for (int i = 0; i < _capacity; i++)
	{
		_data[i] = other._data[i];
	}
}

Vector& Vector::operator=(const Vector& other)
{
	if (this == &other)
	{
		return *this;
	}

	_size = other.size();
	_capacity = other.capacity();
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = new Value[_capacity];

	for (int i = 0; i < _capacity; i++)
	{
		_data[i] = other._data[i];
	}

	return *this;
}

Vector::Vector(Vector&& other) noexcept
{
	_size = other.size();
	_capacity = other.capacity();
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = other._data;

	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 2.0f;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	_size = other.size();
	_capacity = other.capacity();
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = other._data;

	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 2.0f;
	
	return *this;
}

//------Своя функция для переаллоцирования памяти

void Vector::reallocate() 
{
	_capacity = _size * _multiplicativeCoef;
	Value* tempArray = new Value[_size];

	for (int i = 0; i < _size; i++)
	{
		tempArray[i] = _data[i];
	}

	delete[] _data;
	_data = new Value[_capacity];

	for (int j = 0; j < _size; j++)
	{
		_data[j] = tempArray[j];
	}

	delete[] tempArray;
}

void Vector::pushBack(const Value& value)
{
	_size = _size + 1;

	if (_size > _capacity)
	{
		reallocate();
	}

	_data[_size - 1] = value;
}

void Vector::pushFront(const Value& value)
{
	_size = _size + 1;

	if (_size > _capacity)
	{
		reallocate();
	}

	for (int i = _size; i > 0; i--)
	{
		_data[i] = _data[i - 1];
	}

	_data[0] = value;
}

void Vector::insert(const Value& value, size_t pos)
{
	if (_size >= _capacity)
	{
		reallocate();
	}

	for (int l = _size; l > pos - 1; l--)
	{
		_data[l] = _data[l - 1];
	}

	_data[pos - 1] = value;
	_size = _size + 1;
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
	size_t shift = size;
	size_t tempSize = _size + size;

	while (tempSize >= _capacity)
	{
		reallocate();
	}

	_size = _size + size;

	while (shift != 0)
	{
		for (int k = _size - 1; k > pos; k--)
		{
			_data[k] = _data[k - 1];
		}
		shift = shift - 1;
	}

	for (int h = 0; h < size; h++)
	{
		_data[pos + h] = values[h];
	}

}

void Vector::insert(const Vector& vector, size_t pos)
{
	size_t shift = vector.size();
	size_t tempSize = vector.size() + _size;
	_multiplicativeCoef = vector._multiplicativeCoef;

	while (tempSize >= _capacity)
	{
		reallocate();
	}

	_size = _size + vector.size();

	while (shift != 0)
	{
		for (int k = _size - 1; k > pos - 1; k--)
		{
			_data[k] = _data[k - 1];
		}
		shift = shift - 1;
	}

	for (int h = 0; h < vector.size(); h++)
	{
		_data[pos - 1 + h] = vector._data[h];
	}
}

void Vector::popBack()
{
	if (_size == 0)
	{
		throw std::runtime_error("Вектор пуст");
	}

	else 
	{
		_data[_size - 1] = 0;
		_size = _size - 1;
	}
}

void Vector::popFront()
{
	if (_size == 0)
	{
		throw std::runtime_error("Вектор пуст");
	}

	else 
	{
		for (int i = 0; i < _size; i++)
		{
			_data[i] = _data[i + 1];
		}

		_data[_size - 1] = 0;
		_size = _size - 1;
	}
}

void Vector::erase(size_t pos, size_t count)
{
	if (_size == 0 || pos > _size)
	{
		return;
	}

	size_t tempCount = count;

	if (pos + count >= _size) 
	{
		for (int i = pos; i < _size; i++)
		{
			_data[i] = 0;
		}
		_size = pos;
	}

	else if (pos + count < _size)
	{
		while (tempCount != 0) 
		{
			for (int i = pos; i < _size; i++)
			{
				_data[i] = _data[i + 1];
			}
			tempCount = tempCount - 1;
		}
		_size = _size - count;
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
	erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const
{
	return(_size);
}

size_t Vector::capacity() const
{
	return(_capacity);
}

double Vector::loadFactor() const
{
	return (_size / _capacity);
}
Value& Vector::operator[](size_t idx)
{
	return(_data[idx]);
}

const Value& Vector::operator[](size_t idx) const
{
	return(_data[idx]);
}

long long Vector::find(const Value& value) const
{
	size_t found = 0;

	for (int i = 0; i < _size; i++)
	{
		if (_data[i] == value)
		{
			return(found);
		}
		found = found + 1;
	}

	return(found);
}


void Vector::reserve(size_t capacity)
{
	if (capacity > _capacity)
	{
		Value* tempArray = new Value[_capacity];

		for (int i = 0; i < _capacity; i++)
		{
			tempArray[i] = _data[i];
		}

		delete[] _data;
		_capacity = capacity;
		_data = new Value[_capacity];

		for (int j = 0; j < _size; j++)
		{
			_data[j] = tempArray[j];
		}

		delete[] tempArray;
	}
	else 
	{
		return;
	}
}

void Vector::shrinkToFit()
{
	_capacity = _size;
	Value* tempArray = new Value[_capacity];

	for (int i = 0; i < _capacity; i++)
	{
		tempArray[i] = _data[i];
	}

	delete[] _data;
	_data = new Value[_capacity];

	for (int j = 0; j < _capacity; j++)
	{
		_data[j] = tempArray[j];
	}

	delete[] tempArray;
}

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr)
{}

Value& Vector::Iterator::operator*()
{
	return (*_ptr);
}

const Value& Vector::Iterator::operator*() const
{
	return (*_ptr);
}

Value* Vector::Iterator::operator->()
{
	return (_ptr);
}

const Value* Vector::Iterator::operator->() const
{
	return (_ptr);
}

Vector::Iterator Vector::Iterator::operator++()
{
	_ptr = _ptr + 1;

	return(*this);
}

Vector::Iterator Vector::Iterator::operator++(int count)
{
	while (count != 0)
	{
		_ptr = _ptr + 1;
		count = count - 1;
	}

	return (*this);
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
	if (_ptr == other._ptr)
	{
		return true;
	}

	return false;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
	if (_ptr != other._ptr)
	{
		return true;
	}

	return false;
}

Vector::Iterator Vector::begin()
{
	Iterator begPos(&_data[0]);

	return (begPos);
}

Vector::Iterator Vector::end()
{
	Iterator endPos(&_data[_size]);

	return (endPos);
}

Vector::~Vector()
{
	delete[] _data;
	_size = 0;
	_capacity = 0;
	_multiplicativeCoef = 2.0f;
}
