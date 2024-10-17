#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace me::render::object {
	class Buffer
	{
	public:
		explicit Buffer();
		~Buffer() noexcept;

	private:
		uint32_t buffer;
		void* mappedBuffer;

	public:
		inline uint32_t GetBuffer() const { return buffer; }

	public:
		template<typename T> void InitBuffer(std::vector<T> value) {
			InitBuffer(value.size() * sizeof(T), value.data());
		}
		template<typename T> void InitBuffer(std::vector<T> value, int size) {
			InitBuffer(size * sizeof(T), value.data());
		}
		template<typename T> void SetMapBuffer(int index, const T& data) {
			if (mappedBuffer)
				static_cast<T*>(mappedBuffer)[index] = data;
		}

		void InitBuffer(int size, void* value);
		void SubData(int offset, int size, void* data);
	};
}
