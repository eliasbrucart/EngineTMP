#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"
#include "shader.h"
#include "material.h"
#include <mat4x4.hpp>

//forward declaration of GLFWwindow
struct GLFWwindow;

namespace Engine {
	class ENGINE_API Renderer {
	public:
		Renderer();
		~Renderer();

		bool InitializeGlew();
		void BeginFrame(float r, float g, float b);
		void EndFrame(GLFWwindow* window);
		void GenerateVAO(unsigned int& vao);
		void BindVAO(unsigned int& vao);
		void GenerateLightVAO(unsigned int& lightvao);
		void BindLightVAO(unsigned int& lightvao);
		void BindBufferLight(unsigned int& vbo);
		void BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
		void BindLightVBO(unsigned int& lightvbo, float* vertices, int verticesAmmount);
		void BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
		void UpdateBuffers(unsigned int& vbo, float* vertices, int verticesAmmount);
		void UnbindBuffers();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, unsigned int& lightvao);
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
		void CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition);
		//void SetTexAttribPointer(unsigned int shaderID);
		void Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, Material* material);
		void DrawLightCube(Shader& shader, glm::mat4 model, unsigned int& vao , unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount);
		void DrawBasicLight(Shader& shader, glm::vec3 lightPos, glm::vec3 lightColor);
		void DrawSprite(Shader &shader, unsigned int &vao, unsigned int &vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, glm::mat4 model);
		void DrawCamera(Shader& shader, glm::vec3 camPos, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	};
}

#endif // !Renderer

