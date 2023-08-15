#include "stdafx.h"
#include "Objects.h"
#include "ShaderManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float light_x = 1.0f;
float light_y = 1.0f;
float light_z = -1.0f;

#pragma region Vertex 정의
GLfloat ground_vertex_normal[] = {
	-1.0f, -0.5f, -100.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, -0.5f, 100.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -0.5f, 100.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -0.5f, -100.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, -0.5f, -100.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -0.5f, 100.0f, 0.0f, 1.0f, 0.0f
};

GLfloat tank_body_vertex_normal[] = {
	//뒷면 
   -0.25f, -0.25f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.25f, -0.25f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.25f,  0.25f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.25f,  0.25f, -0.5f,  0.0f,  0.0f, -1.0f,
   -0.25f,  0.25f, -0.5f,  0.0f,  0.0f, -1.0f,
   -0.25f, -0.25f, -0.5f,  0.0f,  0.0f, -1.0f,

   //앞면
   -0.25f, -0.25f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.25f, -0.25f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.25f,  0.25f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.25f,  0.25f,  0.5f,  0.0f,  0.0f,  1.0f,
   -0.25f,  0.25f,  0.5f,  0.0f,  0.0f,  1.0f,
   -0.25f, -0.25f,  0.5f,  0.0f,  0.0f,  1.0f,

   //왼쪽면
   -0.25f,  0.25f,  0.5f, -1.0f,  0.0f,  0.0f,
   -0.25f,  0.25f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.25f, -0.25f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.25f, -0.25f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.25f, -0.25f,  0.5f, -1.0f,  0.0f,  0.0f,
   -0.25f,  0.25f,  0.5f, -1.0f,  0.0f,  0.0f,

   //오른쪽면
	0.25f,  0.25f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.25f,  0.25f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.25f, -0.25f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.25f, -0.25f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.25f, -0.25f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.25f,  0.25f,  0.5f,  1.0f,  0.0f,  0.0f,

	//밑면
	-0.25f, -0.25f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.25f, -0.25f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.25f, -0.25f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.25f, -0.25f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.25f, -0.25f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.25f, -0.25f, -0.5f,  0.0f, -1.0f,  0.0f,

	//윗면
	-0.25f,  0.25f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.25f,  0.25f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.25f,  0.25f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.25f,  0.25f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.25f,  0.25f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.25f,  0.25f, -0.5f,  0.0f,  1.0f,  0.0f
};

GLfloat obs1_vertex_normal[] = {
	//뒷면
   -0.15f, -0.15f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f, -0.15f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f,  0.15f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f,  0.15f, -0.15f,  0.0f,  0.0f, -1.0f,
   -0.15f,  0.15f, -0.15f,  0.0f,  0.0f, -1.0f,
   -0.15f, -0.15f, -0.15f,  0.0f,  0.0f, -1.0f,

   //앞면
   -0.15f, -0.15f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f, -0.15f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f,  0.15f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f,  0.15f,  0.15f,  0.0f,  0.0f,  1.0f,
   -0.15f,  0.15f,  0.15f,  0.0f,  0.0f,  1.0f,
   -0.15f, -0.15f,  0.15f,  0.0f,  0.0f,  1.0f,

   //왼쪽면
   -0.15f,  0.15f,  0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f,  0.15f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.15f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.15f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.15f,  0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f,  0.15f,  0.15f, -1.0f,  0.0f,  0.0f,

   //오른쪽면
	0.15f,  0.15f,  0.15f,  1.0f,  0.0f,  0.0f,
	0.15f,  0.15f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.15f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.15f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.15f,  0.15f,  1.0f,  0.0f,  0.0f,
	0.15f,  0.15f,  0.15f,  1.0f,  0.0f,  0.0f,

	//밑면
	-0.15f, -0.15f, -0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.15f, -0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.15f,  0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.15f,  0.15f,  0.0f, -1.0f,  0.0f,
	-0.15f, -0.15f,  0.15f,  0.0f, -1.0f,  0.0f,
	-0.15f, -0.15f, -0.15f,  0.0f, -1.0f,  0.0f,

	//윗면
	-0.15f,  0.15f, -0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.15f, -0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.15f,  0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.15f,  0.15f,  0.0f,  1.0f,  0.0f,
	-0.15f,  0.15f,  0.15f,  0.0f,  1.0f,  0.0f,
	-0.15f,  0.15f, -0.15f,  0.0f,  1.0f,  0.0f
};

GLfloat tree_vertex_normal[]{
	//뒷면
   -0.15f, -0.5f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f, -0.5f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f,  0.5f, -0.15f,  0.0f,  0.0f, -1.0f,
	0.15f,  0.5f, -0.15f,  0.0f,  0.0f, -1.0f,
   -0.15f,  0.5f, -0.15f,  0.0f,  0.0f, -1.0f,
   -0.15f, -0.5f, -0.15f,  0.0f,  0.0f, -1.0f,

   //앞면
   -0.15f, -0.5f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f, -0.5f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f,  0.5f,  0.15f,  0.0f,  0.0f,  1.0f,
	0.15f,  0.5f,  0.15f,  0.0f,  0.0f,  1.0f,
   -0.15f,  0.5f,  0.15f,  0.0f,  0.0f,  1.0f,
   -0.15f, -0.5f,  0.15f,  0.0f,  0.0f,  1.0f,

   //왼쪽면
   -0.15f,  0.5f,  0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f,  0.5f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.5f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.5f, -0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f, -0.5f,  0.15f, -1.0f,  0.0f,  0.0f,
   -0.15f,  0.5f,  0.15f, -1.0f,  0.0f,  0.0f,

   //오른쪽면
	0.15f,  0.5f,  0.15f,  1.0f,  0.0f,  0.0f,
	0.15f,  0.5f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.5f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.5f, -0.15f,  1.0f,  0.0f,  0.0f,
	0.15f, -0.5f,  0.15f,  1.0f,  0.0f,  0.0f,
	0.15f,  0.5f,  0.15f,  1.0f,  0.0f,  0.0f,

	//밑면
	-0.15f, -0.5f, -0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.5f, -0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.5f,  0.15f,  0.0f, -1.0f,  0.0f,
	 0.15f, -0.5f,  0.15f,  0.0f, -1.0f,  0.0f,
	-0.15f, -0.5f,  0.15f,  0.0f, -1.0f,  0.0f,
	-0.15f, -0.5f, -0.15f,  0.0f, -1.0f,  0.0f,

	//윗면
	-0.15f,  0.5f, -0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.5f, -0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.5f,  0.15f,  0.0f,  1.0f,  0.0f,
	 0.15f,  0.5f,  0.15f,  0.0f,  1.0f,  0.0f,
	-0.15f,  0.5f,  0.15f,  0.0f,  1.0f,  0.0f,
	-0.15f,  0.5f, -0.15f,  0.0f,  1.0f,  0.0f
};

GLfloat game_over_vertex[] = {
	1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 우측상단0 
	1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,   // 우측하단1 
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 0.0f,   // 좌측하단2
	-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,    0.0f, 1.0f    // 좌측상단3

};
GLubyte game_over_index[] = {
	0,3,2,
	1,2,0
};
#pragma endregion

GLuint Objects::cube_vao = 0;
GLuint Objects::cube_vbo = 0;
GLuint Objects::game_over_vao = 0;
GLuint Objects::game_over_vbo = 0;
GLuint Objects::game_over_ebo = 0;
GLuint Objects::ground_vao = 0;
GLuint Objects::ground_vbo = 0;
GLuint Objects::obs_vao[3] = { 0, 0, 0 };
GLuint Objects::obs_vbo[3] = { 0, 0, 0 };
GLuint Objects::tree_vao = 0;
GLuint Objects::tree_vbo = 0;
GLuint Objects::texture1 = 0;
GLuint Objects::texture_end = 0;

void Objects::Init()
{
	// 땅바닥
	SetVertexData(ground_vao, ground_vbo, sizeof(ground_vertex_normal), ground_vertex_normal);
	// 큐브
	SetVertexData(cube_vao, cube_vbo, sizeof(tank_body_vertex_normal), tank_body_vertex_normal);

	// 장애물1 (cube 1개)
	SetVertexData(obs_vao[0], obs_vbo[0], sizeof(obs1_vertex_normal), obs1_vertex_normal);
	// 장애물2 (Open & Close Obstacle)
	SetVertexData(obs_vao[1], obs_vbo[1], sizeof(obs1_vertex_normal), obs1_vertex_normal);
	SetVertexData(obs_vao[2], obs_vbo[2], sizeof(obs1_vertex_normal), obs1_vertex_normal);

	// 나무
	SetVertexData(tree_vao, tree_vbo, sizeof(tree_vertex_normal), tree_vertex_normal);

	// Game Over
	glGenVertexArrays(1, &game_over_vao);
	glGenBuffers(1, &game_over_vbo);
	glGenBuffers(1, &game_over_ebo);

	glBindVertexArray(game_over_vao);

	glBindBuffer(GL_ARRAY_BUFFER, game_over_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(game_over_vertex), game_over_vertex, GL_STATIC_DRAW);

	//ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game_over_ebo); // GL_ELEMENT_ARRAY_BUFFER 버퍼유형으로바인딩 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(game_over_index), game_over_index, GL_STATIC_DRAW);


	//---위치속성
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//색상
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//텍스처 좌표
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(false);
	initTexture("game_over.png", texture_end);

	// 점수
	initTexture("numset.png", texture1);

	glBindVertexArray(0);
}

void Objects::initTexture(const char* imgStr, GLuint& textureID)
{
	//textureID
	glGenTextures(1, &textureID); //---텍스처생성 
	glBindTexture(GL_TEXTURE_2D, textureID); //---텍스처바인딩

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //---현재바인딩된텍스처객체의속성설정하기 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imgStr, &width, &height, &nrChannels, 0); //---텍스처로사용할비트맵이미지로드하기

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Succeed texture" << std::endl;

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void Objects::SetVertexData(GLuint& vao, GLuint& vbo, GLsizeiptr size, const GLfloat* data)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	//---위치속성
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---노말속성
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}


bool Objects::Update()
{
	return false;
}

void Objects::Draw()
{

}

bool Obstacle::Update()
{
	m_z += 0.1f;
	if (m_z > 50.0f)
		return true;
	return false;
}

void Obstacle::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	//모델-----------------------------------
	glm::mat4 obs1_move = glm::mat4(1.0f);
	glm::mat4 obs1_first_state = glm::mat4(1.0f);

	obs1_first_state = glm::translate(obs1_first_state, glm::vec3(m_x, m_y, m_z));

	obs1_move = obs1_first_state;

	unsigned int modelLocation3 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation3, 1, GL_FALSE, glm::value_ptr(obs1_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation3 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation3, 0.0f, 2.0f, 5.0f);
	int lightColorLocation3 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation3, 1.0f, 1.0f, 1.0f);
	int objColorLocation3 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation3, 1.0f, 1.0f, 0.0f);
	int personLocation3 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation3, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(obs_vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

bool OC_Obstacle::Update()
{
	//왼
	oc_z += 0.1f;
	oc_x += oc_dx;
	if (oc_x >= -0.1f || oc_x <= -0.7f) {
		oc_dx *= -1;
	}

	//오
	oc_z2 += 0.1f;
	oc_x2 += oc_dx2;
	if (oc_x2 <= 0.1f || oc_x2 >= 0.7f) {
		oc_dx2 *= -1;
	}

	if (oc_z > 50.0f || oc_z2 > 50.0f)
		return true;
	return false;
}

void OC_Obstacle::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	//모델-----------------------------------
	glm::mat4 obs_oc_move = glm::mat4(1.0f);
	glm::mat4 obs_oc_first_state = glm::mat4(1.0f);

	obs_oc_first_state = glm::translate(obs_oc_first_state, glm::vec3(oc_x, -0.25f, oc_z));

	obs_oc_move = obs_oc_first_state;

	unsigned int modelLocation7 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation7, 1, GL_FALSE, glm::value_ptr(obs_oc_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation7 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation7, 0.0f, 2.0f, 5.0f);
	int lightColorLocation7 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation7, 1.0f, 1.0f, 1.0f);
	int objColorLocation7 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation7, 0.0f, 1.0f, 1.0f);
	int personLocation7 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation7, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(obs_vao[1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//
	//모델-----------------------------------
	glm::mat4 obs_oc2_move = glm::mat4(1.0f);
	glm::mat4 obs_oc2_first_state = glm::mat4(1.0f);

	obs_oc2_first_state = glm::translate(obs_oc2_first_state, glm::vec3(oc_x2, -0.25f, oc_z2));

	obs_oc2_move = obs_oc2_first_state;

	unsigned int modelLocation8 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation8, 1, GL_FALSE, glm::value_ptr(obs_oc2_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation8 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation8, 0.0f, 2.0f, 5.0f);
	int lightColorLocation8 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation8, 1.0f, 1.0f, 1.0f);
	int objColorLocation8 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation8, 0.0f, 1.0f, 1.0f);
	int personLocation8 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation8, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(obs_vao[2]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

bool RingObstacle::Update()
{
	ring_z += 0.15f;
	if (ring_z > 50.0f)
		return true;
	return false;
}

void RingObstacle::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	glm::mat4 ring_move = glm::mat4(1.0f);
	glm::mat4 ring_first_state = glm::mat4(1.0f);

	ring_first_state = glm::translate(ring_first_state, glm::vec3(ring_x, ring_y, ring_z));
	ring_move = ring_first_state;

	unsigned int modelLocation4 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation4, 1, GL_FALSE, glm::value_ptr(ring_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation4 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation4, 0.0f, 2.0f, 5.0f);
	int lightColorLocation4 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation4, 1.0f, 1.0f, 1.0f);
	int objColorLocation4 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation4, 1.0f, 1.0f, 0.0f);
	int personLocation4 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation4, 0.0f, 0.0f, 1.0f);

	GLUquadric* qobj = gluNewQuadric(); //객체를 생성한다.
	gluQuadricDrawStyle(qobj, GLU_FILL); //어떻게 그릴지 정한다

	gluQuadricNormals(qobj, GLU_SMOOTH); //(생략 가능)
	gluQuadricOrientation(qobj, GLU_OUTSIDE); //(생략 가능)

	gluDisk(qobj, 0.4f, 0.5f, 50, 50);
}

bool Snow::Update()
{
	m_y -= 0.01f;
	if (m_y <= 0)
		return true;
	return false;
}

void Snow::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	glm::mat4 snow_move = glm::mat4(1.0f);
	snow_move = glm::translate(snow_move, glm::vec3(m_x, m_y, m_z));

	unsigned int modelLocation3 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation3, 1, GL_FALSE, glm::value_ptr(snow_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation3 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation3, 1.2f, 1.0f, 1.0f);
	int lightColorLocation3 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation3, 1.0f, 1.0f, 1.0f);
	int objColorLocation3 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation3, 1.0f, 1.0f, 1.0f);
	int personLocation3 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation3, 0.0f, 0.0f, 3.0f);

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GL_FILL); //어떻게 그릴지 정한다

	gluQuadricNormals(qobj, GLU_SMOOTH); //(생략 가능)
	gluQuadricOrientation(qobj, GLU_OUTSIDE); //(생략 가능)

	gluSphere(qobj, 0.01f, 10, 10);
}

bool Tree::Update()
{
	m_z += 0.2f; //나무 다가옴
	if (m_z > 100.0f)
		return true;
	return false;
}

void Tree::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	glm::mat4 tree_move = glm::mat4(1.0f);
	glm::mat4 tree_first_state = glm::mat4(1.0f);

	tree_first_state = glm::translate(tree_first_state, glm::vec3(m_x, 0.0f, m_z));
	tree_move = tree_first_state;

	unsigned int modelLocation5 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation5, 1, GL_FALSE, glm::value_ptr(tree_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation5 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation5, 0.0f, 0.0f, 5.0f);
	int lightColorLocation5 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation5, 1.0f, 1.0f, 1.0f);
	int objColorLocation5 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation5, 1.0f, 1.0f, 0.5f);
	int personLocation5 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation5, 0.0f, 0.0f, 5.0f);

	glBindVertexArray(tree_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//나뭇잎------------------------
	glm::mat4 leaf_move = glm::mat4(1.0f);
	glm::mat4 leaf_first_state = glm::mat4(1.0f);

	leaf_first_state = glm::translate(leaf_first_state, glm::vec3(m_x, 0.5f, m_z));
	leaf_move = leaf_first_state;

	unsigned int modelLocation6 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(leaf_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation6 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation6, 0.0f, 0.0f, 5.0f);
	int lightColorLocation6 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation6, 1.0f, 1.0f, 1.0f);
	int objColorLocation6 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation6, m_tree_colorR, m_tree_colorG, m_tree_colorB);
	int personLocation6 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation6, 0.0f, 0.0f, 5.0f);

	GLUquadric* qobj = gluNewQuadric(); //객체를 생성한다.
	gluQuadricDrawStyle(qobj, GLU_FILL); //어떻게 그릴지 정한다

	gluQuadricNormals(qobj, GLU_SMOOTH); //(생략 가능)
	gluQuadricOrientation(qobj, GLU_OUTSIDE); //(생략 가능)
	gluSphere(qobj, 0.4f, 20, 20);
}

void Tree::SetColor(float r, float g, float b)
{
	m_tree_colorR = r;
	m_tree_colorG = g;
	m_tree_colorB = b;
}



Ground::Ground()
	: ground_color_r{ 1.0f },
	ground_color_g{ 0.8f },
	ground_color_b{ 0.61f }
{

}

void Ground::SetColor(float r, float g, float b)
{
	ground_color_r = r;
	ground_color_g = g;
	ground_color_b = b;
}


void Ground::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();
	//땅바닥
	//------------------------------------------------------------------
	glm::mat4 ground = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(ground));

	//조명-------------------------------------------------------------------
	int lightPosLocation = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, light_x, light_y, light_z);
	int lightColorLocation = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	int objColorLocation = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, ground_color_r, ground_color_g, ground_color_b);
	int personLocation = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation, 0.0f, 0.0f, 3.0f);

	glBindVertexArray(ground_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}


void GameOver_UI::Init()
{

}

void GameOver_UI::Draw()
{
	glClearColor(0, 0, 0, 1.0f);

	glClear(GL_DEPTH_BUFFER_BIT);

	GLuint shader_gameover = ShaderManager::Inst()->GetShaderProgram_GAMEOVER();
	glUseProgram(shader_gameover);

	// 공용 카메라------------------------------------------
	glm::vec3 cameraPos_go = glm::vec3(0.0f, 0.0f, 3.5f);
	glm::vec3 cameraDirection_go = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp_go = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view_go = glm::mat4(1.0f);
	view_go = glm::lookAt(cameraPos_go, cameraDirection_go, cameraUp_go);

	unsigned int viewLocation_go = glGetUniformLocation(shader_gameover, "viewTransform");
	glUniformMatrix4fv(viewLocation_go, 1, GL_FALSE, &view_go[0][0]);

	//공용 투영
	glm::mat4 projection_go = glm::mat4(1.0f);
	projection_go = glm::perspective(glm::radians(30.0f), (float)800 / (float)800, 0.1f, 100.0f);

	unsigned int projectionLocation_go = glGetUniformLocation(shader_gameover, "projectionTransform");
	glUniformMatrix4fv(projectionLocation_go, 1, GL_FALSE, &projection_go[0][0]);

	//모델
	glm::mat4 game_over = glm::mat4(1.0f);

	unsigned int modelLocation_go = glGetUniformLocation(shader_gameover, "modelTransform");
	glUniformMatrix4fv(modelLocation_go, 1, GL_FALSE, glm::value_ptr(game_over));

	glBindVertexArray(game_over_vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_end);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Player::Draw()
{
	GLuint shader = ShaderManager::Inst()->GetShaderProgram();

	glm::mat4 player_move = glm::mat4(1.0f);
	glm::mat4 player_first_state = glm::mat4(1.0f);
	glm::mat4 player_trans = glm::mat4(1.0f);
	glm::mat4 player_rotate_y = glm::mat4(1.0f);

	glm::mat4 player_scale = glm::mat4(1.0f);
	player_scale = glm::scale(player_scale, glm::vec3(0.5f));

	player_first_state = glm::translate(player_first_state, glm::vec3(0.f, -0.25f, -0.f));
	player_rotate_y = glm::rotate(player_rotate_y, glm::radians(player_angle), glm::vec3(0.0f, 1.0f, 0.0f));
	player_trans = glm::translate(player_trans, glm::vec3(body_x, body_y, body_z));

	if (IsLkeyPressed == true)
	{
		player_move = player_trans * player_first_state * player_rotate_y * player_scale;
	}
	else
	{
		player_move = player_trans * player_first_state * player_rotate_y;
	}

	unsigned int modelLocation2 = glGetUniformLocation(shader, "modelTransform");
	glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(player_move));

	//조명-------------------------------------------------------------------
	int lightPosLocation2 = glGetUniformLocation(shader, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation2, light_x, light_y, light_z);
	int lightColorLocation2 = glGetUniformLocation(shader, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation2, 1.0f, 1.0f, 1.0f);
	int objColorLocation2 = glGetUniformLocation(shader, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation2, 1.0f, 0.0f, 0.0f);
	int personLocation2 = glGetUniformLocation(shader, "viewPos");
	glUniform3f(personLocation2, 0.0f, 0.0f, 3.0f);

	glBindVertexArray(cube_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Score_UI::Draw()
{
	glClearColor(0, 0, 0, 1.0f);

	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(ShaderManager::Inst()->GetShaderProgram_UI());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	score++;
	drawInt(life, -1, 1, 0.1f);
	//drawInt(1203, 0, 0, 0.1f, 0.2f, 0.98f, 0.68f);
	drawInt(score / 10, 0.7f, 0.7f, 0.05f, score / 1000.f, (1 - score / 1000.f), 0.1f);
	//if (testnum > 1000)testnum = 0;
}

void Score_UI::SetScore(int num)
{
	score = num;
}

void Score_UI::SetLife(int _life)
{
	life = _life;
}

//return offset
int Score_UI::drawNum(int num, int offset, float scale)
{
	GLuint shader_ui = ShaderManager::Inst()->GetShaderProgram_UI();

	int ten = num / 10;
	int one = num % 10;

	if (ten)
		offset = drawNum(ten, offset, scale);

	int uiCharIDuniform = glGetUniformLocation(shader_ui, "uiCharid");
	int uioffsetuniform = glGetUniformLocation(shader_ui, "offset");
	glUniform1i(uiCharIDuniform, one);
	glUniform3f(uioffsetuniform, offset, scale, 800.0f / 1000.0f);

	glDrawArrays(GL_QUADS, 0, 4);
	offset++;

	return offset;
}

void Score_UI::drawInt(int num, float posx, float posy, float scale, float colorx, float colory, float colorz)
{
	GLuint shader_ui = ShaderManager::Inst()->GetShaderProgram_UI();

	int uiposuniform = glGetUniformLocation(shader_ui, "pos");
	int uicoloruniform = glGetUniformLocation(shader_ui, "color");
	glUniform2f(uiposuniform, posx, posy);
	glUniform3f(uicoloruniform, colorx, colory, colorz);
	drawNum(num, 0, scale);
}
