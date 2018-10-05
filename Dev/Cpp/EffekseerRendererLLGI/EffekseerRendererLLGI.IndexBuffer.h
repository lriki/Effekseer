
#pragma once

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.IndexBufferBase.h"
#include "EffekseerRendererLLGI.DeviceObject.h"
#include "LLGI/G3/LLGI.G3.IndexBuffer.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererLLGI
{
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class IndexBuffer
	: public DeviceObject
	, public ::EffekseerRenderer::IndexBufferBase
{
private:
	LLGI::G3::IndexBuffer* indexBuffer = nullptr;
	
	IndexBuffer( RendererImplemented* renderer, LLGI::G3::IndexBuffer* buffer, int maxCount, bool isDynamic );

public:
	virtual ~IndexBuffer();

	static IndexBuffer* Create( RendererImplemented* renderer, int maxCount, bool isDynamic );

	LLGI::G3::IndexBuffer* GetIndexBuffer() { return indexBuffer; }

public:
	void Lock();
	void Unlock();
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------