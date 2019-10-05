#pragma once
#include <vector>

struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	bool normalize;

	static unsigned char GetStrideByte(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_SHORT: return 2;
		case GL_UNSIGNED_BYTE:	return 1;
		default:
			return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	template <typename T >
	void Push(VertexBufferElement & element)
	{
		static_assert(false);
	}

	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template <>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, false });
		m_Stride += count * VertexBufferElement::GetStrideByte(GL_FLOAT);
	}

	template <>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, false });
		m_Stride += count * VertexBufferElement::GetStrideByte(GL_UNSIGNED_INT);
	}

	template <>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, false });
		m_Stride += count * VertexBufferElement::GetStrideByte(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
protected:
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
};