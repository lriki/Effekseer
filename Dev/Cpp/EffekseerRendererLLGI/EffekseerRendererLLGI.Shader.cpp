
#include "EffekseerRendererLLGI.Shader.h"
#include "EffekseerRendererLLGI.RendererImplemented.h"

namespace EffekseerRendererLLGI
{

Shader::Shader(
		RendererImplemented* renderer,
		LLGI::G3::Shader* shader,
		const std::vector<LLGI::VertexLayoutFormat>& layoutFormats)
	: DeviceObject			( renderer )
	, shader_				( shader )
	, layoutFormats			(layoutFormats)
	, m_vertexConstantBuffer(NULL)
	, m_pixelConstantBuffer(NULL)
	, m_vertexRegisterCount(0)
	, m_pixelRegisterCount(0)
{
}

Shader::~Shader()
{
	ES_SAFE_RELEASE( shader_ );
	ES_SAFE_DELETE_ARRAY(m_vertexConstantBuffer);
	ES_SAFE_DELETE_ARRAY(m_pixelConstantBuffer);
}

Shader* Shader::Create(
	RendererImplemented* renderer,
	const uint8_t vertexShader[],
	int32_t vertexShaderSize,
	const uint8_t pixelShader[],
	int32_t pixelShaderSize,
	const char* name,
	const std::vector<LLGI::VertexLayoutFormat>& layoutFormats)
{
	assert( renderer != NULL );
	assert( renderer->GetGraphics() != NULL );

	LLGI::DataStructure shaderData[2];
	shaderData[0].Data = (void*)vertexShader;
	shaderData[0].Size = vertexShaderSize;
	shaderData[1].Data = (void*)pixelShader;
	shaderData[1].Size = pixelShaderSize;

	auto shader = renderer->GetGraphics()->CreateShader(shaderData, 2);

	return new Shader( renderer, shader, layoutFormats);
}

void Shader::SetVertexConstantBufferSize(int32_t size)
{
	ES_SAFE_DELETE_ARRAY(m_vertexConstantBuffer);
	m_vertexConstantBuffer = new uint8_t[size];
}

void Shader::SetPixelConstantBufferSize(int32_t size)
{
	ES_SAFE_DELETE_ARRAY(m_pixelConstantBuffer);
	m_pixelConstantBuffer = new uint8_t[size];
}

void Shader::SetConstantBuffer()
{
	if (m_vertexRegisterCount > 0)
	{
	}

	if (m_pixelRegisterCount > 0)
	{
	}
}

}