#include "Skybox.h"

Skybox::Skybox(std::string* texFileRightPosX, std::string* texFileLeftNegX,
	std::string* texFileTopPosY, std::string* texFileBottomNegY,
	std::string* texFileBackPosZ, std::string* texFileFrontNegZ)
{
	// Load textures into cubemap.
	cubemap = Cubemap::LoadTexture(texFileRightPosX, texFileLeftNegX, texFileTopPosY, texFileBottomNegY, texFileBackPosZ, texFileFrontNegZ)
		->Anisotropic()->ClampEdges()->Create();

	// Load shader program
	shader = new ShaderProgram("Shaders/skybox_vs.glsl", "Shaders/skybox_fs.glsl");

	// Construct the VAO/VBO for cube geometry.
	std::vector<GLfloat> vertices;
	std::vector<GLfloat>* vertices_data = new std::vector<GLfloat>();
	GLfloat vertices_arr[24] = {
		-1.0f, -1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 
		1.0f, 1.0f, -1.0f, -1.0f, -1.0f,1.0f,-1.0f, -1.0f, 1.0f, 1.0f, 
		-1.0f, -1.0f, 1.0f,-1.0f
	};
	float v;
	vertices.push_back(-1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);

	vertices.push_back(-1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(-1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	for (int i = 0; i < 24; i++)
	{
		v = vertices[i];
		vertices_data->push_back(v);
	}

	std::vector<GLfloat> texCoords;
	std::vector<GLfloat>* texCoords_data = new std::vector<GLfloat>();
	texCoords.push_back(0);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(0);
	texCoords.push_back(0);
	texCoords.push_back(0);
	texCoords.push_back(0);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(1);
	texCoords.push_back(0);
	texCoords.push_back(0);
	texCoords.push_back(0);
	GLfloat texcoords_arr[16] = {
		0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0
	};
	for (int i = 0; i < 16; i++)
	{
		v = texCoords[i];
		texCoords_data->push_back(v);
	}

	std::vector<GLfloat>* normals = new std::vector<GLfloat>();
	std::vector<GLfloat>* normals_data = new std::vector<GLfloat>();
	GLfloat normals_dat[24] = {
		-1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,-1.0f
	};
	normals->push_back(-1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);

	normals->push_back(-1.0f);
	normals->push_back(-1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(-1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(1.0f);
	normals->push_back(-1.0f);
	normals->push_back(-1.0f);
	normals->push_back(1.0f);
	normals->push_back(-1.0f);

	for (int i = 0; i < 24; i++)
	{
		GLfloat vv = (*normals)[i];
		v = vv;
		normals_data->push_back(v);
	}
	std::vector<unsigned int>* indexBuffer = new std::vector<unsigned int>();

	unsigned int indices[48] =
	{
		// front face
		0, 1, 2, 
		2, 3, 0, 
		// top face
		3, 2, 6, 
		6, 7, 3, 
		// back face
		7, 6, 5, 
		5, 4, 7, 
		// left face
		4, 0, 3, 
		3, 7, 4, 
		// bottom face
		0, 1, 5, 
		5, 4, 0, 
		// right face
		1, 5, 6, 
		6, 2, 1, 
	};
	for (int i = 0; i < 48; i++) indexBuffer->push_back(indices[i]);

	
	//glGenVertexArrays(1, &_TEST_VAO);
	//glBindVertexArray(_TEST_VAO);

	//glGenBuffers(1, &_TEST_EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 48, &indices[0], GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &_TEST_VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO);
	//glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices_arr[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexPointer(3, GL_FLOAT, 0, &vertices_arr[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//glGenBuffers(1, &_TEST_VBO_TEXCOORD);
	//glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_TEXCOORD);
	//glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), &texcoords_arr[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(1);
	////glVertexPointer(3, GL_FLOAT, 0, &texcoords_arr[0]);
	//glTexCoordPointer(3, GL_FLOAT, 0, &texcoords_arr[0]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	//glGenBuffers(1, &_TEST_VBO_NORMAL);
	//glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_NORMAL);
	//glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &normals_dat[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(2);
	////glVertexPointer(3, GL_FLOAT, 0, &normals_dat[0]);
	//glNormalPointer(GL_FLOAT, 0, &normals_dat[0]);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//vao = Vao::create();
	//vao->bind();
	//vao->createIndexBuffer(indexBuffer);
	//vao->createAttribute(0, vertices_data, 3);
	//vao->createAttribute(1, texCoords_data, 2);
	//vao->createAttribute(2, normals_data, 3);
	//vao->unbind();



	///////////////////////////////////////////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &_TEST_VAO);
	glBindVertexArray(_TEST_VAO);

	glGenBuffers(1, &_TEST_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_data->size() * sizeof(float), &vertices_arr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	//glVertexPointer(3, GL_FLOAT, 0, farray);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glBufferData(GL_ARRAY_BUFFER, norms->size() * sizeof(float) * 3, farray_norms, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenBuffers(1, &_TEST_VBO_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_NORMAL);
	glBufferData(GL_ARRAY_BUFFER, normals_data->size() * sizeof(float), &normals_dat[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glNormalPointer(GL_FLOAT, 0, &normals_dat[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(verts->size()));

	glGenBuffers(1, &_TEST_VBO_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_TEXCOORD);
	glBufferData(GL_ARRAY_BUFFER, texCoords_data->size() * sizeof(float) * 3, &texcoords_arr[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glTexCoordPointer(3, GL_FLOAT, 0, &texcoords_arr[0]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(verts->size() + norms->size()));

	////glGenBuffers(1, &tangentsBuffer);
	////glBindBuffer(GL_ARRAY_BUFFER, tangentsBuffer);
	////glBufferData(GL_ARRAY_BUFFER, face_tangents->size() * sizeof(float) * 3, farray_tangents, GL_STATIC_DRAW);
	////glEnableVertexAttribArray(3);
	//////glTexCoordPointer(3, GL_FLOAT, 0, face_tangents->data());
	////glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	////glGenBuffers(1, &bitangentsBuffer);
	////glBindBuffer(GL_ARRAY_BUFFER, bitangentsBuffer);
	////glBufferData(GL_ARRAY_BUFFER, face_bitangents->size() * sizeof(float) * 3, farray_bitangents, GL_STATIC_DRAW);
	////glEnableVertexAttribArray(4);
	//////glTexCoordPointer(3, GL_FLOAT, 0, face_tangents->data());
	////glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glVertexPointer(3, GL_FLOAT, 0, bananaVerts);
	//glNormalPointer(GL_FLOAT, 0, bananaNormals);
	//glTexCoordPointer(2, GL_FLOAT, 0, bananaTexCoords);





	glGenBuffers(1, &_TEST_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 48 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);





	//glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), verts->data(), GL_STATIC_DRAW);

	// fill buffer
	//glBufferSubData(GL_ARRAY_BUFFER, 0, verts->size() * 3, to_float_array(verts->data(), verts->size()));
	//glBufferSubData(GL_ARRAY_BUFFER, verts->size(), norms->size(), to_float_array(norms->data(), norms->size()));
	//glBufferSubData(GL_ARRAY_BUFFER, verts->size() + norms->size(), tex_coord->size(), to_float_array(tex_coord->data(), tex_coord->size()));

	//glGenVertexArrays(1, &VAO);
	glBindVertexArray(_TEST_VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_TEXCOORD);
	//glBindBuffer(GL_ARRAY_BUFFER, tangentsBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, bitangentsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
}

Skybox::~Skybox()
{
	delete cubemap;
	delete shader;
	delete vao;
}

void Skybox::Render(Transform* cameraTransform, Matrix4* projection)
{
	std::vector<Uniform*>* inUniforms = new std::vector<Uniform*>();
	inUniforms->push_back((Uniform*)projectionMatrix);
	inUniforms->push_back((Uniform*)viewMatrix);
	inUniforms->push_back((Uniform*)cubeMap);
	
	shader->start();
	
	projection = Matrix4::Perspective(45, 800.0f / 600.0f, 0.1f, 1000);
	projectionMatrix->loadMatrix(shader->programID, projection);

	// Remove translation from view matrix.
	Matrix4* view = new Matrix4(
		cameraTransform->localMatrix->Row0(), 
		cameraTransform->localMatrix->Row1(), 
		cameraTransform->localMatrix->Row2(), 
		cameraTransform->localMatrix->Row3()
	);
	view->SetTranslation(Vector3f::ZERO);
	view = new Matrix4(
		cameraTransform->localMatrix->Row0(), 
		cameraTransform->localMatrix->Row1(), 
		cameraTransform->localMatrix->Row2(), 
		cameraTransform->localMatrix->Row3()
	);
	//view->SetTranslation(Vector3f::ZERO);
	//view->Scale(1.5f);

	viewMatrix->loadMatrix(shader->programID, view);
	cubeMap->loadTexUnit(shader->programID, 0); // Indicates which texture unit the cubemap texture should be sampled from
	shader->storeAllUniformLocations(inUniforms);
	cubemap->bindToUnit(0);
	//vao->bind();
	//vao->binder(0, 3);

	OpenGlUtils::Antialias(true);
	OpenGlUtils::DisableBlending();
	OpenGlUtils::EnableDepthTesting(true);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(_TEST_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _TEST_EBO);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, _TEST_VBO_NORMAL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//OpenGlUtils::GoWireframe(true);
	//glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, nullptr); // vao->getIndexCount() vao->indicies_data
	
	unsigned int verticiesCount = 24 * 3;
	glDrawArrays(GL_TRIANGLES, 0, verticiesCount);

	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	shader->stop();
	//vao->unbinder(0, 3);

	glDepthFunc(GL_LESS);
}