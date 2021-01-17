#pragma once
#include"BaseClass.h"
#include"Utils.h"
class Delete :public BaseClass {
public:
	Delete(std::string command) : BaseClass(command)
	{

	}
	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);
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
	}
}; 
