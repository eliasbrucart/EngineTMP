#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "renderer.h"
#include "shader.h"
#include "entity2D.h"
#include "input.h"
#include "time_manager.h"

struct GLFWwindow;

namespace Engine {

	enum class ENGINE_API ProjectionType {
		orthographic, perspective
	};

	class ENGINE_API Camera : public Entity2D{
	private:
		Renderer* _renderer;
		ProjectionType _type;
		glm::mat4 _view;
		glm::mat4 _projection;
		Input inputCam;
		Time time;
		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
	public:
		Camera(Renderer* renderer, ProjectionType type);
		~Camera();
		void SetView(glm::vec3 direction, glm::vec3 up);
		void SetProjection(ProjectionType type);
		void Init(Shader& shader, GLFWwindow* window);
		//void SetLookAt(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 upVector);
		void SetLookAt();
		void SetCameraPos(glm::vec3 cameraPos);
		void SetCameraFront(glm::vec3 cameraFront);
		void SetCameraUp(glm::vec3 cameraUp);
		glm::vec3 GetCameraPos();
		glm::vec3 GetCameraFront();
		glm::vec3 GetCameraUp();
		void RotateCamera();
		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::mat4 GetMVP();
		ProjectionType GetProjectionType();
		void Draw(Shader& shader);
	};

}

#endif // !CAMERA_H

