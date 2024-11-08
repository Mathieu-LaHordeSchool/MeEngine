#pragma once

#include <typeinfo>
#include <me/Core/EnableObject.h>

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
const char* GetType() const override { \
return ComponentID; \
} \
static const char* GetStaticType() { \
return ComponentID; \
} \

namespace me::core::input { class Inputs; }
namespace me::core { class Entity; }
namespace me::render { class Renderer; }

namespace me::core {
	class Component
		: public EnableObject
	{
	private:
		me::core::Entity* owner;

	public:
		explicit Component(Entity* own)
			: EnableObject()
		{
			owner = own;
		}
		~Component() noexcept = default;

		me::core::Entity* GetOwner() const { return owner; }

		virtual void Start() {}

		virtual void Update() {}
		virtual void BindInputs(me::core::input::Inputs* inputs) {}
		virtual const char* GetType() const { return "Component"; }

		virtual void Render(me::render::Renderer* render) {}
		virtual Component* Clone() { return nullptr; }
	};
}
