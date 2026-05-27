#pragma once
class IGameEngine
{
protected:
	IGameEngine() = default;
public:
	IGameEngine(const IGameEngine&) = delete;
	IGameEngine& operator=(const IGameEngine&) = delete;

	IGameEngine(IGameEngine&&) = delete;
	IGameEngine& operator=(IGameEngine&&) = delete;

	virtual void RunLoop() = 0;

    virtual ~IGameEngine() = default;
};
