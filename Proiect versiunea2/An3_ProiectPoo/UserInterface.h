#pragma once
#include<iostream>
#include<vector>
#include<sstream>
#include<tuple>
#include"CreateTable.h"
#include"DropTable.h"
#include"DisplayTable.h"
#include"Insert.h"
#include"Select.h"
#include"Update.h"
#include"Delete.h"
using namespace std;

class UI {
public:
	void Help()
	{
		cout << "************ OPTIUNI DISPONIBILE ************\n";
		cout << "- CREATE TABLE nume_tabel [DACA NU EXISTA] ((nume_coloana_1, tip, dimensiunea, valoare_implicita), (nume_coloana_2, tip, dimensiunea, valoare_implicita), ...) - minim o coloana\n";
		cout << "- DROP TABLE nume_tabel\n";
		cout << "- DISPLAY TABLE nume_tabel\n";
		cout << "- INSERT INTO nume_tabel VALUES(valoare_1, ...)\n";
		cout << "- DELETE FROM nume_tabel WHERE nume_coloana = valoare\n";
		cout << "- SELECT (coloana_1, coloana_2, ...) | ALL FROM nume_tabel [WHERE nume_coloana = valoare]\n";
		cout << "- UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare\n";
	}

	void StartApp()
	{
		string comanda;
		bool end = false;
		while (!end) {
			cout << "Introdu comanda (pentru ajutor utilizeaza optiunea \"help\"): ";
			getline(cin, comanda);

			while (comanda == "")
			{
				cout << "Introdu comanda (pentru ajutor utilizeaza optiunea \"help\"): ";
				getline(cin, comanda);
			}

			int nrArgs = 0;
			char** args = Utils::splitStringChar(comanda, ' ', true, nrArgs);

			if (args[0] != nullptr) {
				if (strcmp(args[0], "help") == 0)
					Help();
				if (strcmp(args[0], "create") == 0)
				{
					CreateTable createTableInstance(comanda);
					if (createTableInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "drop") == 0)
				{
					DropTable dropTableInstance(comanda);
					if (dropTableInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "display") == 0)
				{
					DisplayTable displayTableInstance(comanda);
					if (displayTableInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "insert") == 0)
				{
					Insert insertInstance(comanda);
					if (insertInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "select") == 0)
				{
					Select selectInstance(comanda);
					if (selectInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "update") == 0)
				{
					Update updateInstance(comanda);
					if (updateInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
				if (strcmp(args[0], "delete") == 0)
				{
					Delete deleteInstance(comanda);
					if (deleteInstance.valideaza())
						cout << "Comanda este valida!" << endl;
				}
			}
		}
	}
}; 
