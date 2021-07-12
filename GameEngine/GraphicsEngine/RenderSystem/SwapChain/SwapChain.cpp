//
// Created by lucai on 7/12/2021.
//

#include "SwapChain.h"

SwapChain::SwapChain(HWND hWnd, UINT width, UINT height, RenderSystem *r_system) : m_r_system(r_system) {
    ID3D11Device *device = m_r_system->m_d3d_device;

    DXGI_SWAP_CHAIN_DESC desc;

    // Clear out the struct for use
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    // TODO: Parameterize the descriptor from user input
    desc.BufferCount = 1;                                   // one back buffer
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
    desc.OutputWindow = hWnd;                               // the window to be used
    // how many multisamples (for anti-aliasing; the higher the better)
    desc.SampleDesc.Count = 4;
    desc.SampleDesc.Quality = 0;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    desc.Windowed = TRUE;                                   // windowed/full-screen mode

    // Create the swap chain for the window indicated by HWND parameter
    HRESULT hr = m_r_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

    if (FAILED(hr))
        throw std::exception("SwapChain not created successfully");

    reloadBuffers(width, height);
}

void SwapChain::setFullScreen(bool fullscreen, unsigned int width, unsigned int height) {
    resize(width, height);
    m_swap_chain->SetFullscreenState(fullscreen, nullptr);
}

void SwapChain::resize(unsigned int width, unsigned int height) {
    if (m_rtv)
        m_rtv->Release();
    if (m_dsv)
        m_dsv->Release();

    m_swap_chain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    reloadBuffers(width, height);
}

bool SwapChain::present(bool vsync) {
    m_swap_chain->Present(vsync, NULL);
    return true;
}

void SwapChain::reloadBuffers(UINT width, UINT height) {
    ID3D11Device *device = m_r_system->m_d3d_device;

    // Get the back backBuffer color and create its render target view
    ID3D11Texture2D *backBuffer = nullptr;
    HRESULT hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **) &backBuffer);

    if (FAILED(hr))
        throw std::exception("SwapChain not created successfully");

    // The render target is like a blank canvas where we draw the shapes
    // (for example the back buffer of the swap chain)
    hr = device->CreateRenderTargetView(backBuffer, nullptr, &m_rtv);
    backBuffer->Release();
    if (FAILED(hr))
        throw std::exception("SwapChain not created successfully");

    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = width;
    tex_desc.Height = height;
    tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    hr = device->CreateTexture2D(&tex_desc, nullptr, &backBuffer);
    if (FAILED(hr))
        throw std::exception("SwapChain not created successfully");

    hr = device->CreateDepthStencilView(backBuffer, nullptr, &m_dsv);
    if (FAILED(hr))
        throw std::exception("SwapChain not created successfully");

    backBuffer->Release();

}

SwapChain::~SwapChain() {
    m_rtv->Release();
    // The release of depth stencil view was not here originally. Added by me, remove if it gives errors
    m_dsv->Release();
    m_swap_chain->Release();
}
