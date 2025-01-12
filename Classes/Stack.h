//---------------------------------------------------------------------------

#ifndef StackH
#define StackH
#include "List.h"
namespace MyClasses{
	template<typename T>
	class Stack{
		List<T> list;
	public:
		Stack(): list(){}

		void Clear(){
			list.clear();
		}

		void Push(const T& item){
			list.pushFront(item);
		}

		void Pop(){
			list.popFront();
		}

		T& Peek(){
			return *(list.begin());
		}

		void Print(){
			list.print();
		}

		int Len(){
            return list.size();
		}
	};
}
#endif
