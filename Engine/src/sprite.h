#ifndef SPRITE_H
#define SPRITE_H
#include"shape.h"
#include"export.h"
#include"texture_importer.h"
#include"renderer.h"
#include"material.h"

namespace Engine {
	class Animation;
	class Time;

	struct ENGINE_API UVs {
		float u;
		float v;
	};

	class ENGINE_API Sprite : public Entity2D {
	private:
		int _width = 0;
		int _height = 0;
		bool _transparency;
		Renderer* _renderer;
		TextureImporter* _texImporter;
		Material* _material;
		UVs uv[4];
		unsigned int _texture = 0;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		float _vertices[32] = {
				1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 1,
				1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 0,
			   -1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 0,
			   -1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 1
		};

		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};

		float _cubeVertices2[396] = {
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,//0
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,//1
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,//2
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,//3
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,//4
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,//5

			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,//6
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 0.0f,//7
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,//8
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,//9
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  0.0f, 1.0f,//10
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,//11

			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,//12
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,//13
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,//14
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,//15
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,//16
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,//17

			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,//18
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,//19
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,//20
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,//21
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,//22
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,//23

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,//24
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,//25
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,//26
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,//27
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,//28
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,//29

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,//30
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,//31
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,//32
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,//33
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,//34
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f//35
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
		Shader shader;

		void GenerateVAO();
		void BindVAO();
		void BindVBO();
		void BindEBO();
		void UnbindBuffers();
		void DeleteBuffer();
		void BindBuffers();
		void BindTexture();
		void BlendSprite();
		void UnBlendSprite();
		void LoadSprite();
		void LoadSprite(const char* path);
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
	public:
		Sprite();
		Sprite(bool transparency, Renderer* renderer, Shader shader);
		Sprite(bool transparency, const char* path, Renderer* renderer, Shader shader);
		Sprite(bool transparency, const char* path, Renderer* renderer, Shader shader, MaterialType materialType);
		~Sprite();
		void Init();
		void Init(unsigned int texture);
		void Color(float r, float g, float b);
		void Color(glm::vec3 color);
		void SetUVs(glm::vec4 uvRect);
		void SetUVs(float sheetHeight, float sheetWidth, float spriteHeight, float spriteWidth, int x, int y);
		void UpdateUVs();
		void DrawSprite();
		void DrawFromUVs(glm::vec4 uv);
		void DrawAnimation(glm::vec4 uv);
		void SetRenderer(Renderer* renderer);
		void SetShader(Shader shader);
		Renderer* GetRenderer();
		void SetPath(const char* path);
		const char* GetPath();
		void SetTransparency(bool value);
	};
}

#endif