#include "mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Engine;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Shader shader, Renderer* renderer) : Entity2D() {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	_shader = shader;

	SetUpMesh();
}

Mesh::~Mesh() {

}

void Mesh::SetUpMesh() {
	//Pasar a renderer el setup del mesh ya que genera buffers y los bindea.

	_renderer->GenerateVAO(_vao);

	_renderer->BindVAO(_vao);

	_renderer->GenerateVBO(_vbo);

	_renderer->UpdateMeshBuffers(_vbo, vertices.size() * sizeof(Vertex), &vertices[0]);

	_renderer->BindMeshEBO(_ebo, indices.size() * sizeof(unsigned int), &indices[0]);

	_renderer->SetMeshAttribPointers(_shader, 3, sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords));
	//_shader.SetMeshVertexAttributes("position", 3, sizeof(Vertex), 0);
	//_shader.SetMeshVertexAttributes("aNormal", 3, sizeof(Vertex), offsetof(Vertex, Normal));
	//_shader.SetMeshVertexAttributes("uv", 2, sizeof(Vertex), offsetof(Vertex, TexCoords));

	//glGenVertexArrays(1, &_vao);
	//glGenBuffers(1, &_vbo);
	//glGenBuffers(1, &_ebo);
	//
	//glBindVertexArray(_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	//
	//_shader.SetTypeOfshape("type", 2);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//
	////Especificar al shader las posiciones, las normales y las uv del mesh
	//_positionAttrib = glGetAttribLocation(_shader.GetID(), "position");
	//glVertexAttribPointer(_positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//glEnableVertexAttribArray(_positionAttrib);
	//
	//_normalAttrib = glGetAttribLocation(_shader.GetID(), "aNormal");
	//glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	//glEnableVertexAttribArray(_normalAttrib);
	//
	//_textureAttrib =  glGetAttribLocation(_shader.GetID(), "uv");
	//glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//glEnableVertexAttribArray(_textureAttrib);

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) {
	UpdateMatrices();
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

	//Esto pasarlo a renderer
	_renderer->BindVAO(_vao);
	_renderer->UpdateMeshBuffers(_vbo, vertices.size() * sizeof(Vertex), &vertices[0]);
	//_renderer->DrawMesh(_shader, _vao, _vbo, indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), GetModel());

	//glBindVertexArray(_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//
	shader.Use(GetModel());
	//
	shader.SetTypeOfshape("type", 2);
	_renderer->SetMeshAttribPointers(shader, 3, sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords));
	//
	//_positionAttrib = glGetAttribLocation(shader.GetID(), "position");
	//glVertexAttribPointer(_positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//glEnableVertexAttribArray(_positionAttrib);
	//
	//_normalAttrib = glGetAttribLocation(shader.GetID(), "aNormal");
	//glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	//glEnableVertexAttribArray(_normalAttrib);
	//
	//_textureAttrib = glGetAttribLocation(shader.GetID(), "uv");
	//glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//glEnableVertexAttribArray(_textureAttrib);
	//
	////glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//
	//
	//glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glActiveTexture(GL_TEXTURE0);
}