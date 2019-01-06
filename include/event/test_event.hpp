#pragma once

#include <iostream>
#include "event/event.hpp"


class test_event : public event
{
public:
	virtual void notify() override
	{
		std::cout << "test event called" << std::endl;
	}
};