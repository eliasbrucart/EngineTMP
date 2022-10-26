#include "mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Engine;

Mesh::Mesh() {

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Shader& shader, Renderer* renderer) : Entity2D() {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_shader = shader;
	_renderer = renderer;
	SetUpMesh();
}

Mesh::~Mesh() {
	//if (_boundingVolume != NULL) {
	//	delete _boundingVolume;
	//	_boundingVolume = NULL;
	//}
}

void Mesh::SetUpMesh() {
	_renderer->GenerateVAO(_vao);

	_renderer->BindVAO(_vao);

	_renderer->GenerateVBO(_vbo);

	_renderer->UpdateMeshBuffers(_vbo, vertices.size() * sizeof(Vertex), &vertices[0]);

	_renderer->BindMeshEBO(_ebo, indices.size() * sizeof(unsigned int), &indices[0]);

	_renderer->SetMeshAttribPointers(_shader, 3, sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

	//_boundingVolume = GenerateAABB();
	//_boundingVolume->GenerateGlobalAABB(_parent);
	//_boundingVolume.GetGlobalAABB();
}

//AABB* Mesh::GenerateAABB() {
//	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
//	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
//
//	for (auto&& mesh : _meshes) {
//		for (auto&& vertex : vertices) {
//			minAABB.x = std::min(minAABB.x, vertex.Position.x);
//			minAABB.y = std::min(minAABB.y, vertex.Position.y);
//			minAABB.z = std::min(minAABB.z, vertex.Position.z);
//
//			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
//			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
//			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
//		}
//	}
//	return new AABB(minAABB, maxAABB);
//}

//AABB* Mesh::GetMeshAABB() {
//	return _boundingVolume;
//}

void Mesh::AddChildMesh(Mesh* children) {
	_meshesChildren.emplace_back(children);
	_meshesChildren.back()->_parentMesh = this;
}

void Mesh::SetCanDraw(bool value) {
	_canDraw = value;
}

bool Mesh::GetCanDraw() {
	return _canDraw;
}

void Mesh::Draw(Shader& shader, Frustum frustum) {
	UpdateMatrices();
	//UpdateSelfAndChild();
	//UpdateVectors();
	UpdateModel();
	//Pasar este codigo a renderer y que reciba como parametros todos los datos necesarios
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = textures[i].type;
		if (name == "diffuseM")
			number = std::to_string(diffuseNr++);
		else if (name == "specularM")
			number = std::to_string(specularNr++);
		//else if (name == "texture_normal")
		//	number = std::to_string(normalNr++); // transfer unsigned int to string
		//else if (name == "texture_height")
		//	number = std::to_string(heightNr++); // transfer unsigned int to string

		//setear el float de MaterialPro al shader
		//Acordarse de agregar los nuevos samplers de textura para la mesh en el struct MaterialPro
		glUniform1f(glGetUniformLocation(shader.GetID(), ("materialPro." + name).c_str()), i);
		//glUniform1f(glGetUniformLocation(shader.GetID(), (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//std::cout << "parent->children size: " << _parent->children.size() << std::endl;
	//if (/*_boundingVolume->IsOnFrustum(frustum, _parent) ||*/ _canDraw) //Para hacer el chequeo con el frsutum y que funcione por jerarquia, chequear por parent y no por this (malla actual)
		//_renderer->DrawMesh(shader, _vao, _vbo, vertices.size() * sizeof(Vertex), &vertices[0], indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), glm::vec3(1.0f) ,model.trs);
}