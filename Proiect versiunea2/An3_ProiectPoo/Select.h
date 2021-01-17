#pragma once
#include"BaseClass.h"
#include"Utils.h"
class Select :public BaseClass {
public:
	Select(std::string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);
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
