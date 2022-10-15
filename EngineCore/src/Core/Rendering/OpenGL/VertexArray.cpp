#include "VertexArray.hpp"
#include "Core/Log.hpp"

#include <glad/glad.h>

namespace EngineCore {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertex_buffer) noexcept
	{
		m_id = vertex_buffer.m_id;
		m_elements_count = vertex_buffer.m_elements_count;
		vertex_buffer.m_id = 0;
		vertex_buffer.m_elements_count = 0;
		
		return *this;
	}

	VertexArray::VertexArray(VertexArray&& vertex_buffer) noexcept
		: m_id(vertex_buffer.m_id)
		, m_elements_count(vertex_buffer.m_elements_count)
	{
		vertex_buffer.m_id = 0;
		vertex_buffer.m_elements_count = 0;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_buffer(const VertexBuffer& vertex_buffer)
	{
		bind();
		vertex_buffer.bind();

		glEnableVertexAttribArray(m_elements_count);
		glVertexAttribPointer(m_elements_count, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		++m_elements_count;
	}
}