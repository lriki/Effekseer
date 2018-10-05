
#ifndef	__EFFEKSEERRENDERER_LLGI_RENDERSTATE_H__
#define	__EFFEKSEERRENDERER_LLGI_RENDERSTATE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "../../EffekseerRendererCommon/EffekseerRenderer.RenderStateBase.h"
#include "EffekseerRendererLLGI.Base.h"
#include "EffekseerRendererLLGI.RendererImplemented.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererLLGI
{
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class RenderState
	: public ::EffekseerRenderer::RenderStateBase
{
private:
	static const int32_t		DepthTestCount = 2;
	static const int32_t		DepthWriteCount = 2;
	static const int32_t		CulTypeCount = 3;
	static const int32_t		AlphaTypeCount = 5;
	static const int32_t		TextureFilterCount = 2;
	static const int32_t		TextureWrapCount = 2;

	RendererImplemented*		m_renderer;
	ID3D11RasterizerState*		m_rStates[CulTypeCount];
	ID3D11DepthStencilState*	m_dStates[DepthTestCount][DepthWriteCount];
	ID3D11BlendState*			m_bStates[AlphaTypeCount];
	ID3D11SamplerState*			m_sStates[TextureFilterCount][TextureWrapCount];

public:
	RenderState(RendererImplemented* renderer, D3D11_COMPARISON_FUNC depthFunc);
	virtual ~RenderState();

	void Update( bool forced );
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_LLGI_RENDERSTATE_H__
