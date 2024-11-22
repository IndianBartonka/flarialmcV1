#pragma once

#include "../Hook.hpp"
#include <dxgi1_6.h>

#include <d2d1_3.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <winrt/base.h>

#include "kiero.h"
#include "../../../../SDK/Client/Render/FrameTransform.hpp"

class SwapchainHook : public Hook {
private:
    static HRESULT swapchainCallback(IDXGISwapChain3 *pSwapChain, UINT syncInterval, UINT flags);


public:
    typedef HRESULT(__thiscall *SwapchainOriginal)(IDXGISwapChain3 *, UINT, UINT);

    static inline SwapchainOriginal funcOriginal = nullptr;
    static bool init;

    SwapchainHook();

    void enableHook() override;

    static ID3D12CommandQueue* queue;
    static inline std::vector<winrt::com_ptr<IDXGISurface1>> DXGISurfaces;
    static inline std::vector<winrt::com_ptr<ID2D1Bitmap1>> D2D1Bitmaps;
    static inline std::vector<winrt::com_ptr<ID3D11Resource>> D3D11Resources;
    static inline IDXGISwapChain3* swapchain;
    static inline winrt::com_ptr<ID3D12DescriptorHeap> D3D12DescriptorHeap;
    static inline winrt::com_ptr<ID3D11On12Device> d3d11On12Device;
    static inline winrt::com_ptr<ID2D1Bitmap1> D2D1Bitmap;
    static inline winrt::com_ptr<ID3D11DeviceContext> context;

    static inline uintptr_t bufferCount;
    static bool hasResized;
    static int currentBitmap;

    static inline std::mutex frameTransformsMtx;
    static inline std::queue<FrameTransform> FrameTransforms;
    static inline int transformDelay = 3;

    static inline UINT flagsreal;
};