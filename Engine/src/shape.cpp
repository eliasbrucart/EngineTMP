#include "shape.h"
#include "renderer.h"
#include "GL/glew.h"

using namespace Engine;

Shape::Shape() : Entity2D() {
	_type = Type::triangle;
	_renderer = NULL;
	_material = new Material(MaterialType::esmerald); //Probando el material esmerald, hacer que el usuario eliga el material
}

Shape::Shape(Type type, Renderer* renderer, Shader shader) : Entity2D() {
	_type = type;
	_renderer = renderer;
	_shader = shader;
	_material = new Material(MaterialType::esmerald);
}

Shape::Shape(Type type, Renderer* renderer, Shader shader, const char* texPath, bool isTransparent) : Entity2D() {
	_renderer = renderer;
	_shader = shader;
	_type = type;
	_path = texPath;
	_transparency = isTransparent;
	_useTexture = true;
	_texImporter = new TextureImporter();

	if (_transparency)
		BlendSprite();

	LoadTexture(_path, _transparency);
}

Shape::~Shape() {
	UnbindBuffers();
	DeleteBuffer();
	if (_material != NULL) {
		delete _material;
		_material = NULL;
	}
	if (_texImporter != NULL) {
		delete _texImporter;
		_texImporter = NULL;
	}
}

void Shape::SetShader(Shader shader) {
	_shader = shader;
}

void Shape::GenerateVAO() {
	_renderer->GenerateVAO(_vao);
}

void Shape::BindVAO() {
	_renderer->BindVAO(_vao);
}

void Shape::GenerateLightVAO() {
	_renderer->GenerateLightVAO(_lightvao);
}

void Shape::BindLightVAO() {
	_renderer->BindLightVAO(_lightvao);
}

void Shape::BindBufferLight() {
	_renderer->BindBufferLight(_lightvbo);
}

void Shape::BindVBO(float* vertices, int verticesAmmount) {
	_renderer->BindVBO(_vbo, vertices, verticesAmmount);
}

void Shape::BindLightVBO(float* vertices, int verticesAmmount) {
	_renderer->BindLightVBO(_lightvbo, vertices, verticesAmmount);
}

void Shape::BindEBO(unsigned int* indices, int indicesAmmount) {
	_renderer->BindEBO(_ebo, indices, indicesAmmount);
}

void Shape::Init() {
	GenerateVAO();
	BindVAO();
	switch (_type)
	{
	case Engine::Type::triangle:
		BindVBO(_triVertices,18);
		BindEBO(_triIndices,3);
		_shader.SetVertexAttributes("position", 6);
		_shader.SetColorAttributes("color", 6);
		break;
	case Engine::Type::quad:
		BindVBO(_quadVertices, 24);
		BindEBO(_quadIndices, 6);
		_shader.SetVertexAttributes("position", 6);
		_shader.SetColorAttributes("color", 6);
		break;
	case Engine::Type::cube:
		BindVBO(_cubeTextureVertices, 396);
		BindEBO(_cubeIndices2, 36);
		_shader.SetVertexAttributes("position", 11);
		_shader.SetColorAttributes("color", 11);
		_shader.SetNormalAttributes("aNormal", 11);
		_shader.SetTypeOfshape("type", 0);
		break;
	case Engine::Type::lightCube:
		//GenerateLightVAO();
		//BindLightVAO();
		BindVBO(_cubeVertices2, 324);
		BindEBO(_cubeIndices2, 36);
		_shader.SetVertexAttributes("position",9);
		_shader.SetColorAttributes("color", 9);
		_shader.SetNormalAttributes("aNormal", 9);
		_shader.SetTextureAttributes("uv", 9); 
		break;

	case Engine::Type::textureCube:
		//GenerateLightVAO();
		//BindLightVAO();
		if (_useTexture) {
			LoadTexture(_path, _transparency);
			//_renderer->SetTexAttribPointer(_shader.GetID());
			BindVBO(_cubeTextureVertices, 396);
			BindEBO(_cubeIndices, 36);
			_shader.SetVertexAttributes("position", 11);
			_shader.SetColorAttributes("color", 11);
			_shader.SetNormalAttributes("aNormal", 11);
			_shader.SetTextureAttributes("uv", 11);
			_shader.SetTypeOfshape("type", 1);
			//_shader.SetVertexAttributes("aPos", 12);
			//_shader.SetColorAttributes("aColor", 12);
			//_shader.SetNormalAttributes("aNormal", 12);
			//_shader.SetTextureAttributes("aTexCoord", 12); //por ahora son 9, cuando se agregen las uv, el tamaño del vertice, crece.
		}
		//_shader.SetVertexAttributes("aPos", 12);
		//_shader.SetColorAttributes("aColor", 12);
		//_shader.SetNormalAttributes("aNormal", 9);
		break;
	}
	//Probar si estos se hace para todos los tipos de shape, si se cumple, 
	//hacer una condicion para que sean los que no son lightcube
	//_shader.SetColorAttributes("color", 6);
}

void Shape::Color(float r, float g, float b) {
	switch (_type)
	{
	case Engine::Type::triangle:
		_triVertices[3] = r;  _triVertices[4] = g;  _triVertices[5] = b;
		_triVertices[9] = r; _triVertices[10] = g; _triVertices[11] = b;
		_triVertices[15] = r; _triVertices[16] = g; _triVertices[17] = b;
		break;
	case Engine::Type::quad:
		_quadVertices[3] = r;  _quadVertices[4] = g;  _quadVertices[5] = b;
		_quadVertices[9] = r; _quadVertices[10] = g; _quadVertices[11] = b;
		_quadVertices[15] = r; _quadVertices[16] = g; _quadVertices[17] = b;
		_quadVertices[21] = r; _quadVertices[22] = g; _quadVertices[23] = b;
		break;
	}
}

void Shape::SetRenderer(Renderer* renderer){
	_renderer = renderer;
}

void Shape::Color(glm::vec3 color) {
	switch (_type)
	{
	case Engine::Type::triangle:
		_triVertices[3] = color.x;  _triVertices[4] = color.y;  _triVertices[5] = color.z;
		_triVertices[9] = color.x; _triVertices[10] = color.y; _triVertices[11] = color.z;
		_triVertices[15] = color.x; _triVertices[16] = color.y; _triVertices[17] = color.z;
		break;
	case Engine::Type::quad:
		_quadVertices[3] = color.x;  _quadVertices[4] = color.y;  _quadVertices[5] = color.z;
		_quadVertices[9] = color.x; _quadVertices[10] = color.y; _quadVertices[11] = color.z;
		_quadVertices[15] = color.x; _quadVertices[16] = color.y; _quadVertices[17] = color.z;
		_quadVertices[21] = color.x; _quadVertices[22] = color.y; _quadVertices[23] = color.z;
		break;
	}
}

void Shape::Draw() {
	UpdateMatrices();
	switch (_type)
	{
	case Engine::Type::triangle:
		_renderer->Draw(_shader, GetModel(), _vao, _vbo, _triVertices, 18, _triIndices, 3, _material);
		break;
	case Engine::Type::quad:
		_renderer->Draw(_shader, GetModel(), _vao, _vbo, _quadVertices, 24, _quadIndices, 6, _material);
		break;
	case Engine::Type::cube:
		_renderer->Draw(_shader, GetModel(), _vao, _vbo, _cubeTextureVertices, 396, _cubeIndices2, 36, _material);
		break;
	case Engine::Type::lightCube:
		_renderer->DrawLightCube(_shader, GetModel(), _vao, _vbo, _cubeVertices2, 324, _cubeIndices2, 36);
		break;
	case Engine::Type::textureCube:
		if (_useTexture) {
			if (_transparency) {
				BlendSprite();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
				glActiveTexture(GL_TEXTURE0);
				_renderer->DrawSprite(_shader, _vao, _vbo, _cubeTextureVertices, 396, _cubeIndices, 36, GetModel());
				UnBlendSprite();
				glDisable(GL_TEXTURE_2D);

			}
			else {
				glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
				glActiveTexture(GL_TEXTURE0);
				_renderer->DrawSprite(_shader, _vao, _vbo, _cubeTextureVertices, 396, _cubeIndices, 36, GetModel());
				glDisable(GL_TEXTURE_2D);
			}
		}
		break;
	}

	//if (_useTexture) {
	//
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//	glDisable(GL_TEXTURE_2D);
	//
	//	if (_transparency)
	//		UnBlendSprite();
	//}
}

void Shape::LoadTexture(const char* texPath, bool transparency) {
	if (_texImporter) {
		_texImporter->SetPath(texPath);
		_texImporter->LoadImage(_width, _height, transparency);
	}
	else
		std::cout << "Couldn't find image" << std::endl;
}

void Shape::UnbindBuffers() {
	_renderer->UnbindBuffers();
}

void Shape::DeleteBuffer() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo, _lightvao);
}

void Shape::BlendSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Shape::UnBlendSprite() {
	glDisable(GL_BLEND);
}