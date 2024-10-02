#include <RendererObject/Map.h>

#include <RendererObject/Buffer.h>
#include <vector>
#include <algorithm>

Map::Map()
{
	mapBuffer = new Buffer();
	mapBuffer->InitBuffer(sizeof(glm::vec3) * 500, nullptr);

	for (int i = 0; i < 500; i++) {
		map.push_back(glm::vec3(-9999999));
	}
}

void Map::AddElement(glm::vec3 object)
{
	mapBuffer->SetMapBuffer(numInstance, object);
	map[numInstance] = object;
	numInstance++;
}
void Map::RemoveElement(glm::vec3 object)
{
	auto it = std::find(map.begin(), map.end(), object);

	if (it != map.end()) {
		int index = std::distance(map.begin(), it);
		mapBuffer->SetMapBuffer(index, map[numInstance - 1]);
		map[index] = map[numInstance - 1];

		numInstance--;
	}
}