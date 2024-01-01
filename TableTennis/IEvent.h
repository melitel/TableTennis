#pragma once

class IEvent
{
public:
	virtual void onEvent() = 0;
	virtual ~IEvent() = default;
};

