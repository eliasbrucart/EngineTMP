#include "entity.h"
//#include "renderer.h"

namespace Engine
{
	const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

	Entity::Entity()
	{
		_renderer = NULL;
		worldModel = glm::mat4(1.0f);
		localModel = glm::mat4(1.0f);
		parentModel = glm::mat4(1.0f);
		localTranslate = glm::mat4(1.0f);
		localRotateX = glm::mat4(1.0f);
		localRotateY = glm::mat4(1.0f);
		localRotateZ = glm::mat4(1.0f);
		localScale = glm::mat4(1.0f);

		v3localPos = glm::vec3(0.0f);
		v3localRot = glm::vec3(0.0f);
		v3localScale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));

		useLocalMatrix = false;
	}

	Entity::~Entity()
	{

	}

	glm::vec3 Entity::getForward()
	{
		glm::quat rotation = eulerToQuat(v3localRot);

		return quatToVec(rotation, glm::vec3(0.f, 0.f, 1.f));
	}

	glm::vec3 Entity::toEulerRad(glm::quat rot)
	{
		float sqw = rot.w * rot.w;
		float sqx = rot.x * rot.x;
		float sqy = rot.y * rot.y;
		float sqz = rot.z * rot.z;
		float unit = sqx + sqy + sqz + sqw;
		float test = rot.x * rot.w - rot.y * rot.z;

		glm::vec3 v = glm::vec3();

		if (test > 0.4995f * unit)
		{
			v.y = 2.f * atan2(rot.y, rot.x);
			v.x = glm::pi<float>() / 2.f;
			v.z = 0.f;

			return normalizeAngles(v * 57.29578f);
		}
		if (test < -0.4995f * unit)
		{
			v.y = -2.f * atan2(rot.y, rot.x);
			v.x = -glm::pi<float>() / 2.f;
			v.z = 0.f;

			return normalizeAngles(v * 57.29578f);
		}

		glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
		v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
		v.x = asin(2.f * (q.x * q.z - q.w * q.y));
		v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));

		return normalizeAngles(v * 57.29578f);
	}

	glm::vec3 Entity::normalizeAngles(glm::vec3 angles)
	{
		angles.x = normalizeAngle(angles.x);
		angles.y = normalizeAngle(angles.y);
		angles.z = normalizeAngle(angles.z);

		return angles;
	}

	float Entity::normalizeAngle(float angle)
	{
		while (angle > 360.f)
			angle -= 360.f;
		while (angle < 0.f)
			angle += 360.f;

		return angle;
	}

	glm::quat Entity::getRotationByMatrix(glm::mat4 mat)
	{
		glm::vec3 s = getScale(mat);

		float m00 = mat[0].x / s.x;
		float m01 = mat[0].y / s.y;
		float m02 = mat[0].z / s.z;
		float m10 = mat[1].x / s.x;
		float m11 = mat[1].y / s.y;
		float m12 = mat[1].z / s.z;
		float m20 = mat[2].x / s.x;
		float m21 = mat[2].y / s.y;
		float m22 = mat[2].z / s.z;

		glm::quat q = glm::quat();
		q.w = glm::sqrt(glm::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
		q.x = glm::sqrt(glm::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
		q.y = glm::sqrt(glm::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
		q.z = glm::sqrt(glm::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
		q.x *= glm::sign(q.x * (m21 - m12));
		q.y *= glm::sign(q.y * (m02 - m20));
		q.z *= glm::sign(q.z * (m10 - m01));

		float qMagnitude = glm::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
		q.w /= qMagnitude;
		q.x /= qMagnitude;
		q.y /= qMagnitude;
		q.z /= qMagnitude;

		return q;
	}

	glm::quat Entity::eulerToQuat(glm::vec3 euler)
	{
		euler *= deg2rad;

		float cy = cos(euler.z * 0.5f);
		float sy = sin(euler.z * 0.5f);
		float cp = cos(euler.x * 0.5f);
		float sp = sin(euler.x * 0.5f);
		float cr = cos(euler.y * 0.5f);
		float sr = sin(euler.y * 0.5f);

		glm::quat q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = cr * sp * cy + sr * cp * sy;
		q.y = sr * cp * cy - cr * sp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	glm::vec3 Entity::quatToVec(glm::quat quat, glm::vec3 vec)
	{
		float x2 = quat.x * 2.f;
		float y2 = quat.y * 2.f;
		float z2 = quat.z * 2.f;
		float xx2 = quat.x * x2;
		float yy2 = quat.y * y2;
		float zz2 = quat.z * z2;
		float xy2 = quat.x * y2;
		float xz2 = quat.x * z2;
		float yz2 = quat.y * z2;
		float wx2 = quat.w * x2;
		float wy2 = quat.w * y2;
		float wz2 = quat.w * z2;

		glm::vec3 res;
		res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
		res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
		res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
		return res;
	}

	void Entity::updateModelMatrix()
	{
		if (useLocalMatrix)
		{
			localModel = localTranslate * localRotateX * localRotateY * localRotateZ * localScale;
			worldModel = parentModel * localModel;
		}
		else
		{
			worldModel = localTranslate * localRotateX * localRotateY * localRotateZ * localScale;
		}
	}
	void Entity::setPos(glm::vec3 pos)
	{
		v3localPos = pos;
		localTranslate = glm::translate(glm::mat4(1.0f), v3localPos);
		updateModelMatrix();
	}
	void Entity::setPos(float x, float y, float z)
	{
		setPos(glm::vec3(x, y, z));
	}
	void Entity::setRot(glm::vec3 rot)
	{
		setRotX(rot.x);
		setRotY(rot.y);
		setRotZ(rot.z);
		updateModelMatrix();
	}
	void Entity::setRotRadians(glm::vec3 rot)
	{
		setRotX(glm::radians(rot.x));
		setRotY(glm::radians(rot.y));
		setRotZ(glm::radians(rot.z));
		updateModelMatrix();
	}
	void Entity::setRot(float x, float y, float z)
	{
		setRotX(x);
		setRotY(y);
		setRotZ(z);
		updateModelMatrix();
	}
	void Entity::setRotX(float x)
	{
		v3localRot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		localRotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void Entity::setRotY(float y)
	{
		v3localRot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		localRotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void Entity::setRotZ(float z)
	{
		v3localRot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		localRotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
	void Entity::setScale(glm::vec3 localScale)
	{
		v3localScale = localScale;
		this->localScale = glm::scale(glm::mat4(1.0f), v3localScale);
		updateModelMatrix();
	}
	void Entity::setScale(float x, float y, float z)
	{
		setScale(glm::vec3(x, y, z));
	}
	void Entity::setColor(glm::vec4 color)
	{
		this->color = color;
	}
	void Entity::setColor(float r, float g, float b, float a)
	{
		color = glm::vec4(r, g, b, a);
	}
	void Entity::setWorldModelWithParentModel(glm::mat4 parentModel)
	{
		this->parentModel = parentModel;

		updateModelMatrix();
	}
	glm::vec4 Entity::getColor()
	{
		return color;
	}
	glm::vec3 Entity::getPos()
	{
		return v3localPos;
		//return worldModel[3];
	}
	glm::vec3 Entity::getPosFromTransformMatrix()
	{
		return worldModel[3];
	}
	glm::vec3 Entity::getRot()
	{
		return v3localRot;
	}
	glm::vec3 Entity::getScale()
	{
		return v3localScale;
	}
	glm::vec3 Entity::getPos(glm::mat4 mat)
	{
		return glm::vec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	glm::vec3 Entity::getRot(glm::mat4 mat)
	{
		return toEulerRad(getRotationByMatrix(mat));
	}

	glm::vec3 Entity::getScale(glm::mat4 mat)
	{
		glm::vec4 m0 = glm::vec4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
		glm::vec4 m1 = glm::vec4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
		glm::vec4 m2 = glm::vec4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);

		return glm::vec3(glm::length(m0), glm::length(m1), glm::length(m2));
	}
	glm::mat4 Entity::getModel()
	{
		return worldModel;
	}
	glm::mat4 Entity::getLocalModel()
	{
		return localModel;
	}
	void Entity::invertX()
	{
		setRotY(-3.14169265f);
		updateModelMatrix();
	}
	void Entity::invertY()
	{
		setRotZ(-3.14169265f);
		updateModelMatrix();
	}
	void Entity::invertZ()
	{
		setRotX(-3.14169265f);
		updateModelMatrix();
	}
	void Entity::setMatrix(glm::mat4 mat)
	{
		setPos(getPos(mat));
		setRotRadians(getRot(mat));
		setScale(getScale(mat));
	}
	void Entity::UseLocalMatrix()
	{
		useLocalMatrix = true;
	}
}