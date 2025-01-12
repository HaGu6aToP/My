//---------------------------------------------------------------------------

#ifndef BufferH
#define BufferH
#include <iostream>
namespace MyClasses
{
	template<typename T>
	class Buffer
	{
	private:
		int len_m;
		int ilen_m;
		T* arr_m;
	public:

		Buffer(int len):ilen_m(0)
		{
			if(len > 0)
			{
				len_m = len;
				arr_m = new T[len_m];
			}
		}

		//�������� ������� � �����
		void push(const T& item)
		{
			if(arr_m != nullptr && ilen_m < len_m)
			{
				ilen_m++;
				arr_m[ilen_m - 1] = item;
            }

        }

		//������� � ������� ��������� ����������� ��-�
		T pop(){ return arr_m[ilen_m-- - 1];}

		void clear() {ilen_m = 0;}

		void print()
		{
			for(int i = 0; i < ilen_m; ++i)
				std::cout << arr_m[i] << ' ';
			std::cout << '\n';
		}

		char* toStr()
		{
			char* res = new char[ilen_m + 1];

			for(int i = 0; i < ilen_m; ++i)
				res[i] = arr_m[i];
			res[ilen_m] = '\0';

			return res;
        }

		~Buffer() {delete[] arr_m;}

	};
}
#endif
