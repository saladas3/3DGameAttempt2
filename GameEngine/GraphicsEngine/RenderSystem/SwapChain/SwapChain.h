/*
 Created by lucai on 7/12/2021.
 The SwapChain is a collection of buffers that swap their values continuously
 in order to prevent tearing. This is basically the resource that draws the images on the screen
*/

#ifndef INC_3DGAME_SWAPCHAIN_H
#define INC_3DGAME_SWAPCHAIN_H

#pragma once

#include "../../Prerequisites.h"
#include "../RenderSystem.h"

class SwapChain {

public:
    SwapChain(HWND hWnd, UINT width, UINT height, RenderSystem *system);
    ~SwapChain();
    void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
    void resize(unsigned int width, unsigned int height);
    bool present(bool vsync);

private:
    void reloadBuffers(UINT width, UINT height);

private:
    IDXGISwapChain *m_swap_chain = nullptr;
    ID3D11RenderTargetView *m_rtv = nullptr;
    ID3D11DepthStencilView *m_dsv = nullptr;
    RenderSystem *m_r_system = nullptr;

private:
    friend class DeviceContext;

};

#endif //INC_3DGAME_SWAPCHAIN_H
