#pragma once
#include "Initializer.h"
#include "UI.h"
#include <memory>

class UIInitializer : public Initializer
{
private:
	std::shared_ptr<UI> ui;
public:
	UIInitializer(std::shared_ptr<UI> ui) : ui(ui) {}

	void Initialize() override
	{
		ui->Initialize();
		ui->ResetUI();
	}
};