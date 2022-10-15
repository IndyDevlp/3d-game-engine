#pragma once

#include "VertexBuffer.hpp"

namespace EngineCore {

	class VertexArray {
	public:
		
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray& operator=(VertexArray&& vertex_buffer) noexcept;
		VertexArray(VertexArray&& vertex_buffer) noexcept;

		void add_buffer(const VertexBuffer& vertex_buffer);
		void bind() const;
		static void unbind();

	private:

		unsigned m_id = 0;
		unsigned m_elements_count = 0;
	};
}
