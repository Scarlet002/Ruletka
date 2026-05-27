#pragma once
class Validator
{
protected:
	Validator() = default;
public:

	Validator(const Validator&) = delete;
	Validator& operator=(const Validator&) = delete;

	Validator(Validator&&) = delete;
	Validator operator=(Validator&&) = delete;

	virtual void Validate() = 0;

	virtual ~Validator() = default;
};