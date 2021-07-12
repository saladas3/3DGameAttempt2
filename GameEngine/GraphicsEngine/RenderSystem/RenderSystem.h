//
// Created by lucai on 7/12/2021.
//

#ifndef INC_3DGAME_RENDERSYSTEM_H
#define INC_3DGAME_RENDERSYSTEM_H

#pragma once

#include "../Prerequisites.h"
#include "DeviceContext/DeviceContext.h"

class RenderSystem {

public:
    // Init the Graphics Engine and DirectX 11 Device
    RenderSystem();

    // Release all the resources loaded
    ~RenderSystem();

public:
    bool compileVertexShader(const wchar_t *file_name, const char *entry_point_name, void **shader_byte_code,
                             size_t *byte_code_size);

    bool compilePixelShader(const wchar_t *file_name, const char *entry_point_name, void **shader_byte_code,
                            size_t *byte_code_size);

    void releaseCompiledShader();

    void setRasterizerState(bool cull_front);

public:
    SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
//    DeviceContextPtr getImmediateDeviceContext();
//    VertexBufferPtr createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list,
//                                       void* shader_byte_code, UINT size_byte_shader);
//    IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list);
//    ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
//    VertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
//    PixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);

private:
    void initRasterizerState();

private:
    DeviceContextPtr m_imm_device_context;

private:
    // DirectX Graphics Infrastructure (DXGI)
    // Members that start with I (Ex: ID3D11Device) are COM (Component Object Model) objects

    ID3D11Device *m_d3d_device = nullptr;
    D3D_FEATURE_LEVEL m_feature_level;
    IDXGIDevice *m_dxgi_device = nullptr;

    /* ------------------------------------------------ *
     * This is a value that indicates what graphics adapter Direct3D should use.
     * A graphics adapter typically refers to a GPU and its video memory, digital-to-analog converter, etc. */
    IDXGIAdapter *m_dxgi_adapter = nullptr;
    /* ------------------------------------------------ */

    /* ------------------------------------------------ *
     * An IDXGIFactory interface implements methods
     * for generating DXGI objects (which handle full screen transitions).
     */
    IDXGIFactory *m_dxgi_factory = nullptr;
    /* ------------------------------------------------ */

    ID3D11DeviceContext *m_imm_context = nullptr;
    ID3DBlob *m_blob = nullptr;
    ID3D11RasterizerState *m_cull_front_state = nullptr;
    ID3D11RasterizerState *m_cull_back_state = nullptr;
    ID3DBlob *m_vsblob = nullptr;
    ID3DBlob *m_psblob = nullptr;
    ID3D11VertexShader *m_vs = nullptr;
    ID3D11PixelShader *m_ps = nullptr;

// Declaring friend classes that can access private members
private:
    friend class SwapChain;

};


#endif //INC_3DGAME_RENDERSYSTEM_H
