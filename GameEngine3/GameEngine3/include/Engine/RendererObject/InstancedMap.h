#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <RendererObject/Buffer.h>
#include <algorithm>

template<typename T>
class InstancedMap
{
public:
	explicit InstancedMap() {
		mapBuffer = new Buffer();
		mapBuffer->InitBuffer(sizeof(T) * 500, nullptr);

		for (int i = 0; i < 500; i++) {
			map.push_back(T());
		}
	}
	~InstancedMap() noexcept = default;

public:
	inline std::vector<T>	GetMapVector()		const { return map;				}
	inline Buffer*			GetMapBuffer()		const { return mapBuffer;		}
	inline int				GetNumInstance()	const { return numInstance;		}

public:
	template<typename T>
	void AddElement(const T& object) {
		mapBuffer->SetMapBuffer(numInstance, object);
		map[numInstance] = object;
		numInstance++;
	}
	template<typename T>
	void RemoveElement(const T& object) {
		auto it = std::find(map.begin(), map.end(), object);

		if (it != map.end()) {
			int index = std::distance(map.begin(), it);
			mapBuffer->SetMapBuffer(index, map[numInstance - 1]);
			map[index] = map[numInstance - 1];

			numInstance--;
		}
	}

private:
	Buffer*			mapBuffer;
	std::vector<T>	map;
	int				numInstance = 0;
};