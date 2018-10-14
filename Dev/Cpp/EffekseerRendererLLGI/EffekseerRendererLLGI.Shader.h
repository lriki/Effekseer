
#ifndef	__EFFEKSEERRENDERER_LLGI_SHADER_H__
#define	__EFFEKSEERRENDERER_LLGI_SHADER_H__

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "EffekseerRendererLLGI.DeviceObject.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.ShaderBase.h"

#include "LLGI/G3/LLGI.G3.Graphics.h"
#include "LLGI/G3/LLGI.G3.Shader.h"

namespace EffekseerRendererLLGI
{

class Shader
	: public DeviceObject
	, public ::EffekseerRenderer::ShaderBase
{
private:
	
	LLGI::G3::Shader* shader_ = nullptr;
	std::vector<LLGI::VertexLayoutFormat> layoutFormats;

	void*					m_vertexConstantBuffer;
	void*					m_pixelConstantBuffer;

	int32_t					m_vertexRegisterCount;
	int32_t					m_pixelRegisterCount;

	Shader(
		RendererImplemented* renderer,
		LLGI::G3::Shader* shader,
		const std::vector<LLGI::VertexLayoutFormat>& layoutFormats);

public:
	virtual ~Shader();

	static Shader* Create( 
		RendererImplemented* renderer, 
		const uint8_t vertexShader[], 
		int32_t vertexShaderSize,
		const uint8_t pixelShader[], 
		int32_t pixelShaderSize,
		const char* name, 
		const std::vector<LLGI::VertexLayoutFormat>& layoutFormats);

public:
	LLGI::G3::Shader* GetShader() const { return shader_; }
	
	void SetVertexConstantBufferSize(int32_t size);
	void SetPixelConstantBufferSize(int32_t size);

	void* GetVertexConstantBuffer() { return m_vertexConstantBuffer; }
	void* GetPixelConstantBuffer() { return m_pixelConstantBuffer; }

	void SetVertexRegisterCount(int32_t count){ m_vertexRegisterCount = count; }
	void SetPixelRegisterCount(int32_t count){ m_pixelRegisterCount = count; }

	void SetConstantBuffer();
};

}

#endif	// __EFFEKSEERRENDERER_LLGI_SHADER_H__
