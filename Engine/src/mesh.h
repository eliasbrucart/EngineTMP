#ifndef MESH_H
#define MESH_H

#include <glm.hpp>

#include "shader.h"
#include "entity2D.h"
#include "renderer.h"

#include <vector>
#include <string>

#include "export.h"
using namespace std;

namespace Engine {
	struct ENGINE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	
	struct ENGINE_API Texture {
		unsigned int id;
		string type;
		string path;
	};

	class ENGINE_API Mesh : public Entity2D {
	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _positionAttrib;
		unsigned int _normalAttrib;
		unsigned int _textureAttrib;
		Shader _shader;
		void SetUpMesh();
	public:
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		~Mesh();
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		void Draw(Shader& shader);
	};
}

#endif