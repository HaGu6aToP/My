//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Translator.h"
#include "List.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TabOrder = 0;
	Identifiers->Cells[0][0] = static_cast<System::AnsiString>("Name");
	Identifiers->Cells[1][0] = static_cast<System::AnsiString>("Data");
	Integers->Cells[0][0] = static_cast<System::AnsiString>("Name");
	Integers->Cells[1][0] = static_cast<System::AnsiString>("Data");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BeginClick(TObject *Sender)
{
	System::AnsiString s = Memo->Text;
	//	char* sourse = new char[s.Length() + 1];
	//	System::strcpy(sourse, s)
		char* sourse = s.c_str();
		if (sourse == nullptr) return;


		try{

			MyClasses::Ñompiler::SyntaxBlock parser;
			MyClasses::List<MyClasses::Ñompiler::SyntaxBlock::Slot> l = parser.WorkWithSourse(sourse);
			MyClasses::Ñompiler::SyntaxBlock::Slot* array = l.toArray();
			int size = l.size();
			MyClasses::Ñompiler::SyntaxBlock::StoreSymbols symbol;
			int** atributes;
			TranslationRes->Clear();
			for(int i = 0; i < size; i++){
				symbol = array[i].getSymbol();
				atributes = array[i].getAttributes();
				switch (symbol){
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_Assign:
						TranslationRes->Lines->Add("Ïğèñâîèòü");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_Sum:
						TranslationRes->Lines->Add("Ñëîæèòü");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_Div:
						TranslationRes->Lines->Add("Ğàçäåëèòü");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_Condit0:
						TranslationRes->Lines->Add("Óñë. ïåğåõ. ïî 0");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_GOE:
						TranslationRes->Lines->Add("Áîëüøå èëè ğàâíî");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_EQ:
						TranslationRes->Lines->Add("Ğàâíî");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_UnCondit:
						TranslationRes->Lines->Add("Áåçóñë. ïåğåõîä");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_Inc:
						TranslationRes->Lines->Add("Óâåëè÷òü Id íà 1");
						break;
					case MyClasses::Ñompiler::SyntaxBlock::StoreSymbols::a_CompTrans:
						TranslationRes->Lines->Add("Ïåğ. ïî ñğàâí.");
						break;
					default:
						break;
				}
			}

			parser.Interpreter(array);

			const MyClasses::List<MyClasses::Ñompiler::TableOfIdentifiers::Identifier*> id_table = parser.id_table_s.toList();
			const MyClasses::List<MyClasses::Ñompiler::TableOfIdentifiers::Identifier*> int_table = parser.int_table_s.toList();

			int count = 0;
			Identifiers->RowCount = 1;
			for(auto i = id_table.begin(); i != id_table.end(); i++){
				Identifiers->Cells[0][count + 1] = static_cast<System::AnsiString>((*i)->Name);
				Identifiers->Cells[1][count + 1] = *((*i)->Attribute);
				count++;

				if(count == Identifiers->RowCount) Identifiers->RowCount++;
			}

			count = 0;
			Integers->RowCount = 1;
			for(auto i = int_table.begin(); i != int_table.end(); i++){
				Integers->Cells[0][count + 1] = static_cast<System::AnsiString>((*i)->Name);
				Integers->Cells[1][count + 1] = *((*i)->Attribute);
				count++;

				if(count == Integers->RowCount) Integers->RowCount++;
			}
		}
		catch(const MyClasses::Error &e){
			char* s = e.getStr();
			ShowMessage(s);
//			MessageBox(0, s, "Îøèáêà", MB_OK);

			delete[] sourse;
			delete[] s;
			return;
		}


		ShowMessage("Óñïåõ");
}
//---------------------------------------------------------------------------
