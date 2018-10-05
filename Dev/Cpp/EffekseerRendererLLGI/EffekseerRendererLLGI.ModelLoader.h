
#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

#ifndef	__EFFEKSEERRENDERER_LLGI_MODELLOADER_H__
#define	__EFFEKSEERRENDERER_LLGI_MODELLOADER_H__

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "EffekseerRendererLLGI.DeviceObject.h"

namespace EffekseerRendererLLGI
{

class ModelLoader
	: public ::Effekseer::ModelLoader
{
private:
	LLGI::G3::Graphics* graphics = nullptr;
	::Effekseer::FileInterface* m_fileInterface;
	::Effekseer::DefaultFileInterface m_defaultFileInterface;

public:
	ModelLoader(LLGI::G3::Graphics* graphics, ::Effekseer::FileInterface* fileInterface );
	virtual ~ModelLoader();

public:
	void* Load( const EFK_CHAR* path );

	void Unload( void* data );
};

}

#endif	// __EFFEKSEERRENDERER_LLGI_MODELLOADER_H__

#endif // __EFFEKSEER_RENDERER_INTERNAL_LOADER__