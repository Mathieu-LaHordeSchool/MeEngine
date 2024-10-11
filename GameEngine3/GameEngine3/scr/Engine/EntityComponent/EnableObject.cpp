
#include <Engine/EntityComponent/EnableObject.h>

struct EnableObject::Internal
{
	bool enable;
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
