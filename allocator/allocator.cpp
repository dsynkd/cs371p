#include <cassert>
#include <cstddef>
#include <new>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

template <typename T, std::size_t N>
class my_allocator {
private:
	char a[N]; // defined as char array to be byte iterable
public:
	class iterator {
	private:
		int* _p;
	public:
		iterator (int* p) {
			_p = p;
		}
		friend bool operator == (const iterator& lhs, const iterator& rhs) {
			return *lhs == *rhs;
		}
		friend bool operator != (const iterator& lhs, const iterator& rhs) {
			return !(lhs == rhs);
		}
		int& operator * () const {
			return *_p;
		}
		iterator& operator + (int a) {
			_p = (int*)(((char*)_p) + a);
			return *this;
		}
		iterator& next (int a) {
			if(a == 0)
				a = sizeof(int);
			_p = (int*)(((char*)_p) + a);
			return *this;
		}
		iterator& prev (int a) {
			if(a == 0)
				a = sizeof(int);
			_p = (int*)(((char*)_p) - a);
			return *this;
		}
		iterator& operator ++ () {
			_p = (int*)(((char*)_p) + 2*sizeof(int) + abs(*_p));
			return *this;
		}
		iterator operator ++ (int) {
			iterator x = *this;
			++*this;
			return x;
		}
		iterator& operator -- () {
			this->prev(sizeof(int));
			_p = (int*)(((char*)_p) - sizeof(int) - abs(*_p));
			return *this;
		}
		iterator operator -- (int) {
			iterator x = *this;
			--*this;
			return x;
		}
	};

	my_allocator () {
		if(N < sizeof(T) + 2*sizeof(int))
			throw bad_alloc();
		int si = sizeof(int);
		int sentinel = N - 2*si;
		*reinterpret_cast<int*>(a) = sentinel;
		*reinterpret_cast<int*>(&a[N - si]) = sentinel;
	}

	my_allocator (const my_allocator&) = default;
	~my_allocator()	= default;
	my_allocator& operator = (const my_allocator&) = default;

	T* allocate (size_t n) {
		// <your code>
		int bytes_allocate = (n * sizeof(T) + sizeof(T));
		
		auto i = this->begin();
		auto e = this->end();
		int block_size_required = n * sizeof(T);
		while(*i < block_size_required && i != e)
			++i;
		if(i == e)
			throw bad_alloc();

		int busy_sentinel = -1 * n * sizeof(T);
		int free_sentinel = *i + busy_sentinel - 2*sizeof(int);
		if(free_sentinel == 0)
			busy_sentinel -= sizeof(T);

		*i = busy_sentinel;
		i.next((abs(busy_sentinel) + sizeof(int)));
		*i = busy_sentinel;
		i.next(sizeof(int));

		if(free_sentinel > 0) {
			*i = free_sentinel;
			i.next(free_sentinel + sizeof(int));
			*i = free_sentinel;
		}

		return nullptr;}

	void construct (T* p, T& v) {
		new (p) T(v);
	}

	void deallocate (int a) {
		iterator i = this->begin();
		iterator e = this->end();

		// find block that needs to be deallocated
		while(a < 0 && i != this->end()) {
			while(*i >= 0)
				++i;
			++a;
			if(a < 0)
				++i;
		}

		*i *= -1;
		++i;
		i.prev(sizeof(int));
		*i *= -1;
		i.next(sizeof(int));
		iterator ir = i;
		iterator il = --i;

		if(&(*il) != &(*this->begin())) {
			int* s1 = &(*il);
			il.prev(sizeof(int));
			int* s2 = &(*il);
			if(*s1 >= 0 && *s2 >= 0) {
				int sentinel = *s1 + *s2 + 2*sizeof(int);
				il.prev(*il + sizeof(int));
				*il = sentinel;
				++il;
				il.prev(sizeof(int));
				*il = sentinel;
				il.next(sizeof(int));
			}
			else {
				il.next(sizeof(int));
			}
		}
		
		if(&(*ir) != &(*this->end())) {
			int* s1 = &(*ir);
			ir.prev(sizeof(int));
			int* s2 = &(*ir);
			if(*s1 >= 0 && *s2 >= 0) {
				int sentinel = *s1 + *s2 + 2*sizeof(int);
				ir.prev(*ir + sizeof(int));
				*ir = sentinel;
				++ir;
				ir.prev(sizeof(int));
				*ir = sentinel;
				ir.next(sizeof(int));
			}
			else {
				ir.next(sizeof(int));
			}
		}
	}

	void destroy (T* p) {
		p->~T();
	}

	int& operator [] (int i) {
		return *reinterpret_cast<int*>(&a[i]);
	}

	const int& operator [] (int i) const {
		return *reinterpret_cast<const int*>(&a[i]);}

	iterator begin () {
		return iterator(reinterpret_cast<int*>(&a[0]));
	}

	iterator end () {
		return iterator(reinterpret_cast<int*>(&a[N]));
	}
};

int main() {
	string line;
	getline(cin, line);
	int c = stoi(line, nullptr);
	getline(cin, line);
	while(c-->0) {
		my_allocator<double, 1000> m;
		auto i = m.begin();
		getline(cin, line);
		while(!line.empty()) {
			int a = stoi(line, nullptr);
			if(a < 0)
				m.deallocate(a);
			else
				double* tmp = m.allocate(a);
			getline(cin, line);
		}
		auto t = m.begin();
		auto e = m.end();
		while(t != e) {
			cout << *t;
			++t;
			if(t != e)
				cout << " ";
		}
		cout << endl;
	}
}
