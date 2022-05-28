#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "texture_importer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <iostream>	

#define STBI_FAILURE_USERMSG

using namespace Engine;

TextureImporter::TextureImporter() {
	_texture = 0;
	_path = NULL;
}

TextureImporter::TextureImporter(const char* path) {
	_texture = 0;
	_path = path;
}

TextureImporter::TextureImporter(int width, int height, const char* path, bool transparency) {
	_texture = 0;
	_path = path;
	LoadImage(width, height, transparency);
}

TextureImporter::~TextureImporter() {
}

void TextureImporter::LoadImage(int& width, int& height, bool transparency) {
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	if (transparency)
		_data = stbi_load(_path, &width, &height, &nrChannels, STBI_rgb_alpha);
	else
		_data = stbi_load(_path, &width, &height, &nrChannels, STBI_rgb);

	if (_data) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		if (!transparency)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << " - " << stbi_failure_reason() << std::endl;
	}
	stbi_image_free(_data);
}

unsigned int TextureImporter::TextureFromFile(const char* path, const string& directory) {
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void TextureImporter::SetPath(const char* path) {
	_path = path;
}

const char* TextureImporter::GetPath() {
	return _path;
}

unsigned int TextureImporter::GetTexture() {
	return _texture;
}