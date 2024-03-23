//---------------------------------------------------------------------------

#pragma hdrstop

#include "stdlib.h"
#include "Translator.h"
using MyClasses::Сompiler;
using MyClasses::List;


void MyClasses::printString(char* str){
	for(int i = 0; str[i] != '\0'; ++i)
	std::cout << str[i] << ' ';
	std::cout << '\n';
}

void MyClasses::copyStr(char*& str, char* copyStr){
	int len = 0;
	for (len; copyStr[len] != '\0'; len++);
	str = new char[len+1];
	for(int i = 0; i < len; i++)
		str[i] = copyStr[i];
	str[len] = '\0';

}

void MyClasses::concatenateStr(char*& str1, const char* const str2)
{
	int len1 = 0;
	int len2 = 0;

	if (str2 == nullptr)
		return;

	if (str1 != nullptr)
		 for (len1; str1[len1] != '\0'; len1++);

	for (len2; str2[len2] != '\0'; len2++);

	char* s = new char[len1 + len2 + 1];
	for(int i = 0; i < len1; i++)
		s[i] = str1[i];
	for(int i = len1; i < len1+len2; i++)
		s[i] = str2[i-len1];
	s[len1+len2] = '\0';
//	delete[] str1;
	str1 = s;
}

bool MyClasses::inStr(char c, const char* const str){
	if (str == nullptr)
		return false;

	for(int i = 0; str[i] != '\0'; i++)
		if (c == str[i])
			return true;

	return false;
}

bool MyClasses::isNumber(char c){
	int a = static_cast<int>(c);
	if (a >= 48 && a <= 57)
		return true;
    return false;
}

bool MyClasses::isLetter(char c){
	int a = static_cast<int>(c);
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122) || (inStr(c, MyClasses::RUSLETTERS)))
		return true;
	return false;
}

char* MyClasses::charToStr(char c){
	char* str = new char[2];
	str[0] = c;
	str[1] = '\0';
	return str;
}

Сompiler::TableOfIdentifiers::TableOfIdentifiers():  table_m(){}

Сompiler::TableOfIdentifiers::Identifier::Identifier(): Attribute{0}, Name{nullptr}, Type{0}{}

Сompiler::TableOfIdentifiers::Identifier::Identifier(char* name, int* attribute, int l): Attribute(attribute), Type(l){
	int len = MyClasses::len(name);
	Name = new char [len + 1];

	for (int i = 0; name[i] != '\0'; i++)
		Name[i] = name[i];

	Name[len] = '\0';
}

Сompiler::TableOfIdentifiers::Identifier::~Identifier(){ delete[] Name; delete Attribute;}

int MyClasses::len(const char* const str){
	int res = 0;

	for (int i = 0; str[i] != '\0'; i++) res++;

	return res;
}

bool MyClasses::compare(char* s1, char* s2){
	int l1 = MyClasses::len(s1);
	int l2 = MyClasses::len(s2);

	if (l1 != l2) return false;

	for (int i = 0; s1[i] != '\0'; i++)
		if (s1[i] != s2[i]) return false;

	return true;
}

int MyClasses::wordInStr(const char* const word, const char* const str){
	if (MyClasses::len(word) == 1)
        return -1;

	int i = 0;
	int j = 0;
	int k = 0;
	bool flag = false;

	if (str == nullptr || word == nullptr) {return false;}
	else if (word[i] == '\0') {return false; }

	for(j; str[j] != '\0'; j++){
		
		if(word[i] == str[j])
			flag = true;
		else{
			flag = false;
			i = 0;
		}

		if (str[j] == ' ')
			k++;

		if (flag) {i++;}

        if (i == MyClasses::len(word)) {return k;}
	}

	return -1;
}

List<Сompiler::TableOfIdentifiers::Identifier*>::Iterator Сompiler::TableOfIdentifiers::find(char* name){
	List<TableOfIdentifiers::Identifier*>::Iterator res{};

	for(auto i = table_m.begin(); i != table_m.end(); i++)
		if (compare((*i)->Name, name)){
			res = i;
			break;
		}

	return res;
}


Сompiler::TableOfIdentifiers::Identifier* Сompiler::TableOfIdentifiers::get(char* name){
	if (name == nullptr)
		return nullptr;

	auto res = find(name);
	return (res == nullptr)? nullptr: *res;
}

void Сompiler::TableOfIdentifiers::append(char* name, int* attribute, int l){
	if (TableOfIdentifiers::find(name) == nullptr){
		TableOfIdentifiers::Identifier* f = new TableOfIdentifiers::Identifier (name, attribute, l);
		table_m.pushBack(f);
	}
}


void Сompiler::TableOfIdentifiers::remove(char* name){
	if (table_m.size() == 0) return;
	auto i = find(name);
	table_m.remove(i);
}

void Сompiler::TableOfIdentifiers::clear(){ table_m.clear();}

void Сompiler::TableOfIdentifiers::print(){
	for(auto i = table_m.begin(); i != table_m.end(); i++)
		std::cout << (*i)->Name << ' ' << (*i)->Attribute << "\n";
}

const List<Сompiler::TableOfIdentifiers::Identifier*>& Сompiler::TableOfIdentifiers::toList(){return table_m;}



char Сompiler::LexicalBlock::DEFAULT_WHITESPACES[] {" \n\r\t"};
const char* Сompiler::LexicalBlock::KEYWORDS {"if else ДЛЯ КОНЕЦ"};

Сompiler::LexicalBlock::LexicalBlock(): buffer(MAXIDLEN), sourse_m(nullptr), currentChar_m(0){}

Сompiler::LexicalBlock::LexicalBlock(char* sourse): LexicalBlock(){
	copyStr(sourse_m ,sourse);
	len_m = MyClasses::len(sourse);
}

void Сompiler::LexicalBlock::put(char* sourse){
	copyStr(sourse_m ,sourse);
	len_m = MyClasses::len(sourse);
}

//List<Сompiler::TableOfIdentifiers::Identifier*> Сompiler::LexicalBlock::work(){
//	TableOfIdentifiers::Identifier* item;
//	List<TableOfIdentifiers::Identifier*> list{};
//
//	while ((item = getLexeme()) != nullptr){
//		if (item->Type == 1)
//		{
//			if(id_table_s.find(item->Name) == nullptr)
//				id_table_s.append(item->Name, id_table_s.size(), 1);
//		}
//		else if (item->Type == 2)
//		{
//			if(id_table_s.find(item->Name) == nullptr)
//				int_table_s.append(item->Name, int_table_s.size(), 2);
//		}
//
//		list.pushBack(item);
//	}
//
//	return list;
//}


MyClasses::Error::Error(){}

char* MyClasses::LexicalBlockError::getStr() const{
	std::string s("Лексическая Ошибка! Последний прочитанный символ ");
	s += letter;
	s += '(';
	s += std::to_string(letter_num);
	s += ").\n";
	char* res = new char[s.length() + 1];
	strcpy(res, s.c_str());
	return res;
}

char* MyClasses::FileError::getStr() const{
	std::string s("Не удалось отркыть файл ");
	s += FileName;
	s += '\n';
	char* res = new char[s.length() + 1];
	strcpy(res, s.c_str());
	return res;
}

char* MyClasses::SyntaxBlockError::getStr() const{
	return s;
}


Сompiler::TableOfIdentifiers::Identifier* Сompiler::LexicalBlock::getLexeme(){
	State T = State::s;

	if (currentChar_m == len_m) {return nullptr;}

	TableOfIdentifiers::Identifier* N = nullptr;
	do{

		N = step(T);

		if (T == State::err) {
			throw MyClasses::LexicalBlockError(currentChar_m - 1, buffer.pop());
		}

		if (N == nullptr)
			currentChar_m++;
		else{
			if (T == op || T == se) currentChar_m++;
			return N;
		}

	}while ((T != State::f && N == nullptr) || currentChar_m == len_m);

    delete N;
    return nullptr;
}

Сompiler::TableOfIdentifiers::Identifier* Сompiler::LexicalBlock::step(Сompiler::LexicalBlock::State& T)
{
	 char c = sourse_m[currentChar_m];
	 switch(T)
	 {
		case State::s:
			if (MyClasses::inStr(c, DEFAULT_WHITESPACES))
				break;
			if(c == '^' || c == '\0'){
				T = State::f;
				return nullptr;
			}


			if (c == '+' || c == '/'){
				T = State::op;
				int type = 0;
				if (c == '+') type = 12;
				if (c == '/') type = 13;
				TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(charToStr(c), nullptr, type);
				return obj;
			}


			if(c == '(' || c == ')' || c == ';' || c == ','){
				T = State::se;
                int type = 0;
				if (c == '(') type = 7;
				if (c == ')') type = 8;
				if (c == ';') type = 9;
				if (c == ',') type = 10;
				TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(charToStr(c), nullptr, type);
				return obj;
			}


			buffer.push(c);
			if (c == ':' || c == '>' || c == '='){
				T = State::op;
				break;
			}

			if(MyClasses::isLetter(c)){
				T = State::id;
				break;
			}

			if(MyClasses::isNumber(c)){
				T = State::it;
				break;
			}


			T = State::err;
			return nullptr;
		case State::id:
			//Если соблюдается правило построения идентификатора
			if (MyClasses::isLetter(c) || MyClasses::isNumber(c)){
				buffer.push(c);
				break;
			}
			else
			{
				if (MyClasses::isNumber(c)) {
				   T = State::err;
				   return nullptr;
				}
				char* name = buffer.toStr();
				int t = MyClasses::wordInStr(name, KEYWORDS);
				//Если найдено ключевое слово
				if (t != -1)
				{
					buffer.clear();
					T = State::kw;
					TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(name, nullptr, 3+t);
					delete[] name;
					return obj;
				}
				//Если это идентификатор
				else{

					buffer.clear();

					TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(name, nullptr, 1);
					delete[] name;
					return obj;
				}

			}
		case State::op:
			if (c == '='){
				buffer.push(c);
				char* name = buffer.toStr();
				int type = 0;

				if (name[0] == ':') type = 11;
				if (name[0] == '=') type = 15;
				if (name[0] == '>') type = 14;

				TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(name, nullptr, type);

				buffer.clear();
				delete[] name;
				return obj;
			}
		case State::it:
			//Если соблюдается правило построения числовой константы
			if (MyClasses::isNumber(c)){
				buffer.push(c);
				break;
			}
			else
			{
				if (MyClasses::isLetter(c)) {
					T = State::err;
					return nullptr;
				}
				char* name = buffer.toStr();

				buffer.clear();

				TableOfIdentifiers::Identifier* obj = new TableOfIdentifiers::Identifier(name, nullptr, 2);
				delete[] name;
				return obj;
			}
	 }
	 return nullptr;
}

MyClasses::Stack<Сompiler::SyntaxBlock::Slot> Сompiler::SyntaxBlock::store {};


MyClasses::List<Сompiler::SyntaxBlock::Slot> Сompiler::SyntaxBlock::WorkWithSourse(char* sourse){
	store.Clear();
	store.Push(Slot{StoreSymbols::Stop});
	store.Push(Slot{StoreSymbols::Start});

	LexicalBlock L(sourse);
	TableOfIdentifiers::Identifier* lexeme = nullptr;
	List<Slot> res;

	do{
		if (lexeme == nullptr)
			lexeme = L.getLexeme();
		step(lexeme, res);
	}while (store.Peek().getSymbol() != StoreSymbols::Stop || lexeme != nullptr);
    res.pushBack(Slot{StoreSymbols::Stop});
	return res;
}


MyClasses::List<Сompiler::SyntaxBlock::Slot> Сompiler::SyntaxBlock::work(char* FileName){

	store.Clear();
	store.Push(Slot{StoreSymbols::Stop});
	store.Push(Slot{StoreSymbols::Start});

	std::string str;
	char* s = "";
	ifstream in(FileName);

	if (in.is_open())
	{
		while (std::getline(in, str))
		{
//			std::cout << str << std::endl;
			MyClasses::concatenateStr(s, str.c_str());
		}
	}
	else
		throw MyClasses::FileError(FileName);

	LexicalBlock L(s);
	TableOfIdentifiers::Identifier* lexeme = nullptr;
	List<Slot> res;

	do{
		if (lexeme == nullptr)
			lexeme = L.getLexeme();

        id_table_s.print();
		step(lexeme, res);
	}while (store.Peek().getSymbol() != StoreSymbols::Stop || lexeme != nullptr);

	int k = 1;
	res.pushBack(Slot{StoreSymbols::Stop});
	return res;
}

void generateExc(std::string s){
   s += '\n';
   char* res = new char[s.length() + 1];
   strcpy(res, s.c_str());
   throw MyClasses::SyntaxBlockError(res);
}

void Сompiler::SyntaxBlock::step(TableOfIdentifiers::Identifier*& input, List<Slot>& res){
	Slot& sl = store.Peek();
	StoreSymbols symbol;
	symbol = sl.getSymbol();
	int **attributes = nullptr;



	if (input == nullptr){

		if(symbol != StoreSymbols::End && symbol != StoreSymbols::End2 && symbol != StoreSymbols::Start && symbol != StoreSymbols::Op_s && symbol != StoreSymbols::a_Label && symbol != StoreSymbols::a_UnCondit  && store.Len() != 0){
				std::string s;

				switch(symbol){
					case Op:
						s += "Синтаксическая ошибка. Ожидался оператор.";
						break;
					case Assign:
						s += "Синтаксическая ошибка. Ожидалось ':='";
						break;
					case Semicolon:
						s += "Синтаксическая ошибка. Ожидалось ';'";
						break;
					case OpBracket:
						s += "Синтаксическая ошибка. Ожидалось '('";
						break;
					case ClBracket:
						s += "Синтаксическая ошибка. Ожидалось '('";
						break;
					case Id:
						s += "Синтаксическая ошибка. Ожидался идентификатор";
						break;
					case Comma:
						s += "Синтаксическая ошибка. Ожидалось ','";
						break;
					case End:
						s += "Синтаксическая ошибка. Ожидалось 'Конец'";
						break;
					case End2:
						 s += "Синтаксическая ошибка. Ожидалось 'End'";
						 break;
					case E:
					case E_list:
					case T:
					case T_list:
						s += "Синтаксическая ошибка. Ожидалось арифметическое выражение";
						break;
					case F:
						s += "Синтаксическая ошибка. Ожидался идентификатор или целое цисло";
						break;
					case Bool_expr:
						s += "Синтаксическая ошибка. Ожидалось логическое выражение";
						break;
					case Bool_op:
						s += "Синтаксическая ошибка. Ожидалcя логический оператор";
						break;
				}

				generateExc(s);

			}
			else if(symbol == StoreSymbols::Start){
				std::string s;
				s = "Пустая программа";
				generateExc(s);
			}
			else{
//				if (sl.getSymbol() == StoreSymbols::a_Label || sl.getSymbol() == StoreSymbols::End2){
//                    res.pushBack(sl);
//					*(sl.getAttributes()[0]) = res.size();
//					std::cout << "Метка(" << *(sl.getAttributes()[0]) << ")\n";
//				}
//				store.Pop();
//				return;
				if (symbol == StoreSymbols::End2){
//					res.pushBack(sl);
					*(sl.getAttributes()[0]) = res.size();
					std::cout << "Метка(" << *(sl.getAttributes()[0]) << ")\n";
					store.Pop();
					return;
				}
				else if(symbol == StoreSymbols::Op_s){
					store.Pop();
                    return;
				}
			}
	}

//	symbol = store.Peek();

	if (symbol == StoreSymbols::Stop){
		std::string s = "Синтаксическая ошибка. Ожидался конец программы";
		generateExc(s);
	}

	std::string s;
	switch(symbol){
		case Start:
			if (input->Type == 1 || input->Type == 3 || input->Type == 5){

				store.Pop();
				store.Push(StoreSymbols::Op_s);
				store.Push(StoreSymbols::Op);

				return;
			}
			else{
				s = "Синтаксическая ошибка. Встречена неожиданная лексема - ";
				s += input->Name;
				generateExc(s);
			}
		case a_Assign:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
//			attributes = sl.getAttributes();
//			std::cout << "Присвоить(" << *attributes[0] << ", " << *attributes[1] << ")\n";
//			*attributes[0] = *attributes[1];
			// Вытолк
			store.Pop();
			return;
		}
		case a_Sum:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
			int* r1 = sl.getAttributes()[2];
//			std::cout << "Сложить(" << *attributes[0] << ", " << *attributes[1] << ", " << *attributes[2] << ")\n";
//			*attributes[2] =  *attributes[0] + *attributes[1];
//			int* r1 = attributes[2];
			// Вытолк
			store.Pop();
			sl = store.Peek();
			if (sl.getSymbol() == StoreSymbols::E_list)
				sl.getAttributes()[0] = r1;
			return;
		}
		case a_Div:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
			int* r1 = sl.getAttributes()[2];
//			std::cout << "Разделить(" << *attributes[0] << ", " << *attributes[1] << ", " << *attributes[2] << ")\n";
//			*attributes[2] =  *attributes[0] / *attributes[1];
//			int* r1 = attributes[2];
			// Вытолк
			store.Pop();
			sl = store.Peek();
			if (sl.getSymbol() == StoreSymbols::T_list)
				sl.getAttributes()[0] = r1;
			return;
		}
		case a_GOE:{
			sl = store.Peek();
			int* r1 = sl.getAttributes()[2];
			// Выдать
			res.pushBack(sl);

//			std::cout << attributes[0] << ' ' << attributes[1] << ' ' << attributes[2] << '\n';
//			std::cout << "БольшеИлиРавно(" << *attributes[0] << ", " << *attributes[1] << ", " << *attributes[2] << ")\n";
//			*attributes[2] =  (*attributes[0] >= *attributes[1]);
//			int* r1 = attributes[2];
			// Вытолк
			store.Pop();
			sl = store.Peek();
			if (sl.getSymbol() == StoreSymbols::a_Condit0)
				sl.getAttributes()[0] = r1;
			return;
		}
		case a_EQ:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
			int* r1 = sl.getAttributes()[2];
//			std::cout << "Равно(" << *attributes[0] << ", " << *attributes[1] << ", " << *attributes[2] << ")\n";
//			*attributes[2] =  (*attributes[0] == *attributes[1]);
//			int* r1 = attributes[2];
			// Вытолк
			store.Pop();
			sl = store.Peek();
			if (sl.getSymbol() == StoreSymbols::a_Condit0)
				sl.getAttributes()[0] = r1;
			return;
		}
		case a_Condit0:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
//			attributes = sl.getAttributes();
//			std::cout << "Усл. переход по 0(" << *attributes[0] << ", " << *attributes[1] << ")\n";
			// Вытолк
			store.Pop();
			return;
		}
		case a_Label:{
			sl = store.Peek();
			attributes = sl.getAttributes();
			(*attributes[0]) = res.size();
//			std::cout << "Метка(" << *attributes[0]<< ")\n";
			// Вытолк
			store.Pop();
			return;
		}
		case a_UnCondit:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
//			attributes = sl.getAttributes();
//			std::cout << "Безусл. перех.(" << *attributes[0]<< ")\n";
			// Вытолк
			store.Pop();
			return;
		}
		case a_CompTrans:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
//			attributes = sl.getAttributes();
//			std::cout << "Пер. по сравн.(" << *attributes[0] << ", " << *attributes[1] << ", " << *attributes[2] << ")\n";
			// Вытолк
			store.Pop();
			return;
		}
		case a_Inc:{
			sl = store.Peek();
			// Выдать
			res.pushBack(sl);
//			attributes = sl.getAttributes();
//			std::cout << "Увел Id на 1(" << *attributes[0]<< ")\n";
			// Вытолк
			store.Pop();
			return;
		}
		case Op_s:
			if(input->Type == 1 || input->Type == 3 || input->Type == 5){
				// Замена <Op_s>-><Op><Op_s>
				store.Push(Slot{StoreSymbols::Op});
				return;
			}
			if(input->Type == 6){
				// Вытолк
				store.Pop();
				return;
			}

            s = "Неизвестный оператор";
			generateExc(s);

		case Op:
			if(input->Type == 1){
				int* p1;
				if (id_table_s.find(input->Name) == nullptr){
					p1 = allocMem();
					id_table_s.append(input->Name, p1, 1);
				}
				else
					p1 = id_table_s.get(input->Name)->Attribute;

				// Замена
				store.Pop();
                store.Push(Slot{StoreSymbols::Semicolon});
				Slot slot = Slot{StoreSymbols::a_Assign, 2};
				slot.getAttributes()[0] = p1;
				store.Push(slot);
				slot = Slot{StoreSymbols::E, 1};
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Assign});


				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}
			else if(input->Type == 3){
				// Замена
				store.Pop();
				int* z1 = allocLabel();
				Slot slot;
				slot = Slot{StoreSymbols::End2, 1};
				slot.getAttributes()[0] = z1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Op});
                store.Push(Slot{StoreSymbols::ClBracket});
				slot = Slot{StoreSymbols::a_Condit0, 2};
				slot.getAttributes()[1] = z1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Bool_expr, 1});
				store.Push(Slot{StoreSymbols::OpBracket});
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}
			else if(input->Type == 5){
				//Замена
				store.Pop();
				int* w1 = allocLabel();
				int* z1 = allocLabel();
				int* p1 = allocMem();
				int* x1 = allocMem();
				Slot slot{StoreSymbols::a_Label, 1};
				slot.getAttributes()[0] = z1;
				store.Push(slot);
				slot = Slot{StoreSymbols::a_UnCondit, 1};
				slot.getAttributes()[0] = w1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::End});
				slot = Slot{StoreSymbols::a_Inc, 1};
				slot.getAttributes()[0] = p1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Op_s});
				store.Push(Slot{StoreSymbols::ClBracket});
				slot = Slot{StoreSymbols::a_CompTrans, 3};
				attributes = slot.getAttributes();
				attributes[0] = p1;
				attributes[1] = x1;
				attributes[2] = z1;
				store.Push(slot);
				slot = Slot{StoreSymbols::a_Label, 1};
				slot.getAttributes()[0] = w1;
				store.Push(slot);
				slot = Slot{StoreSymbols::F, 1};
				slot.getAttributes()[0] = x1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Comma});
				slot = Slot{StoreSymbols::a_Assign, 2};
				slot.getAttributes()[0] = p1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::F, 1});
				store.Push(Slot{Assign});
				slot = Slot{StoreSymbols::Id, 1};
				slot.getAttributes()[0] = p1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::OpBracket});
                // Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Неизвестный оператор";
			generateExc(s);

		case Assign:
			if (input->Type == 11){
				// Вытолк
				store.Pop();
				// Сдвиг
                delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось :=, а встречено ";
			s += input->Name;
			generateExc(s);

		case E:
			if (input->Type == 1 || input->Type == 2){
				// Замена
				store.Pop();
				store.Push(Slot{StoreSymbols::E_list, 2});
				store.Push(Slot{StoreSymbols::T, 1});
				return;
			}

			s = "Ожидалось арифметическое выражение";
			generateExc(s);

		case T:
			 if (input->Type == 1 || input->Type == 2){
				// Замена
				store.Pop();
				store.Push(Slot{StoreSymbols::T_list, 2});
				store.Push(Slot{F, 1});
				return;
			 }

			 s = "Ошибка построения арифметического выражения";
			 generateExc(s);

		case F:
			if (input->Type == 1 || input->Type == 2){
				// Вытолк
				sl = store.Peek();
				store.Pop();

				int* p1;
				if (input->Type == 1){
					if (id_table_s.find(input->Name) == nullptr){
						s = "Непроинициализированная переменная ";
						s += input->Name;
						generateExc(s);
					}
					if (store.Peek().getSymbol() == StoreSymbols::a_Label){
						Slot slot = store.Peek();
						store.Pop();
						sl = store.Peek();
						sl.getAttributes()[1] = id_table_s.get(input->Name)->Attribute;
						store.Push(slot);
					}
					else
						p1 = id_table_s.get(input->Name)->Attribute;
				}
				else
					if (int_table_s.find(input->Name) == nullptr){
							p1 = allocMem();
							*p1 = atoi(input->Name);
							int_table_s.append(input->Name, p1, 2);
                            if (store.Peek().getSymbol() == StoreSymbols::a_Label){
								Slot slot = store.Peek();
								store.Pop();
								sl = store.Peek();
								sl.getAttributes()[1] = int_table_s.get(input->Name)->Attribute;
								store.Push(slot);
							}

					}
					else
					if (store.Peek().getSymbol() == StoreSymbols::a_Label){
						Slot slot = store.Peek();
						store.Pop();
						sl = store.Peek();
						sl.getAttributes()[1] = int_table_s.get(input->Name)->Attribute;
						store.Push(slot);
					}
					else
						p1 = int_table_s.get(input->Name)->Attribute;

                 sl = store.Peek();

				if (sl.getSymbol() ==  StoreSymbols::T_list){
					attributes = sl.getAttributes();
				    attributes[0] = p1;
				}
				else if (sl.getSymbol() == StoreSymbols::a_Div || sl.getSymbol() == StoreSymbols::a_GOE || sl.getSymbol() == StoreSymbols::a_EQ || sl.getSymbol() == StoreSymbols::a_Assign){
					sl.getAttributes()[1] = p1;
					attributes = sl.getAttributes();
//					std::cout << attributes[0] << ' ' << attributes[1] << ' ' << attributes[2] << '\n';
				}


				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидался идентификатор или целочисленная константа";
			generateExc(s);

		case Semicolon:
			if(input->Type == 9){
				// Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось ;";
			generateExc(s);
		case E_list:
			if(input->Type == 9){
				sl = store.Peek();
				int* p2 = sl.getAttributes()[0];
				// Вытолк
				store.Pop();
				sl = store.Peek();
				if (sl.getSymbol() == StoreSymbols::a_Assign)
					sl.getAttributes()[1] = p2;
				return;
			}

			if(input->Type == 12){
				// Замена
				sl = store.Peek();
				int* p1 = sl.getAttributes()[0];
				int* r1 = allocMem();
				store.Pop();
				store.Push(Slot{StoreSymbols::E_list, 2});
				Slot slot = Slot{StoreSymbols::a_Sum, 3};
				attributes = slot.getAttributes();
				attributes[0] = p1;
				attributes[2] = r1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::T, 1});
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ошибка построения арифметического выражения";
			generateExc(s);

		case T_list:
			if(input->Type == 9 || input->Type == 12){
				sl = store.Peek();
				int* p2 = sl.getAttributes()[0];
				// Вытолк
				store.Pop();
				sl = store.Peek();
				if (sl.getSymbol() == StoreSymbols::E_list)
					sl.getAttributes()[0] = p2;
				else if(sl.getSymbol() == StoreSymbols::a_Sum)
					sl.getAttributes()[1] = p2;
				return;

			}
			if(input->Type == 13){
				// Замена
				sl = store.Peek();
				int* p1 = sl.getAttributes()[0];
				int* r1 = allocMem();
				store.Pop();
				store.Push(Slot{StoreSymbols::T_list, 2});
				Slot slot{StoreSymbols::a_Div, 3};
				attributes = slot.getAttributes();
				attributes[0] = p1;
				attributes[2] = r1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::F});
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

            s = "Ошибка построения арифметического выражения";
			generateExc(s);
		case OpBracket:
			if(input->Type == 7){
				// Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось (";
			generateExc(s);

		case ClBracket:
			if(input->Type == 8){
				// Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось )";
			generateExc(s);

		case Bool_expr:
			if (input->Type == 1 || input->Type == 2){
				int* p1;
				if (input->Type == 1){
					if (id_table_s.find(input->Name) == nullptr){
						s = "Непроинициализированная переменная ";
						s += input->Name;
						generateExc(s);
					}
					p1 = id_table_s.get(input->Name)->Attribute;
				}
				else
					if (int_table_s.find(input->Name) == nullptr){
						p1 = allocMem();
						*p1 = atoi(input->Name);
						int_table_s.append(input->Name, p1, 2);
				}
				else
					p1 = int_table_s.get(input->Name)->Attribute;

				// Замена
				store.Pop();
				Slot slot{StoreSymbols::Bool_op, 2};
				slot.getAttributes()[0] = p1;
				store.Push(slot);

				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидался идентификатор или целочисленная константа, в логическом выражении";
			generateExc(s);

		case Bool_op:
			if(input->Type == 14 || input->Type == 15){
				sl = store.Peek();
				int* p1 = sl.getAttributes()[0];
				// Замена
				store.Pop();
				int* t1 = allocMem();

				if(input->Type == 14){
					Slot slot{StoreSymbols::a_GOE, 3};
					attributes = slot.getAttributes();
					attributes[0] = p1;
					attributes[2] = t1;
//					std::cout << attributes[0] << ' ' << attributes[1] << ' ' << attributes[2] << '\n';
					store.Push(slot);
					store.Push(Slot{StoreSymbols::F, 1});
					store.Push(Slot{StoreSymbols::GOE});
					return;
				}
				else{
					Slot slot{StoreSymbols::a_EQ, 3};
					attributes = slot.getAttributes();
					attributes[0] = p1;
					attributes[2] = t1;
					store.Push(slot);
					store.Push(Slot{StoreSymbols::F, 1});
					store.Push(Slot{StoreSymbols::EQ});
                    return;
				}

			}

			s = "Ожидалось >= или ==, встречено ";
			s += input->Name;
			generateExc(s);
		case GOE:
			if(input->Type == 14){
				// Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось >=";
			generateExc(s);

		case EQ:
			if(input->Type == 15){
				// Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидалось ==";
			generateExc(s);

		case End2:
			if(input->Type == 1 || input->Type == 3 || input->Type == 5){
				sl = store.Peek();
				int* z1 = sl.getAttributes()[0];
				(*z1) = res.size();
				Slot slot{StoreSymbols::a_Label, 1};
				slot.getAttributes()[0] = z1;

				//Замена
				store.Pop();
				store.Push(slot);
                return;
			}

			if(input->Type == 4){
				sl = store.Peek();
				Slot slot;
				int* z1 = sl.getAttributes()[0];
				int* w1 = allocLabel();
				//Замена
				store.Pop();
				slot = Slot{StoreSymbols::a_Label, 1};
				slot.getAttributes()[0] = w1;
				store.Push(slot);
				store.Push(Slot{StoreSymbols::Op});
				slot = Slot{StoreSymbols::a_Label, 1};
				slot.getAttributes()[0] = z1;
				store.Push(slot);
				slot = Slot{StoreSymbols::a_UnCondit, 1};
				slot.getAttributes()[0] = w1;
				store.Push(slot);
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}
		case Id:
			if(input->Type == 1){
				sl = store.Peek();
				int* p1 = sl.getAttributes()[0];
				if(id_table_s.find(input->Name) == nullptr){
					(*p1) = 0;
					id_table_s.append(input->Name, p1, 1);
				}
				else{
					(*p1) = (*(id_table_s.get(input->Name)->Attribute));
					freeMem(id_table_s.get(input->Name)->Attribute);
					id_table_s.get(input->Name)->Attribute = p1;
				}

				//Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}

			s = "Ожидался идентификатор";
			generateExc(s);
		case End:
			if(input->Type == 6){
				//Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}
			s = "Ожидалось КОНЕЦ";
			generateExc(s);
		case Comma:
			if(input->Type == 10){
				//Вытолк
				store.Pop();
				// Сдвиг
				delete input;
				input = nullptr;
				return;
			}
			s = "Ожидалось ,";
			generateExc(s);

	}

}

Сompiler::SyntaxBlock::Slot::Slot(Сompiler::SyntaxBlock::StoreSymbols s, int attributesCount): m_symbol{s}, m_attributesCount{attributesCount}{
	if (attributesCount == 0) return;
	m_attributes = new int*[m_attributesCount];
	for (int i = 0; i < m_attributesCount; i++)
		 m_attributes[i] = nullptr;
}

Сompiler::SyntaxBlock::Slot::Slot(const Сompiler::SyntaxBlock::Slot& item){
//	std::cout << "Копирование\n";
	m_symbol = item.m_symbol;
	m_attributesCount = item.m_attributesCount;
	m_attributes = new int*[m_attributesCount];
	for (int i=0; i<m_attributesCount; i++){
		m_attributes[i] = item.m_attributes[i];
//		std::cout << item.m_attributes[i] << ' ';
	}
//	std::cout << '\n';
	return;
}

//Сompiler::SyntaxBlock::Slot& Сompiler::SyntaxBlock::Slot::operator=(const Сompiler::SyntaxBlock::Slot& item)
//	{
//		std::cout << "Присваивание\n";
//		if(&item != this)
//		{
//			m_symbol = item.m_symbol;
//			m_attributesCount = item.m_attributesCount;
//			m_attributes = new int*[m_attributesCount];
//			for(int i = 0; i < m_attributesCount; i++){
//				m_attributes[i] = item.m_attributes[i];
//				std::cout << item.m_attributes[i] << ' ';
//			}
//		}
//		std::cout << '\n';
//		return *this;
//	}

Сompiler::SyntaxBlock::Slot::~Slot(){
//	for (int i=0; i<m_attributesCount; i++) delete m_attributes[i];
	delete[] m_attributes;
//    std::cout << "Дестркутор\n";
}

Сompiler::SyntaxBlock::SyntaxBlock(int n, int m): N{n}, M{m}, id_table_s{}, int_table_s{}{
	labels[0] = new int[M];
	labels[1] = new int[M];
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < N; j++)
			labels[i][j] = 0;

	data[0] = new int[N];
	data[1] = new int[N];
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < N; j++)
			data[i][j] = 0;
}

Сompiler::SyntaxBlock::~SyntaxBlock(){
	delete[] data[0];
	delete[] data[1];
	delete[] labels[0];
    delete[] labels[1];
}

int* Сompiler::SyntaxBlock::allocMem(){
	for(int i = 0; i < N; i++)
		if(data[1][i] == 0) {
			data[1][i] = 1;
			return data[0] + i;
		}


	return nullptr;
}

bool Сompiler::SyntaxBlock::freeMem(int* i){
//	if(i < 0 || i >= N)
//		return false;
	int count = i - data[0];
	data[1][count] = 0;
	return true;
}

int* Сompiler::SyntaxBlock::allocLabel(){
	for(int i = 0; i < N; i++)
		if(labels[1][i] == 0) {
			labels[1][i] = 1;
			return labels[0] + i;
		}


	return nullptr;
}

bool Сompiler::SyntaxBlock::freeLabel(int* i){
//	if(i < 0 || i >= N)
//		return false;
	int count = i - labels[0];
	labels[1][count] = 0;
	return true;
}

void Сompiler::SyntaxBlock::Interpreter(Сompiler::SyntaxBlock::Slot* commands){
	int i = 0;
	bool notEnd = true;
	StoreSymbols comandCode;
	int** attributes = nullptr;
	while(notEnd){
		comandCode = commands[i].getSymbol();
		attributes = commands[i].getAttributes();
		switch(comandCode){
			// Присвоить
			case a_Assign:
				*(attributes[0]) = *(attributes[1]);
				i++;
				break;
			// Сложить
			case a_Sum:{
				int sum = *(attributes[0]) + *(attributes[1]);
				*(attributes[2]) = sum;
				i++;
				break;
			}
			// Разделить
			case a_Div:{
			   int div = *(attributes[0]) / *(attributes[1]);
			   *(attributes[2]) = div;
               i++;
			   break;
			}
			// Усл. переход по 0
			case a_Condit0:
				if(*(attributes[0]) == 0)
					i = *(attributes[1]);
				else
					i++;
				break;
			// Больше или равно
			case a_GOE:
				if(*(attributes[0]) >= *(attributes[1]))
					*(attributes[2]) = 1;
				else
					*(attributes[2]) = 0;
				i++;
				break;
			// Равно
			case a_EQ:
				if(*(attributes[0]) == *(attributes[1]))
					*(attributes[2]) = 1;
				else
					*(attributes[2]) = 0;
				i++;
				break;
			// Безусл. переход
			case a_UnCondit:
				i = *(attributes[0]);
				break;
			// {Увелич. Id на 1}
			case a_Inc:
				*(attributes[0]) = *(attributes[0]) + 1;
				i++;
				break;
			// {Пер. по сравн.}
			case a_CompTrans:
				if(*(attributes[0]) > *(attributes[1]))
					i = *(attributes[2]);
				else
					i++;
				break;
			case Stop:
				notEnd = false;
		}
	}
}


#pragma package(smart_init)
