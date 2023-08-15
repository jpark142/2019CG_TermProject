#include "stdafx.h"
#include "ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
	m_shaderprogram = CompileShader("tp.glvs", "tp_fragment.glfs");
	m_shaderprogram_ui = CompileShader("test.glvs", "test.glfs");
	m_shaderprogram_game_over = CompileShader("game_over.glvs", "game_over.glfs");
}

char* ShaderManager::filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

GLuint ShaderManager::CompileShader(const char* vs, const char* fs)
{
	GLuint shaderProgram; // ���̴����α׷�

	vertexsource = filetobuf(vs);
	fragmentsource = filetobuf(fs);

	//���ؽ� ���̴� ��ü �����
	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	//���̴� �ڵ带 ���̴� ��ü�� �ֱ�: GL�� ��������. (�ҽ��ڵ�: ���ڿ�)
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	// ���ؽ����̴��������ϱ�
	glCompileShader(vertexshader);

	// ������������ε����������: ����üũ 

	GLint IsCompiled_VS;
	GLint maxLength;
	GLchar* vertexInfoLog;
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if (IsCompiled_VS == FALSE)
	{
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
		vertexInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		std::cout << vertexInfoLog;
		free(vertexInfoLog);
		return false;
	}

	//---�����׸�Ʈ���̴���ü����� 
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴��ڵ带���̴���ü���ֱ�: GL�κ�������. 
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	// �����׸�Ʈ���̴������� 
	glCompileShader(fragmentshader);

	GLint IsCompiled_FS;
	GLchar* fragmentInfoLog;

	// ������������ε����������: �����Ͽ���üũ
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
	if (IsCompiled_FS == FALSE)
	{
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
		fragmentInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
		std::cout << fragmentInfoLog;
		free(fragmentInfoLog);
		return false;
	}


	// ���ؽ����̴��������׸�Ʈ���̴��������ϵư�, ���������°�� 
	// GL ���̴���ü�������μ��̴�����ũ�Ѵ�. 
	// ���̴����α׷���ü�����
	shaderProgram = glCreateProgram();

	// ���̴������̴����α׷���ü�����δ�. 
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);

	// in_Position: �ε��� 0, 
	// in_Color: �ε��� 1 ���μӼ��ε��������ε��Ѵ�. 
	// �Ӽ���ġ�����α׷���ũ���������Ѵ�.
	//glBindAttribLocation(tempSP, 0, "in_Position"); 
	//glBindAttribLocation(tempSP, 1, "in_Color");

	// ���α׷���ũ 
	// �̶�, ���̴����α׷����������̹��̳ʸ��ڵ尡���̴������Ͽ� 
	// �����ǰ���ڵ尡 GPU�����ε�� (���������ٸ�) 
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexshader); // ���̴����α׷�����ũ�Ͽ����̴���ü��ü�»������� 
	glDeleteShader(fragmentshader);


	GLint IsLinked;
	GLchar* tempSPInfoLog;
	// ��ũ���Ǿ�����üũ�ϱ� 
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&IsLinked);
	if (IsLinked == FALSE) {
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		tempSPInfoLog = (char*)malloc(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, tempSPInfoLog);
		free(tempSPInfoLog);
		return false;
	}

	return shaderProgram;
}

