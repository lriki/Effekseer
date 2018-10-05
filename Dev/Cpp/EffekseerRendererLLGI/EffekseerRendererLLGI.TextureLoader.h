#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

#ifndef	__EFFEKSEERRENDERER_LLGI_TEXTURELOADER_H__
#define	__EFFEKSEERRENDERER_LLGI_TEXTURELOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "EffekseerRendererLLGI.DeviceObject.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererLLGI
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class TextureLoader
	: public ::Effekseer::TextureLoader
{
private:
	ID3D11Device*						device;
	ID3D11DeviceContext*				context = nullptr;
	::Effekseer::FileInterface*			m_fileInterface;
	::Effekseer::DefaultFileInterface	m_defaultFileInterface;

public:
	TextureLoader(ID3D11Device* device, ID3D11DeviceContext* context, ::Effekseer::FileInterface* fileInterface = NULL );
	virtual ~TextureLoader();

public:
	Effekseer::TextureData* Load(const EFK_CHAR* path, ::Effekseer::TextureType textureType) override;

	void Unload(Effekseer::TextureData* data ) override;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_LLGI_TEXTURELOADER_H__

#endif // __EFFEKSEER_RENDERER_INTERNAL_LOADER__