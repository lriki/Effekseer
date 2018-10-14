#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

#ifndef	__EFFEKSEERRENDERER_LLGI_TEXTURELOADER_H__
#define	__EFFEKSEERRENDERER_LLGI_TEXTURELOADER_H__

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "EffekseerRendererLLGI.DeviceObject.h"
#include "LLGI/G3/LLGI.G3.Graphics.h"
#include "LLGI/G3/LLGI.G3.Texture.h"

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
	LLGI::G3::Graphics* graphics = nullptr;

	::Effekseer::FileInterface*			m_fileInterface;
	::Effekseer::DefaultFileInterface	m_defaultFileInterface;

public:
	TextureLoader(LLGI::G3::Graphics* graphics, ::Effekseer::FileInterface* fileInterface = NULL );
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