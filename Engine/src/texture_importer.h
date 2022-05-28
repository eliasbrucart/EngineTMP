#ifndef TEXTURE_IMPORTER
#define TEXTURE_IMPORTER

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "export.h"

using namespace std;

namespace Engine {

	class ENGINE_API TextureImporter {
	private:
		const char* _path;
		unsigned char* _data;
		unsigned int _texture;
		int nrChannels;
	public:
		TextureImporter();
		TextureImporter(const char* path);
		TextureImporter(int width, int height, const char* path, bool transparency);
		~TextureImporter();
		void LoadImage(int& width, int& height, bool transparency);
		unsigned int TextureFromFile(const char* path, const string& directory);
		void SetPath(const char* path);
		const char* GetPath();
		unsigned int GetTexture();
	};

}
#endif