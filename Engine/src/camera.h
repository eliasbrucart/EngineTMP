#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "renderer.h"
#include "shader.h"
#include "entity2D.h"
#include "input.h"
#include "time_manager.h"

using namespace std;

struct GLFWwindow;

namespace Engine {

	enum class ENGINE_API ProjectionType {
		orthographic, perspective
	};

	enum class ENGINE_API CamMode {
		firstPerson, thirdPerson
	};

	class ENGINE_API Camera : public Entity2D{
	private:
		Renderer* _renderer;
		ProjectionType _type;
		CamMode _mode;
		glm::mat4 _view;
		glm::mat4 _projection;
		Input inputCam;
		Time time;
		float _roll;
		float _yaw;
		float _pitch;
		bool _firstMouse;
		float _rotationAngle;
	public:
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		glm::vec3 _cameraRight;
		Camera(Renderer* renderer, ProjectionType type, CamMode mode);
		~Camera();
		void SetView(glm::vec3 direction, glm::vec3 up);
		void SetProjection(ProjectionType type);
		void Init(Shader& shader, GLFWwindow* window);
		void SetCameraMode(CamMode mode);
		void SetLookAt(glm::vec3 forward);
		void FollowTarget(glm::vec3 positionTarget);
		void SetCameraFront(glm::vec3 cameraFront);
		void SetCameraUp(glm::vec3 cameraUp);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		float GetYaw();
		float GetPitch();
		void RotateYaw(float yaw);
		void RotatePitch(float pitch);
		glm::vec3 GetCameraFront();
		glm::vec3 GetCameraUp();
		void UpdateRotation();
		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::mat4 GetMVP();
		ProjectionType GetProjectionType();
		void Draw(Shader& shader);
	};

}

#endif // !CAMERA_H

