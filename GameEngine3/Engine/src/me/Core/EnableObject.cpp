
#include <me/Core/EnableObject.h>

using namespace me::core;

struct EnableObject::Internal
{
	bool enable = true;
};

EnableObject::EnableObject()
	: m_enableObj(new Internal())
{}

bool EnableObject::GetActive() const
{
	return m_enableObj->enable;
}
void EnableObject::SetActive(bool active)
{
	m_enableObj->enable = active;
}
