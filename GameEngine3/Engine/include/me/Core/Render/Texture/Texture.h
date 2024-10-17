#pragma once

namespace me::core::render {
	class Texture
	{
	public:
		explicit Texture(const char* path);
		~Texture() noexcept = default;

		void BindTexture(unsigned int id);

	public:
		int width, height, nrChannels;

	private:
		unsigned char* data;
		unsigned int texture;

	private:
		void LoadTexture(const char* path);
	};
}