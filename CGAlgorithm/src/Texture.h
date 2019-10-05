#pragma once
#include <string>
class Texture
{
private:
	unsigned int m_RenderID;
	int m_BPP, m_Width, m_Height;
	unsigned char * m_LocalBuffer;
	std::string m_Filepath;
public:
	Texture(std::string filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
private:
	int GetWidht() const { return m_Width; }
	int GetHeight() const { return m_Height; }
};
