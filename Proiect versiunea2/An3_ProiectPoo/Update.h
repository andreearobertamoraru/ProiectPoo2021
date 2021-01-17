#pragma once
#include"BaseClass.h"
#include"Utils.h"
class Update :public BaseClass {
public:
	Update(std::string command) : BaseClass(command)
	{

	}

	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);
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
