﻿#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__

#include "EffekseerRendererLLGI.RendererImplemented.h"
#include "EffekseerRendererLLGI.TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"

namespace EffekseerRendererLLGI
{

TextureLoader::TextureLoader(LLGI::G3::Graphics* graphics, ::Effekseer::FileInterface* fileInterface )
	: m_fileInterface	(fileInterface)
	, graphics			(graphics)
{
	ES_SAFE_ADDREF(graphics);
	
	if( fileInterface == nullptr )
	{
		m_fileInterface = &m_defaultFileInterface;
	}
}

TextureLoader::~TextureLoader()
{
	ES_SAFE_RELEASE(graphics);
}

Effekseer::TextureData* TextureLoader::Load(const EFK_CHAR* path, ::Effekseer::TextureType textureType)
{
	std::auto_ptr<::Effekseer::FileReader> 
		reader( m_fileInterface->OpenRead( path ) );
	
	if( reader.get() != NULL )
	{
		Effekseer::TextureData* textureData = nullptr;

		size_t size_texture = reader->GetLength();
		char* data_texture = new char[size_texture];
		reader->Read( data_texture, size_texture );

		unsigned char* pixels;
		int width;
		int height;
		int bpp;

		pixels = (uint8_t*)stbi_loadf_from_memory((stbi_uc const *)data_texture, size_texture, &width, &height, &bpp, 4);

		if (width > 0)
		{
			auto texture = graphics->CreateTexture(LLGI::Vec2I(width, height), false, false);
			auto buf = texture->Lock();
			memcpy(buf, pixels, width * height * 4);

			textureData = new Effekseer::TextureData();
			textureData->UserPtr = texture;
			textureData->UserID = 0;
			textureData->TextureFormat = Effekseer::TextureFormatType::ABGR8;
			textureData->Width = width;
			textureData->Height = height;
		}

		delete[] data_texture;
		stbi_image_free(pixels);
		return textureData;
	}

	return nullptr;
}

void TextureLoader::Unload(Effekseer::TextureData* data)
{
	if (data != nullptr && data->UserPtr != nullptr)
	{
		auto texture = (LLGI::G3::Texture*)data->UserPtr;
		texture->Release();
	}

	if (data != nullptr)
	{
		delete data;
	}
}

}

#endif // __EFFEKSEER_RENDERER_INTERNAL_LOADER__