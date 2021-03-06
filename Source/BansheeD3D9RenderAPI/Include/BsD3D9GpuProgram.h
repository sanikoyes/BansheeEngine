//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsD3D9Prerequisites.h"
#include "BsGpuProgram.h"
#include "BsD3D9Resource.h"
#include "BsD3D9EmulatedParamBlocks.h"

namespace BansheeEngine 
{
	/** @addtogroup D3D9
	 *  @{
	 */

	/**	Available optimization levels when compiling a GPU program. */
	enum OptimizationLevel
	{
		OPT_DEFAULT,
		OPT_NONE,
		OPT_0,
		OPT_1,
		OPT_2,
		OPT_3
	};

	/**	DirectX 9 implementation of a GPU program. */
    class BS_D3D9_EXPORT D3D9GpuProgramCore : public GpuProgramCore, public D3D9Resource
    {   
    public:
		virtual ~D3D9GpuProgramCore();

		/**	Sets the preprocessor defines use to compile the program. */
		void setPreprocessorDefines(const String& defines) { mPreprocessorDefines = defines; }

		/**	Sets optimization level to use when compiling the shader. */
		void setOptimizationLevel(OptimizationLevel opt) { mOptimisationLevel = opt; }

    protected:
		friend class D3D9HLSLProgramFactory;

		D3D9GpuProgramCore(const String& source, const String& entryPoint,
			GpuProgramType gptype, GpuProgramProfile profile);

		/** @copydoc GpuProgramCore::initialize */
		void initialize() override;
      
		/**	Loads the GPU program from compiled microcode. */
        virtual void loadFromMicrocode(IDirect3DDevice9* d3d9Device, ID3DXBuffer* microcode) = 0;

	protected:    
		OptimizationLevel mOptimisationLevel;
		String mPreprocessorDefines;
		Vector<D3D9EmulatedParamBlock> mBlocks;
		bool mColumnMajorMatrices;
		ID3DXBuffer* mMicrocode;
    };

	/**	DirectX 9 implementation of a vertex GPU program. */
    class BS_D3D9_EXPORT D3D9GpuVertexProgramCore : public D3D9GpuProgramCore
    {  
    public:
		~D3D9GpuVertexProgramCore();
        
		/**	Returns internal DX9 vertex shader object. */
        IDirect3DVertexShader9* getVertexShader();

		/** @copydoc D3D9Resource::notifyOnDeviceCreate */
		virtual void notifyOnDeviceCreate(IDirect3DDevice9* d3d9Device) override;

		/** @copydoc D3D9Resource::notifyOnDeviceDestroy */
		virtual void notifyOnDeviceDestroy(IDirect3DDevice9* d3d9Device) override;

    protected:
		friend class D3D9HLSLProgramFactory;

		D3D9GpuVertexProgramCore(const String& source, const String& entryPoint, GpuProgramProfile profile);

		/** @copydoc D3D9GpuProgramCore::loadFromMicrocode */
		void loadFromMicrocode(IDirect3DDevice9* d3d9Device, ID3DXBuffer* microcode) override;

	protected:
		Map<IDirect3DDevice9*, IDirect3DVertexShader9*>	mMapDeviceToVertexShader;
    };

    /** Direct3D implementation of low-level fragment programs. */
    class BS_D3D9_EXPORT D3D9GpuFragmentProgramCore : public D3D9GpuProgramCore
    {  
    public:
		~D3D9GpuFragmentProgramCore();

		/**	Returns internal DX9 pixel shader object. */
        IDirect3DPixelShader9* getPixelShader();

		/** @copydoc D3D9Resource::notifyOnDeviceCreate */
		virtual void notifyOnDeviceCreate(IDirect3DDevice9* d3d9Device) override;

		/** @copydoc D3D9Resource::notifyOnDeviceDestroy */
		virtual void notifyOnDeviceDestroy(IDirect3DDevice9* d3d9Device) override;

    protected:
		friend class D3D9HLSLProgramFactory;

		D3D9GpuFragmentProgramCore(const String& source, const String& entryPoint, GpuProgramProfile profile);

		/** @copydoc D3D9GpuProgramCore::loadFromMicrocode */
		void loadFromMicrocode(IDirect3DDevice9* d3d9Device, ID3DXBuffer* microcode) override;

	protected:
		Map<IDirect3DDevice9*, IDirect3DPixelShader9*> mMapDeviceToPixelShader;
    };

	/** @} */
}