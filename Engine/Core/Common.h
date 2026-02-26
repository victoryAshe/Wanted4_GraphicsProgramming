#pragma once

// Release D3D resources.
template<typename T>
void SafeRelease(T*& resource)
{
	if (resource)
	{
		resource->Release();
		resource = nullptr;
	}
}