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

#define GetComponentType(ComponentID) \
int GetType() const override { \
return ComponentID; \
} \
static int GetStaticType() { \
return ComponentID; \
} \

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
	virtual int GetType() const		{ return 0; }

	virtual void Render(Renderer* render)	{}
	virtual Component* Clone()				{ return nullptr; }
};
