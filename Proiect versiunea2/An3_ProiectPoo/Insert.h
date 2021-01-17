#pragma once
#include"BaseClass.h"
#include"Utils.h"
class Insert :public BaseClass {
public:
	Insert(std::string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);

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
