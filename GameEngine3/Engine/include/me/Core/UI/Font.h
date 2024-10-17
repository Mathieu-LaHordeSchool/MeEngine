#pragma once

namespace me::core::ui {
	class Font
	{
		struct Internal;
		Internal* m_font;

	public:
		explicit Font(const char* path);
		~Font() noexcept = default;

		void LoadAllCharacter();
	};
}
