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
	GLuint shaderProgram; // 세이더프로그램

	vertexsource = filetobuf(vs);
	fragmentsource = filetobuf(fs);

	//버텍스 세이더 객체 만들기
	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	//세이더 코드를 세이더 객체에 넣기: GL로 보내진다. (소스코드: 문자열)
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	// 버텍스세이더컴파일하기
	glCompileShader(vertexshader);

	// 컴파일이제대로되지않은경우: 에러체크 

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

	//---프래그먼트세이더객체만들기 
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	// 세이더코드를세이더객체에넣기: GL로보내진다. 
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	// 프래그먼트세이더컴파일 
	glCompileShader(fragmentshader);

	GLint IsCompiled_FS;
	GLchar* fragmentInfoLog;

	// 컴파일이제대로되지않은경우: 컴파일에러체크
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


	// 버텍스세이더와프래그먼트세이더가컴파일됐고, 에러가없는경우 
	// GL 세이더객체를만들어두세이더를링크한다. 
	// 세이더프로그램객체만들기
	shaderProgram = glCreateProgram();

	// 세이더를세이더프로그램객체에붙인다. 
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);

	// in_Position: 인덱스 0, 
	// in_Color: 인덱스 1 으로속성인덱스를바인드한다. 
	// 속성위치는프로그램링크전에수행한다.
	//glBindAttribLocation(tempSP, 0, "in_Position"); 
	//glBindAttribLocation(tempSP, 1, "in_Color");

	// 프로그램링크 
	// 이때, 세이더프로그램은에러없이바이너리코드가세이더를위하여 
	// 생성되고그코드가 GPU에업로드됨 (에러가없다면) 
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexshader); // 세이더프로그램에링크하여세이더객체자체는삭제가능 
	glDeleteShader(fragmentshader);


	GLint IsLinked;
	GLchar* tempSPInfoLog;
	// 링크가되었는지체크하기 
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

