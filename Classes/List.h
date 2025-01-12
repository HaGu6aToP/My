// ---------------------------------------------------------------------------

#ifndef ListH
#define ListH
#include <iostream>

namespace MyClasses {
	template<typename T>
	class List {
	private:

		class _Node {
		public:
			_Node* m_next; // ��������� �� ��������� ��-�
			_Node* m_prev; // ��������� �� ���������� ��-�
			T m_data; // �������� ��-��

			_Node(T data = T {}, _Node* prev = nullptr, _Node* next = nullptr): m_data {data}, m_prev {prev}, m_next {next} {
			}
		};

		_Node* m_first; // ��������� �� ������ ��-� ������
		_Node* m_last; // ��������� �� ��������� ��-� ������
		int m_size;

	public:

		class Iterator {
		private:
			_Node* m_current;

		public:
			Iterator() : m_current {
				nullptr
			} {
			}

			Iterator(_Node* first) : m_current {
				first
			} {
			}

			T& operator++() {
				m_current = m_current->m_next;
				return m_current;
			}

			T operator++(int) {
				_Node* temp {
					m_current
				};
				m_current = m_current->m_next;
				return temp->m_data;
			}

			T& operator--() {
				m_current = m_current->m_prev;
				return m_current;
			}

			T operator--(int) {
				_Node* temp {
					m_current
				};
				m_current = m_current->m_prev;
				return temp->m_data;
			}

			bool operator == (const Iterator& it) {
				return (m_current == it.m_current);
			}

			bool operator != (const Iterator& it) {
				return (m_current != it.m_current);
			}

			T& operator*() {
				return m_current->m_data;
			}

			Iterator& operator = (const Iterator & iter) {
				m_current = iter.m_current;
				return *this;
			}

		};

		List(): m_size {0}, m_first {nullptr}, m_last {nullptr} {}
		List(int len): List(){
			for (int i = 0; i < len; i++)
				pushBack(T{});
        }

		~List() {
			// �������� ��-���, ���� ������ �� ������ ������
			_Node* k {};
			if(m_size == 0)
                return;
			for (_Node * i = m_first; i != nullptr;) {
				k = i;
				i = i->m_next;
				delete k;
			}
		}

		void print() const {
			const _Node* t = m_first;

			while (t != m_last) {
				std::cout << t->m_data << ' ';
				t = t->m_next;
			}

			std::cout << t->m_data;

		}

		// ��������� ��-� � ����� ������
		void pushBack(const T& el) {
			if (!m_first) {
				m_first = new _Node {
					el
				};
				m_last = m_first;
			}
			else {
				m_last->m_next = new _Node {
					el, m_last
				};
				m_last = m_last->m_next;
			}

			m_last->m_next = nullptr;
			m_size++;

		}

		// ������ ��-� �� ����� ������
		void popBack() {
			if (m_last == nullptr)
				return;

			_Node* k {
			};

			k = m_last;
			m_last = m_last->m_prev;
			m_last->m_next = nullptr;
			delete k;

			m_size--;
		}

		// �������� ��-� � ������ ������
		void pushFront(const T& el) {
			if (m_first == nullptr) {
				m_first = new _Node {
					el
				};
				m_last = m_first;
			}
			else {
				m_first->m_prev = new _Node {
					el, nullptr, m_first
				};
				m_first = m_first->m_prev;
			}
			m_size++;
		}

		// ������� ��-� �� ������ ������
		void popFront() {
			if (m_first == nullptr)
				return;

			if (m_first == m_last) {
				delete m_first;
				m_first = nullptr;
				m_last = nullptr;

				m_size--;
				return;
			}

			_Node* k;

			k = m_first;
			m_first = m_first->m_next;
			m_first->m_prev = nullptr;
			delete k;
			m_size--;
		}

		Iterator begin() const {
			return m_first;
		}

		Iterator end() const {
			return nullptr;
		}

		// �������� i ��-��
		void remove(Iterator& i) {
			if (i == nullptr)
				return;

			if (i == static_cast<Iterator>(m_first))
				// ���� ��������� ��-� ������ � ������ ��� ������������
			{
				T temp {
					*i
				};
				popFront();

				i = m_first;
				return;
			}
			else if (i == static_cast<Iterator>(m_last))
				// ���� ��������� ��-� ��������� � ������
			{
				T temp {
					*i
				};
				popBack();
				i = nullptr;
				return;
			}

			T data {
				*i
			};
			_Node* temp {
				m_first
			};

			for (; static_cast<Iterator>(temp) != i; temp = temp->m_next);

			i = temp->m_next;
			temp->m_next->m_prev = temp->m_prev;
			temp->m_prev->m_next = temp->m_next;

			delete temp;
			m_size--;

			return;

		}

		void remove(int i) {
			if (i < 0)
				return;

			if (i == 0)
				// ���� ��������� ��-� ������ � ������ ��� ������������
			{
				popFront();
				return;
			}
			else if (i == m_size-1)
				// ���� ��������� ��-� ��������� � ������
			{
				popBack();
				return;
			}


			_Node* n {m_first};
			for(int j = 0; j < i; j++)
				n = n->m_next;

			n->m_prev->m_next = n->m_next;
			n->m_next->m_prev = n->m_prev;
			delete n;
            m_size--;

			return;

		}

		void clear() {
			while (m_size > 0)
				popFront();
		}

		int size() {
			return m_size;
		}

		T* toArray(){
			if (m_size == 0)
				return nullptr;

			T* res = new T[m_size];

			int counter = 0;
			for(auto i = begin(); i != end(); i++){
				res[counter] = *i;
				counter++;
			}

			return res;
		}
	};
}
#endif
