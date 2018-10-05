
#pragma once

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.VertexBufferBase.h"
#include "EffekseerRendererLLGI.DeviceObject.h"
#include "LLGI/G3/LLGI.G3.VertexBuffer.h"

namespace EffekseerRendererLLGI
{

class VertexBuffer
	: public DeviceObject
	, public ::EffekseerRenderer::VertexBufferBase
{
private:
	// TODO make ring buffer
	int32_t currentIndex = 0;
	std::vector<LLGI::G3::VertexBuffer*> vertexBuffers;

	void*					m_lockedResource;

	uint32_t				m_vertexRingOffset;
	bool					m_ringBufferLock;

	int32_t					m_ringLockedOffset;
	int32_t					m_ringLockedSize;


	VertexBuffer( RendererImplemented* renderer, LLGI::G3::VertexBuffer* buffer, int size, bool isDynamic );
public:
	virtual ~VertexBuffer();

	static VertexBuffer* Create( RendererImplemented* renderer, int size, bool isDynamic );

	LLGI::G3::VertexBuffer* GetVertexBuffer() { return vertexBuffers[currentIndex]; }

public:
	void Lock();
	bool RingBufferLock( int32_t size, int32_t& offset, void*& data );
	bool TryRingBufferLock(int32_t size, int32_t& offset, void*& data);
	void Unlock();
};

}
