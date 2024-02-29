#include "MeshBufferVAO.h"
#include "Model.h"

MeshBufferVAO::MeshBufferVAO()
{
	
}

MeshBufferVAO::~MeshBufferVAO()
{
	if (model != nullptr)
	{
		delete model;
	}
	if (Bounds != nullptr)
	{
		delete Bounds;
	}

	// Free VAO and mesh buffers from memory.
	glDeleteBuffers(1, &points_vbo);
	glDeleteBuffers(1, &texcoords_vbo);
	glDeleteBuffers(1, &normals_vbo);
	glDeleteBuffers(1, &tangents_vbo);
	glDeleteBuffers(1, &bitangents_vbo);

	glDeleteVertexArrays(1, &vao);
}

void AppendModelBuffersTriangle(AABB* Bounds,
	Vector3f* v0, Vector3f* v1, Vector3f* v2,
	Vector2f* t0, Vector2f* t1, Vector2f* t2,
	Vector3f* n0, Vector3f* n1, Vector3f* n2,
	std::vector<GLfloat>** verticies,
	std::vector<GLfloat>** texCoords,
	std::vector<GLfloat>** normals,
	std::vector<GLfloat>** tangents,
	std::vector<GLfloat>** bitangents)
{
	int j;
	Vector3f* tangent = new Vector3f();
	Vector3f* bitangent = new Vector3f();

	// Extend the bounds
	Bounds->Add(v0);
	Bounds->Add(v1);
	Bounds->Add(v2);

	// Vertex Coordinates
	(*verticies)->push_back(v0->x);
	(*verticies)->push_back(v0->y);
	(*verticies)->push_back(v0->z);

	(*verticies)->push_back(v1->x);
	(*verticies)->push_back(v1->y);
	(*verticies)->push_back(v1->z);

	(*verticies)->push_back(v2->x);
	(*verticies)->push_back(v2->y);
	(*verticies)->push_back(v2->z);

	// Texture Coordinates
	(*texCoords)->push_back(t0->x);
	(*texCoords)->push_back(t0->y);

	(*texCoords)->push_back(t1->x);
	(*texCoords)->push_back(t1->y);

	(*texCoords)->push_back(t2->x);
	(*texCoords)->push_back(t2->y);

	// Tangents and Bitangents
	TriangleTangentSpace(v0, v1, v2, t0, t1, t2, &tangent, &bitangent);

	// Normal Coordinates
	//Vector3 normal;
	//ComputeTangentBasis(v0, v1, v2, t0, t1, t2, normal, tangent, bitangent);
	//n0 = normal;
	//n1 = normal;
	//n2 = normal;

	(*normals)->push_back(n0->x);
	(*normals)->push_back(n0->y);
	(*normals)->push_back(n0->z);

	(*normals)->push_back(n1->x);
	(*normals)->push_back(n1->y);
	(*normals)->push_back(n1->z);

	(*normals)->push_back(n2->x);
	(*normals)->push_back(n2->y);
	(*normals)->push_back(n2->z);

	for (j = 0; j <= 2; j++)
	{
		// Add the same data for each vertex 

		(*tangents)->push_back(tangent->x);
		(*tangents)->push_back(tangent->y);
		(*tangents)->push_back(tangent->z);

		(*bitangents)->push_back(bitangent->x);
		(*bitangents)->push_back(bitangent->y);
		(*bitangents)->push_back(bitangent->z);
	}
}

void AppendModelBuffersQuad(AABB* Bounds,
	Vector3f* v0, Vector3f* v1, Vector3f* v2, Vector3f* v3,
	Vector2f* t0, Vector2f* t1, Vector2f* t2, Vector2f* t3,
	Vector3f* n0, Vector3f* n1, Vector3f* n2, Vector3f* n3,
	std::vector<GLfloat>** verticies,
	std::vector<GLfloat>** texCoords,
	std::vector<GLfloat>** normals,
	std::vector<GLfloat>** tangents,
	std::vector<GLfloat>** bitangents)
{
	int j;
	Vector3f* tangent = new Vector3f();
	Vector3f* bitangent = new Vector3f();

	// Extend the bounds
	Bounds->Add(v0);
	Bounds->Add(v1);
	Bounds->Add(v2);

	// Vertex Coordinates
	(*verticies)->push_back(v0->x);
	(*verticies)->push_back(v0->y);
	(*verticies)->push_back(v0->z);

	(*verticies)->push_back(v1->x);
	(*verticies)->push_back(v1->y);
	(*verticies)->push_back(v1->z);

	(*verticies)->push_back(v2->x);
	(*verticies)->push_back(v2->y);
	(*verticies)->push_back(v2->z);

	(*verticies)->push_back(v3->x);
	(*verticies)->push_back(v3->y);
	(*verticies)->push_back(v3->z);

	// Texture Coordinates
	(*texCoords)->push_back(t0->x);
	(*texCoords)->push_back(t0->y);

	(*texCoords)->push_back(t1->x);
	(*texCoords)->push_back(t1->y);

	(*texCoords)->push_back(t2->x);
	(*texCoords)->push_back(t2->y);

	(*texCoords)->push_back(t3->x);
	(*texCoords)->push_back(t3->y);

	// Tangents and Bitangents
	TriangleTangentSpace(v0, v1, v2, t0, t1, t2, &tangent, &bitangent);

	// Normal Coordinates
	//Vector3 normal;
	//ComputeTangentBasis(v0, v1, v2, t0, t1, t2, normal, tangent, bitangent);
	//n0 = normal;
	//n1 = normal;
	//n2 = normal;

	(*normals)->push_back(n0->x);
	(*normals)->push_back(n0->y);
	(*normals)->push_back(n0->z);

	(*normals)->push_back(n1->x);
	(*normals)->push_back(n1->y);
	(*normals)->push_back(n1->z);

	(*normals)->push_back(n2->x);
	(*normals)->push_back(n2->y);
	(*normals)->push_back(n2->z);

	(*normals)->push_back(n3->x);
	(*normals)->push_back(n3->y);
	(*normals)->push_back(n3->z);

	for (j = 0; j <= 3; j++)
	{
		// Add the same data for each vertex 

		(*tangents)->push_back(tangent->x);
		(*tangents)->push_back(tangent->y);
		(*tangents)->push_back(tangent->z);

		(*bitangents)->push_back(bitangent->x);
		(*bitangents)->push_back(bitangent->y);
		(*bitangents)->push_back(bitangent->z);
	}
}

void MeshBufferVAO::LoadModelBuffers(Model* model,
	std::vector<GLfloat>** verticies,
	std::vector<GLfloat>** texCoords,
	std::vector<GLfloat>** normals,
	std::vector<GLfloat>** tangents,
	std::vector<GLfloat>** bitangents,
	int& verticiesCount)
{
	int i;

	Bounds = new AABB();

	for (i = 0; i < model->faces_count(); i++)
	{
		auto verts = model->face(i);

		
		if (verts->size() == 4)
		{
			// Entire mesh must be quads.
			quads = true;

			// Vertex Coordinates
			Vector3f* v0 = model->vert(i, 0);
			Vector3f* v1 = model->vert(i, 1);
			Vector3f* v2 = model->vert(i, 2);
			Vector3f* v3 = model->vert(i, 3);

			// Texture Coordinates
			Vector2f* t0 = model->uv(i, 0)->xy();
			Vector2f* t1 = model->uv(i, 1)->xy();
			Vector2f* t2 = model->uv(i, 2)->xy();
			Vector2f* t3 = model->uv(i, 3)->xy();

			// Normal Coordinates
			Vector3f* n0 = model->normal(i, 0);
			Vector3f* n1 = model->normal(i, 1);
			Vector3f* n2 = model->normal(i, 2);
			Vector3f* n3 = model->normal(i, 3);

			AppendModelBuffersQuad(Bounds, v0, v1, v2, v3, t0, t1, t2, t3, n0, n1, n2, n3, verticies, texCoords, normals, tangents, bitangents);
		}
		else if (verts->size() == 3)
		{
			// Entire mesh must be triangles.

			// Vertex Coordinates
			Vector3f* v0 = model->vert(i, 0);
			Vector3f* v1 = model->vert(i, 1);
			Vector3f* v2 = model->vert(i, 2);

			// Texture Coordinates
			Vector2f* t0 = model->uv(i, 0)->xy();
			Vector2f* t1 = model->uv(i, 1)->xy();
			Vector2f* t2 = model->uv(i, 2)->xy();

			// Normal Coordinates
			Vector3f* n0 = model->normal(i, 0);
			Vector3f* n1 = model->normal(i, 1);
			Vector3f* n2 = model->normal(i, 2);

			AppendModelBuffersTriangle(Bounds, v0, v1, v2, t0, t1, t2, n0, n1, n2, verticies, texCoords, normals, tangents, bitangents);
		}
	}

	if (quads)
	{
		verticiesCount += model->faces_count() * 4;
	}
	else 
	{
		verticiesCount += model->faces_count() * 3;
	}

	Bounds->Center = Bounds->GetCenter();
	Bounds->HalfSize = Bounds->GetHalfSize();

}

float* MeshBufferVAO::to_float_array(Vector3f** array, size_t size)
{
	std::vector<float>* primative_array = new std::vector<float>();
	for (int i = 0; i < size; i++) {
		primative_array->push_back(array[i]->x);
		primative_array->push_back(array[i]->y);
		primative_array->push_back(array[i]->z);
	}
	return primative_array->data();
}
float* MeshBufferVAO::to_float_array(Vector2f** array, size_t size)
{
	std::vector<float>* primative_array = new std::vector<float>();
	for (int i = 0; i < size; i++) {
		primative_array->push_back(array[i]->x);
		primative_array->push_back(array[i]->y);
	}
	return primative_array->data();
}
float* MeshBufferVAO::to_float_array(Vector4f** array, size_t size)
{
	std::vector<float>* primative_array = new std::vector<float>();
	for (int i = 0; i < size; i++) {
		primative_array->push_back(array[i]->x);
		primative_array->push_back(array[i]->y);
		primative_array->push_back(array[i]->z);
		primative_array->push_back(array[i]->w);
	}
	return primative_array->data();
}
GLfloat* MeshBufferVAO::to_float_array(std::vector<GLfloat>* farray)
{
	std::vector<GLfloat>* primative_array = new std::vector<GLfloat>();
	GLfloat* result = new GLfloat[farray->size()];
	for (int i = 0; i < farray->size(); i++)
	{
		primative_array->push_back(farray->at(i));
		result[i] = farray->at(i);
	}

	//return primative_array->data();
	return result;
}

void MeshBufferVAO::LoadModel(std::string* fileNameModel)
{
	std::vector<GLfloat>* verticies = new std::vector<GLfloat>();
	std::vector<GLfloat>* texCoords = new std::vector<GLfloat>();
	std::vector<GLfloat>* normals = new std::vector<GLfloat>();
	std::vector<GLfloat>* tangents = new std::vector<GLfloat>();
	std::vector<GLfloat>* bitangents = new std::vector<GLfloat>();

	model = new Model(fileNameModel);

	LoadModelBuffers(model, &verticies, &texCoords, &normals, &tangents, &bitangents, verticiesCount);
	
	if (verticies->size() == 0) {
		std::cout << "Verticies could not be found." << std::endl;
		return;
	}

	//GLfloat* verticies_array = to_float_array(verticies);
	//GLfloat* texCoords_array = to_float_array(texCoords);
	//GLfloat* normals_array = to_float_array(normals);
	//GLfloat* tangents_array = to_float_array(tangents);
	//GLfloat* bitangents_array = to_float_array(bitangents);
	//verticiesCount = verticies->size();

	float* farray = to_float_array(model->face_verts->data(), model->face_verts->size());
	float* farray_norms = to_float_array(model->face_normals->data(), model->face_normals->size());
	float* farray_texcoords = to_float_array(model->tex_coordA->data(), model->tex_coordA->size());
	float* farray_tangents = to_float_array(model->face_tangents->data(), model->face_tangents->size());
	float* farray_bitangents = to_float_array(model->face_bitangents->data(), model->face_bitangents->size());


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, model->face_verts->size() * sizeof(float) * 3, farray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &texcoords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texcoords_vbo);
	glBufferData(GL_ARRAY_BUFFER, model->tex_coordA->size() * sizeof(float) * 3, farray_texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, model->face_normals->size() * sizeof(float) * 3, farray_norms, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &tangents_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tangents_vbo);
	glBufferData(GL_ARRAY_BUFFER, model->face_tangents->size() * sizeof(float) * 3, farray_tangents, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &bitangents_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bitangents_vbo);
	glBufferData(GL_ARRAY_BUFFER, model->face_bitangents->size() * sizeof(float) * 3, farray_bitangents, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &_TEST_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model->faces_indicies->size(), model->faces_indicies->data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
}

void MeshBufferVAO::LoadTextures()
{
	model->diffusemap_ = model->load_texture(model->file_name, new std::string("_diffuse.tga"));
	model->normalmap_ = model->load_texture(model->file_name, new std::string("_nm_tangent.tga"));
	model->specularmap_ = model->load_texture(model->file_name, new std::string("_spec.tga"));
	model->glowmap_ = model->load_texture(model->file_name, new std::string("_glow.tga"));

	if (model->diffusemap_ != nullptr && model->diffusemap_->textureData->getBuffer() != nullptr)
	{
		model->diffusemap_->bindToUnit(0);
		texture = model->diffusemap_->textureId;
	}

	if (model->normalmap_ != nullptr && model->normalmap_->textureData->getBuffer() != nullptr)
	{
		model->normalmap_->bindToUnit(1);
		textureNormalMap = model->normalmap_->textureId;
	}

	if (model->specularmap_ != nullptr && model->specularmap_->textureData->getBuffer() != nullptr)
	{
		model->specularmap_->bindToUnit(1);
		textureSpecularMap = model->specularmap_->textureId;
	}

	if (model->glowmap_ != nullptr && model->glowmap_->textureData->getBuffer() != nullptr)
	{
		model->glowmap_->bindToUnit(1);
		textureGlowMap = model->glowmap_->textureId;
	}
}

void MeshBufferVAO::BindTextures()
{
	model->diffusemap_->bindToUnit(0);
	model->normalmap_->bindToUnit(1);
	model->specularmap_->bindToUnit(2);
	model->glowmap_->bindToUnit(3);
}

void MeshBufferVAO::Render()
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texcoords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tangents_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bitangents_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
	if (quads)
	{
		glDrawArrays(GL_QUADS, 0, verticiesCount);
		//glDrawElements(GL_QUADS, model->faces_indicies->size(), GL_UNSIGNED_INT, nullptr);
	}
	else 
	{
		glDrawArrays(GL_TRIANGLES, 0, verticiesCount);
		//glDrawElements(GL_TRIANGLES, model->faces_indicies->size(), GL_UNSIGNED_INT, nullptr);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glBindVertexArray(0);
}

bool MeshBufferVAO::Intersects(AABB* boundingBox)
{
	return this->Bounds->Intersects(boundingBox);
}