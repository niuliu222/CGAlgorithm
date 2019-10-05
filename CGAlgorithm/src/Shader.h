#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererId;
	std::string m_Filepath;

	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
public:
	Shader(const char* filepath);
	Shader(std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const char * location, float v1, float v2, float v3, float v4);
	void SetUniform1i(const char * location, int value);
private:
	int GetUnigormLocation(const char* name);

	ShaderProgramSource ReadShaderSource(std::string filepath);
	void HandleShaderError(unsigned int shader_id);
	unsigned int CompileShader(unsigned int type, const std::string shader_source);
	unsigned int CreatePregram(const std::string vs_source, const std::string ps_source);
};