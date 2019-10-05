#include "Shader.h"

#include <GL/glew.h>

Shader::Shader(const char* filepath)
	: m_RendererId(0), m_Filepath(filepath)
{
	ShaderProgramSource source = ReadShaderSource(filepath);
	m_RendererId = CreatePregram(source.VertexSource, source.FragmentSource);
}

Shader::Shader(std::string& filepath)
	: Shader(filepath.c_str())
{

}

Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const char * location, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUnigormLocation(location), v1, v2, v3, v4);
}

void Shader::SetUniform1i(const char * location, int value)
{
	glUniform1i(GetUnigormLocation(location),value);
}

int Shader::GetUnigormLocation(const char* name)
{
	std::string sname = name;
	if (m_UniformLocationCache.find(sname) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[sname];
	}
	auto location = glGetUniformLocation(m_RendererId, name);
	if (location == -1)
	{
		std::cout << "Find Uniform Failed:"<< name << ", path=" << m_Filepath << std::endl;
		return -1;
	}
	m_UniformLocationCache[sname] = location;
	return location;
}

ShaderProgramSource Shader::ReadShaderSource(std::string filepath)
{
	std::stringstream ss[2];
	std::fstream filestream(filepath);

	enum class ShaderType
	{
		NoneType = -1, VertexType = 0, FragmentType = 1
	};

	ShaderType type = ShaderType::NoneType;

	std::string line;
	while (getline(filestream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VertexType;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FragmentType;
			}
		}
		else
		{
			ss[(int)type] << line << std::endl;
		}
	}
	return { ss[0].str(), ss[1].str() };
}

void Shader::HandleShaderError(unsigned int shader_id)
{
	int length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
	char * info = new char[length];
	glGetShaderInfoLog(shader_id, length, &length, info);
	std::cout << "Shader Compile Error :" << info << std::endl;

	delete info;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string shader_source)
{
	unsigned int id = glCreateShader(type);
	const char * source = shader_source.c_str();
	glShaderSource(id, 1, &source, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		HandleShaderError(id);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreatePregram(const std::string vs_source, const std::string ps_source)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vs_source);
	if (vs == 0)
	{
		return 0;
	}

	unsigned int ps = CompileShader(GL_FRAGMENT_SHADER, ps_source);
	if (ps == 0)
	{
		glDeleteShader(vs);
		return 0;
	}

	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, ps);
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(ps);

	return program;
}
