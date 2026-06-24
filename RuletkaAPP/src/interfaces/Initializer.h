#pragma once
class Initializer
{
protected:
	Initializer() = default;
public:

	Initializer(const Initializer&) = delete;
	Initializer& operator=(const Initializer&) = delete;

	Initializer(Initializer&&) = delete;
	Initializer operator=(Initializer&&) = delete;

	virtual void Initialize() = 0;

	virtual ~Initializer() = default;
};