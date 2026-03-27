#pragma once

class IGameEngine
{
public:
	virtual void Run() = 0;

    virtual ~IGameEngine() = default;
};
