#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& vb, const IndexBuffer& ib, const Shader& layout) const;
};