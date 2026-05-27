#pragma once
#include "ForwardDeclarations.h"
#include <cstdint>
#include <memory>

class Processor
{
protected:
	Processor() = default;
public:
	Processor(const Processor&) = delete;
	Processor& operator=(const Processor&) = delete;

	Processor(Processor&&) = delete;
	Processor& operator=(Processor&&) = delete;

	virtual void AddAction(int8_t choice, std::shared_ptr<Action> action) = 0;

	virtual void Process() = 0;

	virtual ~Processor() = default;
};