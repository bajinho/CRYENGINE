// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "GpuComputeBackend.h"

namespace gpu
{
// same definition as in shader
const UINT BITONIC_BLOCK_SIZE = 1024;
const UINT TRANSPOSE_BLOCK_SIZE = 16;
const UINT NUM_ELEMENTS = (BITONIC_BLOCK_SIZE * BITONIC_BLOCK_SIZE);

class CBitonicSort
{
public:
	struct SBitonicSortItem
	{
		uint32 key;
		uint32 payload;
	};

	struct CParams
	{
		uint32 iLevel;
		uint32 iLevelMask;
		uint32 iWidth;
		uint32 iHeight;
	};
	CBitonicSort();
	void                       Sort(size_t numElements);
	ID3D11UnorderedAccessView* GetUAV() { return m_data.GetUAV(); }
	ID3D11ShaderResourceView*  GetSRV() { return m_data.GetSRV(); }
private:
	void                       SyncParams(uint32 iLevel, uint32 iLevelMask, uint32 iWidth, uint32 iHeight);
	CTypedConstantBuffer<CParams, 8>                       m_params;
	CTypedResource<SBitonicSortItem, BufferFlagsReadWrite> m_data;
	CTypedResource<SBitonicSortItem, BufferFlagsReadWrite> m_transposeData;
	CComputeBackend m_backend;
};
}
