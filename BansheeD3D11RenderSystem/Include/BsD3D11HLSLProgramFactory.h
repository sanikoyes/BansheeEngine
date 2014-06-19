#pragma once

#include "BsD3D11Prerequisites.h"
#include "BsGpuProgramManager.h"

namespace BansheeEngine
{
	class BS_D3D11_EXPORT D3D11HLSLProgramFactory : public GpuProgramFactory
	{
	public:
		D3D11HLSLProgramFactory();
		~D3D11HLSLProgramFactory();

		const String& getLanguage(void) const;
		GpuProgramPtr create(const String& source, const String& entryPoint, GpuProgramType gptype, 
			GpuProgramProfile profile, const Vector<HGpuProgInclude>* includes, bool requireAdjacencyInfo);
		GpuProgramPtr create(GpuProgramType type);

	protected:
		static const String LANGUAGE_NAME;
	};
}