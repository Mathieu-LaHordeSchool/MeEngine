#pragma once

namespace me::core {
	class EnableObject
	{
		struct Internal;
		Internal* m_enableObj;

	public:
		explicit EnableObject();
		~EnableObject() noexcept = default;

		bool GetActive() const;
		virtual void SetActive(bool active);
	};
}
