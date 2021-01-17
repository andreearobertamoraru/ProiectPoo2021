#pragma once
#include"BaseClass.h"
#include"Utils.h"
class DisplayTable :public BaseClass {
public:
	DisplayTable(std::string command) : BaseClass(command)
	{

	}

	bool valideaza()
	{
		std::vector<std::string> args = Utils::splitString(this->getCommand(), ' ', true);

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
