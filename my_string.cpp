// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}

//   rule of "3"
//     my_string copy constructor
my_string::my_string(const my_string& other)
: _data(new char[other._capacity]), _capacity(other._capacity), _size(other._size)
{
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = other._data[i];
	}
}
//     my_string copy assignment
my_string& my_string::operator=(const my_string& rhs) {
	if (this != &rhs) {
		delete [] _data;
		_capacity = rhs.capacity();
		_size = rhs.size();
		_data = new char[_capacity];
		
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = rhs._data[i];
		}
	}

	return *this;
}
//     destructor
my_string::~my_string() {
	delete [] _data;
}
//   c-string copy constructor
my_string::my_string(const char* other)
:_data(new char[1]), _capacity(1), _size(0)
{
	size_t j = 0;
	size_t size = 0;
	while (other[j] != '\0') {
		++size;
		++j;
	}
	
	_size = size;
	_capacity = size + 1;
	_data = new char[_capacity];
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = other[i];
	}
}

// element access
//   at
const char& my_string::front() const {
	return _data[0];
}

char& my_string::front() {
	return _data[0];
}

//   front
const char& my_string::at(size_type index) const {
	return _data[index];
}

char& my_string::at(size_type index) {
	return _data[index];
}

//   operator[]
const char& my_string::operator[](size_t index) const {
	return _data[index];
}

char& my_string::operator[](size_t index) {
	return _data[index];
}

// capacity
//   empty
bool my_string::empty() const {
	if (_size == 0) {
		return true;
	}
	return false;
}
//   size
size_t my_string::size() const {
	return _size;
}

size_t my_string::capacity() const { 
	return _capacity;
}

// operations
//   concatenation
//     my_string + my_string (non-member, friend)
my_string operator+(my_string lhs, const my_string& rhs) {
	my_string totalString(lhs);
	totalString += rhs;
	
	return totalString;
}
//     my_string + c-string (non-member, friend)
my_string operator+(my_string lhs, const char* rhs) {
	my_string totalString(lhs);
	totalString += rhs;
	
	return totalString;
}
//     my_string + char (non-member, friend)
my_string operator+(my_string lhs, char rhs) {
	char* RHS = new char[1 + lhs._capacity];
	RHS[lhs.size()] = rhs;
	RHS[lhs._capacity] = '\0';
	
	for (size_t i = 0; i < lhs._size; ++i) {
		RHS[i] = lhs[i];
	}
	
	my_string totalString(RHS);
	
	delete [] RHS;
	
	return totalString;
}
//     c-string + my_string (non-member, friend)
my_string operator+(const char* lhs, const my_string& rhs) {
	my_string totalString;
	my_string newLHS(lhs);
	
	totalString = newLHS + rhs;
	
	return totalString;
}
//     char + my_string (non-member, friend)
my_string operator+(char lhs, my_string rhs) {
	char* LHS = new char[1 + rhs._capacity];
	LHS[0] = lhs;
	LHS[rhs._capacity] = '\0';
	
	for (size_t i = 0; i < rhs._size; ++i) {
		LHS[i + 1] = rhs[i];
	}
	
	my_string totalString(LHS);
	
	delete [] LHS;
	
	return totalString;
}
//     my_string += my_string
my_string& my_string::operator+=(const my_string& rhs) {
	*this += rhs._data;
	
	return *this;
}

//     my_string += c-string
my_string& my_string::operator+=(const char* rhs) {
	size_t j = 0;
	size_t csize = 0;
	while (rhs[j] != '\0') {
		++csize;
		++j;
	}
	
	char currChar;
	
	for (size_t i = 0; i < csize; ++i) {
		currChar = rhs[i];
		*this += currChar;
	}
	
	return *this;
}

//     my_string += char
my_string& my_string::operator+=(const char rhs) {
	if (_size + 2 <= _capacity) {
		_data[_size] = rhs;
		++_size;
	} else {
		char* temp = new char[_size + 2];
		for (size_t i = 0; i < _size; ++i) {
			temp[i] = _data[i];
		}
		delete [] _data;
		
		_capacity = _size + 2;
		_data = new char[_capacity];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = temp[i];
		}
		
		_data[_size] = rhs;
		++_size;
		
		delete [] temp;
	}
	return *this;
}

// search
//   find
size_t my_string::find(const my_string& str, size_t pos) const {
	if (pos >= _size - str._size) {
		return - 1;
	}
	
	for (size_t i = pos; i < _size - str._size; ++i) {
		bool equalString = true;
		char* temp = new char[str._capacity];
		
		for (size_t j = i; j < i + str._size; ++j) {
			temp[j] = _data[j];
		}
		
		if (temp != str._data) {
			equalString = false;
		}
		
		if (equalString) {
			return i;
		}
	}
	
	return -1;
}

// non-member functions
//   relational operators
//     my_string == my_string
bool operator==(const my_string& lhs, const my_string& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	} else {
		for (size_t i = 0; i < rhs.size(); ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}
}
//     my_string == c-string
bool operator==(const my_string& lhs, const char* rhs) {
	my_string newRHS(rhs);
	
	return (lhs == newRHS);
}

//     my_string != my_string
bool operator!=(const my_string& lhs, const my_string& rhs) {
	if (lhs.size() != rhs.size()) {
		return true;
	} else {
		for (size_t i = 0; i < rhs.size(); ++i) {
			if (lhs[i] != rhs[i]) {
				return true;
			}
		}
		return false;
	}
}

//     my_string != c-string
bool operator!=(const my_string& lhs, const char* rhs) {
	my_string newRHS(rhs);
	
	return (lhs != newRHS);
}

//   stream operators
//     ostream instertion operator
std::ostream& operator<<(std::ostream& os, const my_string& str) {
	for (size_t i = 0; i < str.size(); ++i) {
		os << str[i];
	}
	
	return os;
}
//     istream extraction operator
std::istream& operator>>(std::istream& os, my_string& str) {
	char* temp = new char[1000];
	size_t i = 0;
	char nextChar;
	size_t j = 0;
	
	while (nextChar != os.eof()) {
		os >> temp[i];
		nextChar = os.peek();
		
		if (nextChar == ' ') {
			break;
		}
		++i;
	}
	
	for (j = 0; j < i; ++j) {
		str += temp[j];
	}

	return os;
}

//     getline
std::istream& getline(std::istream& is, my_string& str, char delim) {
	char currChar;
	is >> currChar;
	
	while (currChar != delim) {
		str += currChar;
		is >> currChar;
	}
	
	return is;
}

my_string& my_string::erase(size_t pos, size_t len) {
	for (size_t i = pos; i < pos + len; ++i) {
		for (size_t j = pos; j < _size - 1; ++j) {
			_data[j] = _data[j + 1];
		}
		_data[_size - 1] = '\0';
		--_size;
		--_capacity;
	}
	
	return *this;
}

//   numeric conversions
//     to_string
my_string to_string(int val) {
	int currVal = 0;
	char currChar;
	my_string stringVal;
	
	if (val > 0) {
		while (val > 0) {
			currVal = val % 10;
			
			if (currVal == 0) {
				currChar = '0';
			} else if (currVal == 1) {
				currChar = '1';
			} else if (currVal == 2) {
				currChar = '2';
			} else if (currVal == 3) {
				currChar = '3';
			} else if (currVal == 4) {
				currChar = '4';
			} else if (currVal == 5) {
				currChar = '5';
			} else if (currVal == 6) {
				currChar = '6';
			} else if (currVal == 7) {
				currChar = '7';
			} else if (currVal == 8) {
				currChar = '8';
			} else {
				currChar = '9';
			}
			
			stringVal = currChar + stringVal;
			val /= 10;
		}
	} else {
		val *= -1;
		while (val > 0) {
			currVal = val % 10;
			
			if (currVal == 0) {
				currChar = '0';
			} else if (currVal == 1) {
				currChar = '1';
			} else if (currVal == 2) {
				currChar = '2';
			} else if (currVal == 3) {
				currChar = '3';
			} else if (currVal == 4) {
				currChar = '4';
			} else if (currVal == 5) {
				currChar = '5';
			} else if (currVal == 6) {
				currChar = '6';
			} else if (currVal == 7) {
				currChar = '7';
			} else if (currVal == 8) {
				currChar = '8';
			} else {
				currChar = '9';
			}
			
			stringVal = currChar + stringVal;
			val /= 10;
		}
		stringVal = '-' + stringVal;
	}
	return stringVal;
}

// my_istringstream methods

/* my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
 */