#ifndef SHAPE_H
#define SHAPE_H
#include "export.h"
#include "entity2D.h"
#include "shader.h"
#include "renderer.h"
namespace Engine {

	enum class ENGINE_API Type
	{
		triangle, quad, cube, lightCube
	};

	class ENGINE_API Shape : public Entity2D {
	private:
		unsigned int _vao = 0;
		unsigned int _lightvao = 0;
		unsigned int _vbo = 0;
		unsigned int _lightvbo = 0;
		unsigned int _ebo = 0;

		float _triVertices[18] = {
			-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
			 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int _triIndices[3] = {
			0,1,2
		};
		float _quadVertices[24] = {
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		   -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top left 
		};
		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};

		float _cubeVertices[48] = {
			-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
		};

		float _cubeVertices2[324] = {
			-0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f,  0.0f, -1.0f,//0
			 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,//1
			 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,//2
			 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,//3
			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,//4
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,//5

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,//6
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,//7
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,//8
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,//9
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,//10
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,//11

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,//12
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,//13
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,//14
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,//15
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,//16
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,//17

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,//18
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,//19
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,//20
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,//21
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,//22
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,//23

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,//24
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,//25
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,//26
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,//27
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,//28
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,//29

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,//30
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,//31
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,//32
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,//33
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,//34
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f//35
		};

		unsigned int _cubeIndices[36] = {
			0,1,2,
			2,3,0,
			1,5,6,
			6,2,1,
			7,6,5,
			5,4,7,
			4,0,3,
			3,7,4,
			4,5,1,
			1,0,4,
			3,2,6,
			6,7,3
		};

		unsigned int _cubeIndices2[36] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17,
			18,19,20,
			21,22,23,
			24,25,26,
			27,28,29,
			30,31,32,
			33,34,35
		};

		Type _type;
		Renderer* _renderer;
		Shader _shader;

		void GenerateVAO();
		void BindVAO();
		void GenerateLightVAO();
		void BindLightVAO();
		void BindBufferLight();
		void BindVBO(float* vertices, int verticesAmmount);
		void BindLightVBO(float* vertices, int verticesAmmount);
		void BindEBO(unsigned int* indices, int indicesAmmount);
		void UnbindBuffers();
		void DeleteBuffer();
	public:
		Shape();
		Shape(Type type, Renderer* renderer, Shader shader);
		~Shape();
		void SetRenderer(Renderer* renderer);
		void SetShader(Shader shader);
		void Init();
		void Color(float r, float g, float b);
		void Color(glm::vec3 color);
		void Draw();

	};

}
#endif // !SHAPE_H

