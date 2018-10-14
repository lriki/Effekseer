
#ifndef	__EFFEKSEERRENDERER_LLGI_MODEL_RENDERER_H__
#define	__EFFEKSEERRENDERER_LLGI_MODEL_RENDERER_H__

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.ModelRendererBase.h"

#include "LLGI/G3/LLGI.G3.Graphics.h"
#include "LLGI/G3/LLGI.G3.VertexBuffer.h"
#include "LLGI/G3/LLGI.G3.IndexBuffer.h"

namespace EffekseerRendererLLGI
{

typedef ::Effekseer::ModelRenderer::NodeParameter efkModelNodeParam;
typedef ::Effekseer::ModelRenderer::InstanceParameter efkModelInstanceParam;
typedef ::Effekseer::Vector3D efkVector3D;

class ModelRenderer
	: public ::EffekseerRenderer::ModelRendererBase
{
private:
	RendererImplemented*			m_renderer;
	Shader*							m_shader_lighting_texture_normal;
	Shader*							m_shader_lighting_normal;

	Shader*							m_shader_lighting_texture;
	Shader*							m_shader_lighting;

	Shader*							m_shader_texture;
	Shader*							m_shader;

	Shader*							m_shader_distortion_texture;
	Shader*							m_shader_distortion;

	ModelRenderer( RendererImplemented* renderer,
		Shader* shader_buf_lighting_texture_normal,
		Shader* shader_buf_lighting_normal,
		Shader* shader_buf_lighting_texture,
		Shader* shader_buf_lighting,
		Shader* shader_buf_texture,
		Shader* shader_buf,
		Shader* shader_buf_distortion_texture,
		Shader* shader_buf_distortion);
public:

	virtual ~ModelRenderer();

	static ModelRenderer* Create( 
		RendererImplemented* renderer,
		LLGI::DataStructure shader_lighting_texture_normal[2],
		LLGI::DataStructure shader_lighting_normal[2],
		LLGI::DataStructure shader_lighting_texture[2],
		LLGI::DataStructure shader_lighting[2],
		LLGI::DataStructure shader_texture[2],
		LLGI::DataStructure shader[2],
		LLGI::DataStructure shader_distortion_texture[2],
		LLGI::DataStructure shader_distortion[2]);

public:
	void BeginRendering(const efkModelNodeParam& parameter, int32_t count, void* userData);

	virtual void Rendering(const efkModelNodeParam& parameter, const InstanceParameter& instanceParameter, void* userData) override;

	void EndRendering( const efkModelNodeParam& parameter, void* userData );
};

}

#endif	// __EFFEKSEERRENDERER_LLGI_MODEL_RENDERER_H__
