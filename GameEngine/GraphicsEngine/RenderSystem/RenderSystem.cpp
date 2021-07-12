//
// Created by lucai on 7/12/2021.
//

#include "RenderSystem.h"

RenderSystem::RenderSystem() {
    D3D_DRIVER_TYPE driver_types[] =
            {
                    D3D_DRIVER_TYPE_HARDWARE,
                    D3D_DRIVER_TYPE_WARP,
                    D3D_DRIVER_TYPE_REFERENCE
            };
    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] =
            {
                    D3D_FEATURE_LEVEL_11_0
            };
    UINT num_feature_levels = ARRAYSIZE(feature_levels);

    HRESULT res = 0;
    for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) {
        res = D3D11CreateDevice(nullptr, driver_types[driver_type_index], nullptr, NULL, feature_levels,
                                num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

        if (SUCCEEDED(res))
            break;

        ++driver_type_index;
    }

    if (FAILED(res))
        throw std::exception("RenderSystem not created successfully");

    m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);

    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void **) &m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void **) &m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void **) &m_dxgi_factory);

    initRasterizerState();
}

bool RenderSystem::compileVertexShader(const wchar_t *file_name, const char *entry_point_name, void **shader_byte_code,
                                       size_t *byte_code_size) {
    ID3DBlob *error_blob = nullptr;
    if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob,
                                        &error_blob))) {
        if (error_blob) error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

bool RenderSystem::compilePixelShader(const wchar_t *file_name, const char *entry_point_name, void **shader_byte_code,
                                      size_t *byte_code_size) {
    ID3DBlob *error_blob = nullptr;
    if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob,
                                        &error_blob))) {
        if (error_blob) error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

void RenderSystem::releaseCompiledShader() {
    if (m_blob) m_blob->Release();
}

void RenderSystem::setRasterizerState(bool cull_front) {
    if (cull_front)
        m_imm_context->RSSetState(m_cull_front_state);
    else
        m_imm_context->RSSetState(m_cull_back_state);
}

void RenderSystem::initRasterizerState() {
    D3D11_RASTERIZER_DESC desc = {};

    desc.CullMode = D3D11_CULL_FRONT;
    desc.DepthClipEnable = true;
    desc.FillMode = D3D11_FILL_SOLID;
    m_d3d_device->CreateRasterizerState(&desc, &m_cull_front_state);

    desc.CullMode = D3D11_CULL_BACK;
    m_d3d_device->CreateRasterizerState(&desc, &m_cull_back_state);
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height) {
    SwapChainPtr sc = nullptr;

    try {
        sc = std::make_shared<SwapChain>(hwnd, width, height, this);
    }
    catch (...) {}

    return sc;
}

RenderSystem::~RenderSystem() {
    if (m_vs)m_vs->Release();
    if (m_ps)m_ps->Release();

    if (m_vsblob)m_vsblob->Release();
    if (m_psblob)m_psblob->Release();

    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();
    m_d3d_device->Release();
}
