#pragma once
#include "Buffer.h"

class Menu
{
private:
	Menu() { }

public:
	static Menu *Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Menu();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool run(Buffer &buffer);

private:
	static Menu *s_pInstance;

private:
	void	runStory(Buffer &buffer);
};

typedef Menu TheMenu;