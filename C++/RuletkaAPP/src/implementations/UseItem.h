#pragma once
#include "ForwardDeclarations.h"
#include "Processor.h"
#include "Action.h"
#include <string>
#include <memory>
#include <cassert>
#include <stdexcept>

class UseItem : public Action
{
private:
	std::shared_ptr<Processor> ip;
public:
	UseItem(std::shared_ptr<Processor> ip) : ip(std::move(ip)) {}

	void Execute() override 
	{ 
		assert(ip);
		if (ip) ip->Process();
		else throw std::runtime_error("Nie ustawiono ip!");
	}
};