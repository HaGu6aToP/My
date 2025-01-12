// ---------------------------------------------------------------------------

#ifndef TranslatorH
#define TranslatorH
#include "List.h"
#include "Buffer.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>

namespace MyClasses {
	int len(const char* const str);
	bool compare(char* s1, char* s2);
	void printString(char* str);
	void copyStr(char*& str, char* copyStr);
	void concatenateStr(char*& str1, const char* const str2);
	bool inStr(char c, const char* const str);
	bool isNumber(char c);
	bool isLetter(char c);
	const char* const RUSLETTERS = "�������������������������������������Ũ��������������������������";
	char* charToStr(char c);
	int wordInStr(const char* const word, const char* const str);


	class Error{
	public:
		Error();
		virtual char* getStr() const {return "";}
	};

	class FileError: public Error{
		char* FileName;
	public:
		FileError(char* filename): FileName{filename}{}
		char* getStr() const override;
	};

	class LexicalBlockError: public Error{
		int letter_num;
		char letter;
	public:
		LexicalBlockError(int n, char c): Error{}{}
		char* getStr() const override;
	};

	class SyntaxBlockError: public Error{
		char* s;
	public:
		SyntaxBlockError(char* ss): s(ss){}
		char* getStr() const override;
	};

	class �ompiler{
	/*
		1, �������������
		2, ����� �����
		3, if
		4, else
		5, ���
		6, �����
		7, (
		8, )
		9, ;
		10, ,
		11, :=
		12, +
		13, /
		14, >=
		15 ==
	*/
	public:
		class TableOfIdentifiers {
		public:
			friend class LexicalBlock;
			struct Identifier {
			public:
				char* Name;
				int* Attribute;
				int Type;

				Identifier();
				Identifier(char* name, int* attribute, int type);
				~Identifier();
			};

			List<Identifier*>table_m;
		public:


			TableOfIdentifiers();

			void append(char* name, int* attribute, int type);
			void remove(char* name);
			Identifier* get(char* name);
			Identifier* get(int num);
			int size(){return table_m.size();}
			const List<Identifier*>& toList();
			void clear();
			void print();

		public:
			List<Identifier*>::Iterator find(char* name);
		};

		class LexicalBlock {

			// ���������� �������
			static char DEFAULT_WHITESPACES[];

			static constexpr int MAXIDLEN = 10;

			// ����������� ������
			char* sourse_m;
			int currentChar_m;
			int len_m;

			static const char* KEYWORDS;

			//�����
			Buffer<char> buffer;
		public:

			LexicalBlock();
			LexicalBlock(char* sourse);
			void put(char* sourse);

			static void DoNothing() {
				std::cout << "Do nothing";
			}

			List<TableOfIdentifiers::Identifier*> work();
			TableOfIdentifiers::Identifier* getLexeme();

		private:

			//��������� ��������
			enum State{s, kw, se, op, id, it, f, err};

			//��� ��������
			TableOfIdentifiers::Identifier* step(State &t);
		};



		class SyntaxBlock{
		public:
			enum StoreSymbols{
				Start,
				Op,
				Assign, // :=
				Semicolon, // ;
				OpBracket, // (
				ClBracket, // )
				Id,
				Comma, // ,
				End, // �����
				Op_s,
				End2, // <End>
				E,
				E_list,
				T,
				T_list,
				F,
				Bool_expr,
				Bool_op,
				GOE, // >=
				EQ, // ==
				Stop,
				a_Assign, // {���������}
				a_Sum, // {�������}
				a_Div, // {���������}
				a_Condit0, // {���. �����. �� 0}
				a_GOE, // {������ ��� �����}
				a_EQ, // {�����}
				a_Label, // {�����}
				a_UnCondit, // {������. �����.}
				a_Inc, // {������. Id �� 1}
				a_CompTrans // {���. �� �����.}
			};


		public:
		class Slot{
			StoreSymbols m_symbol;
			int **m_attributes = nullptr;
			int m_attributesCount;
		public:
			Slot():m_symbol{}, m_attributesCount{0} {}
			Slot(StoreSymbols s, int attributesCount = 0);
			Slot(const Slot& item);

			int** getAttributes(){ return m_attributes; }
			StoreSymbols getSymbol(){ return m_symbol; }
			int attributesCount(){ return m_attributesCount; }
			~Slot();

//			Slot& operator=(const Slot& item);
		};

		public:
		// ������� ���������������
			TableOfIdentifiers id_table_s;
			TableOfIdentifiers int_table_s;

		public:
			const int N;
			const int M;
			int *data[2];
			int *labels[2];

			SyntaxBlock(int n = 100, int m = 100);
			~SyntaxBlock();

			int* allocMem();
			bool freeMem(int* i);

			int* allocLabel();
			bool freeLabel(int* i);

			List<Slot> work(char* FileName);
			List<Slot> WorkWithSourse(char* sourse);
			void Interpreter(Slot* commands);
		private:
			static MyClasses::Stack<Slot> store;
			void step(TableOfIdentifiers::Identifier*& input, List<Slot>& res);
		};



	};


}
#endif
