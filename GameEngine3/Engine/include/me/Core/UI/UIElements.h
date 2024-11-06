#pragma once

#include <glm/glm.hpp>

namespace me::core::ui {
	enum ScaleType
	{
		XY, YX, XX, YY
	};

	class UIElement
	{
	public:
		int order = 0;
		glm::vec4 color = glm::vec4(1.f);
	};
}
