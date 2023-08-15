#pragma once

class ShaderManager
{
public:

	GLuint CompileShader(const char* vs, const char* fs);
	char* filetobuf(const char* file);

	GLuint GetShaderProgram() { return m_shaderprogram; }
	GLuint GetShaderProgram_UI() { return m_shaderprogram_ui; }
	GLuint GetShaderProgram_GAMEOVER() { return m_shaderprogram_game_over; }

private:
	ShaderManager();
	~ShaderManager();

	static ShaderManager* instance;

	GLuint vertexshader, fragmentshader; // 세이더
	GLchar* vertexsource, * fragmentsource; // 소스코드저장변수

	// 세이더프로그램
	GLuint m_shaderprogram; 
	GLuint m_shaderprogram_ui;
	GLuint m_shaderprogram_game_over;

public:
	void Init();
	static ShaderManager* Inst()
	{
		if (instance == nullptr)
			instance = new ShaderManager();
		return instance;
	}
};

