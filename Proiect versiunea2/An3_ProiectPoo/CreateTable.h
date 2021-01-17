#pragma once
#include"BaseClass.h"
#include"Utils.h"
class CreateTable :public BaseClass {
public:
	static int id;
	CreateTable(std::string command) : BaseClass(command)
	{


	}
	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);

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

				std::string columnsDefinition = Utils::subVectorToString(args, 6, args.size());

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

			std::string columnsDefinition = Utils::subVectorToString(args, 3, args.size());

			bool resultValidateColumnsDefinition = validateColumnsDefinition(columnsDefinition);

			if (!resultValidateColumnsDefinition)
				return resultValidateColumnsDefinition;
		}
		else
			return Utils::print(false, "Al patrulea argument ar trebui sa fie inceputul de la \"IF NOT EXISTS\" sau \"((nume_coloana, dimensiune_coloana...))!");

		return Utils::print(true, "");
	}
	bool validateColumnsDefinition(std::string columnsDefinition)
	{
		std::string columnsDefinitionBetweenParantheses = Utils::substring(columnsDefinition, 1, columnsDefinition.length() - 1);

		if (nrOpenedParantheses(columnsDefinitionBetweenParantheses) != nrClosedParantheses(columnsDefinitionBetweenParantheses))
		{
			return Utils::print(false, "Numarul de paranteze deschise " +
				Utils::intToString(nrOpenedParantheses(columnsDefinitionBetweenParantheses) + 1) +
				" nu este acelasi cu numarul de paranteze inchise " +
				Utils::intToString(nrClosedParantheses(columnsDefinitionBetweenParantheses) + 1) +
				"!");
		}

		std::string firstColumnDefinition = extractFirstColumnDefinition(columnsDefinitionBetweenParantheses);

		if (firstColumnDefinition == "")
		{
			return Utils::print(false, "Definitia primei coloane ar trebui sa inceapa cu \"(\" si sa se termine cu \")\"!");
		}
		else
		{
			std::vector<std::string> columnDefinitions = Utils::splitString(firstColumnDefinition, ',', true);
			if (columnDefinitions.size() != 4)
				return Utils::print(false, "Prima coloana nu contine toate datele necesare (nume, tip, dimensiune, valoare implicita)!");
			else
			{
				std::string columnType = Utils::strip(columnDefinitions[1]);
				if (!(columnType == "int" ||
					columnType == "text" ||
					columnType == "float"))
				{
					return Utils::print(false, "Tipul primei coloane ar trebui sa fie \"INT\", \"TEXT\" sau \"FLOAT\"!");
				}
				std::string columnDimension = Utils::strip(columnDefinitions[2]);
				if (!Utils::isNumber(columnDimension))
				{
					return Utils::print(false, "Dimensiunea primei coloane ar trebui sa fie un numar!");
				}
			}
		}

		std::string restColumnsDefinition = extractRestColumnDefinition(columnsDefinitionBetweenParantheses);

		int nrColumn = 2;
		while (restColumnsDefinition != "")
		{
			std::string columnDefinition = extractFirstColumnDefinition(restColumnsDefinition);
			std::vector<std::string> columnDefinitions = Utils::splitString(columnDefinition, ',', true);
			if (columnDefinitions.size() != 4)
				return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) +
					" nu contine toate detaliile (nume, tip, dimensiune, valoare implicita)!");
			else
			{
				std::string columnType = Utils::strip(columnDefinitions[1]);
				if (!(columnType == "int" ||
					columnType == "text" ||
					columnType == "float"))
					return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) + " nu are tipul \"INT\", \"TEXT\" or \"FLOAT\"!");

				std::string columnDimension = Utils::strip(columnDefinitions[2]);
				if (!Utils::isNumber(columnDimension))
					return Utils::print(false, "Coloana nr. " + Utils::intToString(nrColumn) + " nu are dimensiunea un numar!");
			}
			restColumnsDefinition = extractRestColumnDefinition(restColumnsDefinition);

			nrColumn++;
		}
		return Utils::print(true, "");
	}
	std::string extractRestColumnDefinition(std::string columnsDefinitionBetweenParantheses)
	{
		std::string str;
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

	std::string extractFirstColumnDefinition(std::string columnsDefinitionBetweenParantheses)
	{
		std::string str;
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
	int nrOpenedParantheses(std::string str)
	{
		int count = 0;
		for (char letter : str)
			if (letter == '(')
				count++;
		return count;
	}
	int nrClosedParantheses(std::string str)
	{
		int count = 0;
		for (char letter : str)
			if (letter == ')')
				count++;
		return count;
	}
}; 
