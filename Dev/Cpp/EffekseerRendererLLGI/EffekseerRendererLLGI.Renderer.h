
#ifndef	__EFFEKSEERRENDERER_LLGI_RENDERER_H__
#define	__EFFEKSEERRENDERER_LLGI_RENDERER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRendererLLGI.Base.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.Renderer.h"

#include "LLGI/G3/LLGI.G3.Graphics.h"
#include "LLGI/G3/LLGI.G3.VertexBuffer.h"
#include "LLGI/G3/LLGI.G3.IndexBuffer.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerRendererLLGI
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
@brief	テクスチャ読込クラスを生成する。
*/
::Effekseer::TextureLoader* CreateTextureLoader(LLGI::G3::Graphics* graphics, ::Effekseer::FileInterface* fileInterface = NULL);

/**
@brief	モデル読込クラスを生成する。
*/
::Effekseer::ModelLoader* CreateModelLoader(LLGI::G3::Graphics* graphics, ::Effekseer::FileInterface* fileInterface = NULL);


struct FixedShader
{
	LLGI::DataStructure StandardTexture[2];
	LLGI::DataStructure Standard[2];
	LLGI::DataStructure StandardDistortedTexture[2];
	LLGI::DataStructure StandardDistorted[2];

	LLGI::DataStructure ModelShaderLightingTextureNormal[2];
	LLGI::DataStructure ModelShaderLightingNormal[2];
	LLGI::DataStructure ModelShaderLightingTexture[2];
	LLGI::DataStructure ModelShaderLighting[2];
	LLGI::DataStructure ModelShaderTexture[2];
	LLGI::DataStructure ModelShader[2];
	LLGI::DataStructure ModelShaderDistortionTexture[2];
	LLGI::DataStructure ModelShaderDistortion[2];
};

/**
	@brief	描画クラス
*/
class Renderer
	: public ::EffekseerRenderer::Renderer
{
protected:
	Renderer() {}
	virtual ~Renderer() {}

public:
	/**
	*/
	static Renderer* Create(LLGI::G3::Graphics* graphics, int32_t squareMaxCount);

	virtual LLGI::G3::Graphics* GetGraphics() = 0;

	/**
		@brief	\~English	Get background
				\~Japanese	背景を取得する
	*/
	virtual Effekseer::TextureData* GetBackground() = 0;

	/**
		@brief	\~English	Set background
				\~Japanese	背景を設定する
	*/
	virtual void SetBackground(LLGI::G3::Texture* background) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
@brief	\~English	Model
		\~Japanese	モデル
*/
class Model 
	: public Effekseer::Model
{
private:

public:

	struct InternalModel
	{
		LLGI::G3::VertexBuffer*		VertexBuffer;
		LLGI::G3::IndexBuffer*		IndexBuffer;
		int32_t				VertexCount;
		int32_t				IndexCount;
		int32_t				FaceCount;

		InternalModel()
		{
			VertexBuffer = nullptr;
			IndexBuffer = nullptr;
			VertexCount = 0;
			IndexCount = 0;
			FaceCount = 0;
		}

		virtual ~InternalModel()
		{
			ES_SAFE_RELEASE(VertexBuffer);
			ES_SAFE_RELEASE(IndexBuffer);
		}
	};

	InternalModel*				InternalModels = nullptr;
	int32_t						ModelCount;

	Model( uint8_t* data, int32_t size )
		: Effekseer::Model	( data, size )
		, InternalModels(nullptr)
		, ModelCount(0)
	{
		this->m_vertexSize = sizeof(VertexWithIndex);
	}

	virtual ~Model()
	{
		ES_SAFE_DELETE_ARRAY(InternalModels);
	}
};


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_LLGI_RENDERER_H__
