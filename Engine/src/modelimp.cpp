#include "modelimp.h"

#include "GL/glew.h"
using namespace Engine;

ModelImp::ModelImp() {
    _path = "";
    _directory = "";
}

ModelImp::ModelImp(string path, const char* modelTexture, Shader shader) : Entity2D(){
    _modelTexture = modelTexture;
    LoadModel(path);
    //_directory = directory;
    //_shader.SetTypeOfshape("type", 2);
    _shader = shader;
    //_texImporter = new TextureImporter(modelTexture);
    //LoadTexture();
}

ModelImp::ModelImp(string path) {
    LoadModel(path);
}

ModelImp::~ModelImp() {
    if (_texImporter != NULL) {
        delete _texImporter;
        _texImporter = NULL;
    }
}

void ModelImp::MoveModel(glm::vec3 direction) {
    for (int i = 0; i < _meshes.size(); i++) {
        _meshes[i].Translate(direction.x, direction.y, direction.z);
        //_meshes[i].transform.position = _meshes[i].transform.position + (direction * speed * timer.GetDeltaTime());
        //_meshes[i].Translate(_meshes[i].transform.position.x, _meshes[i].transform.position.y, _meshes[i].transform.position.z);
    }
}

void ModelImp::LoadModel(string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));

    if(scene)
        ProcessNode(scene->mRootNode, scene);
}

void ModelImp::ProcessNode(aiNode* node, const aiScene* scene) {
    std::cout << "Entro en ProcessNode!!!" << std::endl;
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh ModelImp::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        //Procesar las posiciones, normales y uvs de los vertices de cada una de la mesh
        //Necesitmaos un vector temporal para los datos de Assimp, eso se hace ya que Assimp tiene sus propios tipos de datos para vectores, matrices, etc.
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //Aca hacemos lo mismo que en el paso anterior solo que con los datos de los vectores normales
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    //Procesar los indices que apuntan a cada mesh
    //Cada mesh contiene una matriz de caras, cada cara contiene vertices, que estos se refieren con sus indices
    //los indices indican en que orden dibujar los vertices para cada primitiva.
    //Y eso termina siendo una cara, una primitiva.

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    //Procesar material de la mesh
    //if (mesh->mMaterialIndex >= 0) {
    //    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    //    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //
    //    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //
    //    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //}


    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    std::cout << "Entro en ProcessMesh!!!" << std::endl;

    return Mesh(vertices, indices, textures, _shader);
}

vector<Texture> ModelImp::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < _textures_loaded.size(); j++) {
            if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->_directory, false);
            //texture.id = TextureModel(_modelTexture);
            texture.type = typeName;
            texture.path = str.C_Str();
            //texture.path = _modelTexture;
            textures.push_back(texture);
            _textures_loaded.push_back(texture);
        }
    }

    std::cout << "Entro en LoadMaterialTextures!!!" << std::endl;

    return textures;
}

//void ModelImp::SetModelPath(string path) {
//    _path = path;
//}
//
//void ModelImp::SetTexturePath(const char* texturePath) {
//    _directory = texturePath;
//}

void ModelImp::Draw(Shader& shader) {
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i].Draw(shader);
}

unsigned int ModelImp::TextureFromFile(const char* path, string const &directory,bool gamma) {
    string filename = string(path);
    filename = directory + '/' + path;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void ModelImp::LoadTexture() {
    if (_texImporter) {
        _texImporter->LoadImage(_width, _height, _transparency);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());

        unsigned int textureDiffuseLoc = glGetUniformLocation(_shader.GetID(), "texture_diffuse1");
        glUniform1i(textureDiffuseLoc, _texImporter->GetTexture());

        glDisable(GL_TEXTURE_2D);
    }
}

unsigned int ModelImp::TextureModel(const char* texture) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(texture, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << texture << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}