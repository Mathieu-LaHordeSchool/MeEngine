#pragma once

#define GetSetInternalValueHPP(Name, Class) \
void Set##Name(Class Name); \
Class Get##Name() const; \

#define GetSetInternalValueCPP(NameMeth, NameVar, ClassVar, Class, Internal) \
void Class::Set##NameMeth(ClassVar NameVar) { \
    Internal->NameVar = NameVar; \
} \
ClassVar Class::Get##NameMeth() const { \
    return Internal->NameVar; \
}

class Inputs;
class Entity;
class Renderer;

class Component 
{
private:
	Entity* owner;

public:
	explicit Component(Entity* own) {
		owner = own;
	}
	~Component() noexcept = default;

	Entity* GetOwner() const { return owner; }

	virtual void Start()					{}

	virtual void Update()					{}
	virtual void BindInputs(Inputs* inputs) {}

	virtual const char* GetType() const		{ return ""; }
	virtual void Render(Renderer* render)	{}
};
