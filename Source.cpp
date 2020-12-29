#include<iostream>
#include<vector>
#include<sstream>
#include<tuple>
using namespace std;

void help();

class Utils {
public:
	static vector<string> splitVector(vector<string> v, int indexStart, int indexEnd)
	{
		vector<string> newVector;
		for (int i = indexStart; i < indexEnd; i++)
		{
			newVector.push_back(v[i]);
		}
		return newVector;
	}
	static string subVectorToString(vector<string> v, int indexStart, int indexEnd)
	{
		string str;
		for (int i = indexStart; i < indexEnd; i++)
		{
			str += v[i] + " ";
		}
		return substring(str, 0, str.length() - 1);
	}
	static vector<string> splitString(string str, char delimiter, bool lower)
	{
		vector<string> tokens;
		string temp;
		for (char letter : str)
		{
			if (letter == delimiter)
			{
				tokens.push_back(temp);
				temp = "";
			}
			else
			{
				if (lower)
					letter = tolower(letter);
				temp += letter;
			}
		}
		if (temp != "")
			tokens.push_back(temp);
		return tokens;
	}
	static char** splitStringChar(string str, char delimiter, bool lower, int& nrTokens)
	{
		void* pointer;
		char** matrixArgs = nullptr;
		pointer = (char**)malloc(2 * sizeof(char*));

		if (pointer != nullptr)
			matrixArgs = (char**)pointer;

		string temp;
		for (char letter : str)
		{
			if (letter == delimiter)
			{
				if (matrixArgs != nullptr) {
					matrixArgs[nrTokens] = (char*)malloc((temp.length() + 1) * sizeof(char));
					strcpy_s(matrixArgs[nrTokens++], temp.length() + 1, temp.c_str());
				}
				pointer = realloc(matrixArgs, (2 + nrTokens) * sizeof(char*));
				if (pointer != nullptr)
					matrixArgs = (char**)pointer;
				temp = "";
			}
			else
			{
				if (lower)
					letter = tolower(letter);
				temp += letter;
			}
		}
		if (temp != "") {
			if (matrixArgs != nullptr) {
				matrixArgs[nrTokens] = (char*)malloc((temp.length() + 1) * sizeof(char));
				if (matrixArgs[nrTokens] != nullptr)
					strcpy_s(matrixArgs[nrTokens++], temp.length() + 1, temp.c_str());
			}
			pointer = (char**)realloc(matrixArgs, (2 + nrTokens) * sizeof(char*));
			if (pointer != nullptr)
				matrixArgs = (char**)pointer;
		}
		return matrixArgs;
	}
	static string substring(string str, int indexStart, int indexEnd)
	{
		string newStr;
		if (indexEnd > str.length())
			indexEnd = str.length();
		for (int i = indexStart; i < indexEnd; i++)
			newStr += str[i];
		return newStr;
	}
	static string vectorToString(vector<string> v)
	{
		string str;
		for (string s : v)
			str += s + " ";
		return str;
	}
	static string intToString(int number)
	{
		string str = "";
		str += (char)(number + '0');
		return str;
	}
	static string toLower(string str)
	{
		string toLowerStr;

		for (char letter : str)
		{
			toLowerStr += tolower(letter);
		}
		return toLowerStr;
	}
	static string toUpper(string str)
	{
		string toUpperStr;

		for (char letter : str)
		{
			toUpperStr += toupper(letter);
		}
		return toUpperStr;
	}
	static bool isNumber(string str)
	{
		for (char letter : str)
			if (!isdigit(letter))
				return false;
		return true;
	}
	static string strip(string str)
	{
		string newStr;
		int i = 0;
		int j = str.size() - 1;
		while (str[i] == ' ')
			i++;
		while (str[j] == ' ')
			j--;
		for (int idx = i; idx <= j; idx++)
			newStr += str[idx];
		return newStr;
	}
	static bool print(bool success, string message) {
		if (message != "")
			cout << message << endl;
		return success;
	}
	static void afisareMatriceChar(char** matrix, int size) {
		for (int i = 0; i < size; i++)
			cout << matrix[i] << '\n';
	}
};

class BaseClass {
private:
	string comanda;
public:
	BaseClass(string comanda)
	{
		this->comanda = comanda;
	}
	string getCommand()
	{
		return comanda;
	}
	void setCommand(string comanda)
	{
		this->comanda = comanda;
	}
	virtual bool valideaza() = 0;
};

class CreateTable :public BaseClass {
public:
	static int id;
	CreateTable(string command) : BaseClass(command)
	{


	}
	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);

		if (args[0] != "create")
		{
			return Utils::print(false, "Primul argument al comenzii ar trebui sa fie \"CREATE\"!");
		}
		if (args[1] != "table")
		{
			return Utils::print(false, "Al doilea argument al comenzii ar trebui sa fie \"TABLE\"!");
		}
		if (args[2] == "if" || args[2][0] == '(')
		{
			return Utils::print(false, "Al treilea argument al comenzii ar trebui sa fie numele tabelei!");
		}
		if (args[3] == "if")
		{
			if (args[4] != "not")
				return Utils::print(false, "Al cincilea argument ar trebui sa fie \"NOT\" daca al patrulea argument este \"IF\"!");

			if (args[5] != "exists")
				return Utils::print(false, "Al saselea argument ar trebui sa fie \"EXISTS\" daca al cincilea argument este \"NOT\"!");

			if (args[6][0] != '(')
				return Utils::print(false, "Al saptelea argument ( definitia coloanelor ) ar trebui sa inceapa cu \"(\"!");

			else {
				if (args[args.size() - 1][args[args.size() - 1].length() - 1] != ')')
					return Utils::print(false, "Comanda ar trebui sa se termine cu \")\"!");

				string columnsDefinition = Utils::subVectorToString(args, 6, args.size());

				bool resultValidateColumnsDefinition = validateColumnsDefinition(columnsDefinition);

				if (!resultValidateColumnsDefinition)
					return resultValidateColumnsDefinition;
			}
		}
		else if (args[3][0] == '(')
		{
			if (args[args.size() - 1][args[args.size() - 1].length() - 1] != ')')
			{
				return Utils::print(false, "Comanda ar trebui sa se termine cu \")\"!");
			}

			string columnsDefinition = Utils::subVectorToString(args, 3, args.size());

			bool resultValidateColumnsDefinition = validateColumnsDefinition(columnsDefinition);

			if (!resultValidateColumnsDefinition)
				return resultValidateColumnsDefinition;
		}
		else
			return Utils::print(false, "Al patrulea argument ar trebui sa fie inceputul de la \"IF NOT EXISTS\" sau \"((nume_coloana, dimensiune_coloana...))!");

		return Utils::print(true, "");
	}
	bool validateColumnsDefinition(string columnsDefinition)
	{
		string columnsDefinitionBetweenParantheses = Utils::substring(columnsDefinition, 1, columnsDefinition.length() - 1);

		if (nrOpenedParantheses(columnsDefinitionBetweenParantheses) != nrClosedParantheses(columnsDefinitionBetweenParantheses))
		{
			return Utils::print(false, "Numarul de paranteze deschise " +
				Utils::intToString(nrOpenedParantheses(columnsDefinitionBetweenParantheses) + 1) +
				" nu este acelasi cu numarul de paranteze inchise " +
				Utils::intToString(nrClosedParantheses(columnsDefinitionBetweenParantheses) + 1) +
				"!");
		}

		string firstColumnDefinition = extractFirstColumnDefinition(columnsDefinitionBetweenParantheses);

		if (firstColumnDefinition == "")
		{
			return Utils::print(false, "Definitia primei coloane ar trebui sa inceapa cu \"(\" si sa se termine cu \")\"!");
		}
		else
		{
			vector<string> columnDefinitions = Utils::splitString(firstColumnDefinition, ',', true);
			if (columnDefinitions.size() != 4)
				return Utils::print(false, "Prima coloana nu contine toate datele necesare (nume, tip, dimensiune, valoare implicita)!");
			else
			{
				string columnType = Utils::strip(columnDefinitions[1]);
				if (!(columnType == "int" ||
					columnType == "text" ||
					columnType == "float"))
				{
					return Utils::print(false, "Tipul primei coloane ar trebui sa fie \"INT\", \"TEXT\" sau \"FLOAT\"!");
				}
				string columnDimension = Utils::strip(columnDefinitions[2]);
				if (!Utils::isNumber(columnDimension))
				{
					return Utils::print(false, "Dimensiunea primei coloane ar trebui sa fie un numar!");
				}
			}
		}

		string restColumnsDefinition = extractRestColumnDefinition(columnsDefinitionBetweenParantheses);

		int nrColumn = 2;
		while (restColumnsDefinition != "")
		{
			string columnDefinition = extractFirstColumnDefinition(restColumnsDefinition);
			vector<string> columnDefinitions = Utils::splitString(columnDefinition, ',', true);
			if (columnDefinitions.size() != 4)
				return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) +
					" nu contine toate detaliile (nume, tip, dimensiune, valoare implicita)!");
			else
			{
				string columnType = Utils::strip(columnDefinitions[1]);
				if (!(columnType == "int" ||
					columnType == "text" ||
					columnType == "float"))
					return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) + " nu are tipul \"INT\", \"TEXT\" or \"FLOAT\"!");

				string columnDimension = Utils::strip(columnDefinitions[2]);
				if (!Utils::isNumber(columnDimension))
					return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) + " nu are dimensiunea un numar!");
			}
			restColumnsDefinition = extractRestColumnDefinition(restColumnsDefinition);

			nrColumn++;
		}
		return Utils::print(true, "");
	}
	string extractRestColumnDefinition(string columnsDefinitionBetweenParantheses)
	{
		string str;
		int paranthesesIndex = -1;
		for (int i = 0; i < columnsDefinitionBetweenParantheses.length(); i++)
			if (columnsDefinitionBetweenParantheses[i] == ')')
			{
				paranthesesIndex = i;
				break;
			}
		if (paranthesesIndex == -1)
			return "";
		for (int i = paranthesesIndex + 1; i < columnsDefinitionBetweenParantheses.length(); i++)
			str += columnsDefinitionBetweenParantheses[i];
		return str;
	}

	string extractFirstColumnDefinition(string columnsDefinitionBetweenParantheses)
	{
		string str;
		int firstParanthesesIndex = -1, secondParanthesesIndex = -1;
		for (int i = 0; i < columnsDefinitionBetweenParantheses.size(); i++) {
			if (columnsDefinitionBetweenParantheses[i] == '(')
				firstParanthesesIndex = i;
			if (firstParanthesesIndex != -1 && columnsDefinitionBetweenParantheses[i] == ')')
			{
				secondParanthesesIndex = i;
				break;
			}
		}
		if (firstParanthesesIndex == -1 || secondParanthesesIndex == -1)
			return "";
		for (int i = firstParanthesesIndex + 1; i < secondParanthesesIndex; i++)
			str += columnsDefinitionBetweenParantheses[i];
		return str;
	}
	int nrOpenedParantheses(string str)
	{
		int count = 0;
		for (char letter : str)
			if (letter == '(')
				count++;
		return count;
	}
	int nrClosedParantheses(string str)
	{
		int count = 0;
		for (char letter : str)
			if (letter == ')')
				count++;
		return count;
	}
};

class DropTable :public BaseClass {
public:
	DropTable(string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);

		if (args.size() != 3)
		{
			return Utils::print(false, "Comanda ar trebui sa aiba trei argumente, foloseste comanda \"help\"!");
		}
		if (args[0] != "drop")
		{
			return Utils::print(false, "Primul argument ar trebui sa fie \"DROP\"!");
		}
		if (args[1] != "table")
		{
			return Utils::print(false, "Al doilea argument ar trebui sa fie \"TABLE\"!");
		}
		return Utils::print(true, "");
	}
};

class DisplayTable :public BaseClass {
public:
	DisplayTable(string command) : BaseClass(command)
	{

	}

	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);

		if (args.size() != 3)
		{
			return Utils::print(false, "Comanda ar trebui sa aiba trei argumente, foloseste comanda \"help\"!");
		}
		if (args[0] != "display")
		{
			return Utils::print(false, "Primul argument ar trebui sa fie \"DISPLAY\"!");
		}
		if (args[1] != "table")
		{
			return Utils::print(false, "Al doilea argument ar trebui sa fie \"TABLE\"!");
		}
		return Utils::print(true, "");
	}
};

class Insert :public BaseClass {
public:
	Insert(string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);

		if (args.size() < 4)
		{
			return Utils::print(false, "Comanda nu poate avea mai putine de 4 argumente!");
		}
		if (args[0] != "insert")
		{
			return Utils::print(false, "Primul argument ar trebui sa fie \"INSERT\"!");
		}
		if (args[1] != "into")
		{
			return Utils::print(false, "Al doilea argument ar trebui sa fie \"INTO\"!");
		}
		if (args[2] == "values")
		{
			return Utils::print(false, "Al treilea argument ar trebui sa fie numele tabelei!");
		}
		if (!(Utils::substring(args[3], 0, 6) == "values"))
		{
			return Utils::print(false, "Al patrulea argument ar trebui sa fie \"VALUES\"!");
		}

		return Utils::print(true, "");
	}
};

class Select :public BaseClass {
public:
	Select(string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);
		if (args.size() != 4 && args.size() != 8)
			return Utils::print(false, "Comanda trebuie sa aiba 4 sau 8 argumente!");

		if (args[0] != "select")
			return Utils::print(false, "Primul argument ar trebui sa fie \"INSERT\"!");

		if (!(args[1] == "all" || (args[2][0] == '(' && args[2][args[2].length() - 1] == ')')))
			return Utils::print(false, "Al doilea argument ar trebui sa fie \"(..)\" sau \"ALL\"!");

		if (args[2] != "from")
			return Utils::print(false, "Al treilea argument ar trebui sa fie \"FROM\"!");

		if (args[3] == "where")
			return Utils::print(false, "Al patrulea argument ar trebui sa fie numele tabelei!");

		if (args.size() > 4)
		{
			if (args[4] != "where")
				return Utils::print(false, "Al cincilea argument ar trebui sa fie \"WHERE\"!");

			if (args[5] == "=")
				return Utils::print(false, "Al saselea argument ar trebui sa fie numele coloanei nu \"=\"!");

			if (args[6] != "=")
				return Utils::print(false, "Al saptelea argument ar trebui sa fie \"=\"!");

		}
		return Utils::print(true, "");
	}
};

class Update :public BaseClass {
public:
	Update(string command) : BaseClass(command)
	{

	}

	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);
		if (args.size() != 10)
		{
			return Utils::print(false, "Comanda trebuie sa aiba 10 argumente!");
		}

		if (args[0] != "update")
		{
			return Utils::print(false, "Primul argument ar trebui sa fie \"INSERT\"!");
		}
		if (args[1] == "set")
		{
			return Utils::print(false, "Al doilea argument ar trebui sa fie numele tabelei!");
		}

		if (args[2] != "set")
		{
			return Utils::print(false, "Al treilea argument ar trebui sa fie \"SET\"!");
		}

		if (args[3] == "=")
		{
			return Utils::print(false, "Al patrulea argument ar trebui sa fie numele coloanei nu \"=\"!");
		}

		if (args[4] != "=")
		{
			return Utils::print(false, "Al cincilea argument ar trebui sa fie \"=\"!");
		}

		if (args[5] == "where")
		{
			return Utils::print(false, "Al saselea argument nu ar trebui sa fie \"WHERE\"!");
		}

		if (args[6] != "where")
		{
			return Utils::print(false, "Al saptelea argument ar trebui sa fie \"WHERE\"!");
		}

		if (args[7] == "=")
		{
			return Utils::print(false, "Al optalea argument nu ar trebui sa fie \"=\"!");
		}

		if (args[8] != "=")
		{
			return Utils::print(false, "Al optalea argument ar trebui sa fie \"=\"!");
		}
		return Utils::print(true, "");
	}
};

class Delete :public BaseClass {
public:
	Delete(string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		vector<string> args = Utils::splitString(this->getCommand(), ' ', true);
		if (args.size() != 7)
		{
			return Utils::print(false, "Comanda trebuie sa aiba 7 argumente!");
		}
		if (args[0] != "delete")
		{
			return Utils::print(false, "Primul argument ar trebui sa fie \"DELETE\"!");
		}
		if (args[1] != "from")
		{
			return Utils::print(false, "Al doilea argument ar trebui sa fie \"FROM\"!");
		}
		if (args[2] == "where")
		{
			return Utils::print(false, "Al treilea argument ar trebui sa fie numele tabelei!");
		}
		if (args[3] != "where")
		{
			return Utils::print(false, "Al patrulea argument ar trebui sa fie \"WHERE\"!");
		}
		if (args[4] == "=")
		{
			return Utils::print(false, "Al cincilea argument ar trebui sa fie numele coloanei nu \"=\"!");
		}
		if (args[5] != "=")
		{
			return Utils::print(false, "Al saselea argument ar trebui sa fie \"=\"!");
		}
		return Utils::print(true, "");
		return true;
	}
};

void help()
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

int main()
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
				help();
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

	return 0;
}
