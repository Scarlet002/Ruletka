#pragma once
class Action
{
protected:
	Action() = default;
public:

	Action(const Action&) = delete;
	Action& operator=(const Action&) = delete;

	Action(Action&&) = delete;
	Action operator=(Action&&) = delete;

	virtual void Execute() = 0;

	virtual ~Action() = default;
};