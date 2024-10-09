#pragma once

#include <Timer/HandleTimer.h>

class Inputs;
class Entity;
class Renderer;

class Component 
{
public:
	explicit Component(Entity* own) {
		owner = own;
	}
	~Component() noexcept = default;

	Entity* owner;

	virtual void Start()					{}
	virtual void Awake()					{}

	virtual void Update(HandleTimer t)		{}
	virtual void BindInputs(Inputs* inputs) {}

	virtual const char* GetType() const		{ return ""; }
	virtual void Render(Renderer* render)	{}
};
