#pragma once

#include<iostream>
class BaseClass {
private:
	std::string comanda;
public:
	BaseClass(std::string comanda)
	{
		this->comanda = comanda;
	}
	std::string getCommand()
	{
		return comanda;
	}
	void setCommand(std::string comanda)
	{
		this->comanda = comanda;
	}
	virtual bool valideaza() = 0;
};
