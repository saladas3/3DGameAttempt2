/*
 Created by lucai on 7/12/2021.
 A device context is similar to a device, but it is responsible for managing the GPU
 and the rendering pipeline (the device mostly handles video memory).
 This object is used to render graphics and to determine how they will be rendered.
*/

#ifndef INC_3DGAME_DEVICECONTEXT_H
#define INC_3DGAME_DEVICECONTEXT_H

#pragma once

#include "../../Prerequisites.h"
#include "../SwapChain/SwapChain.h"

class DeviceContext {

public:
    DeviceContext(ID3D11DeviceContext *device_context, RenderSystem *system);
    ~DeviceContext();

    void clearRenderTargetColor(const SwapChainPtr &swap_chain, float red, float green, float blue, float alpha);
    void clearRenderTargetColor(const TexturePtr &render_target, float red, float green, float blue, float alpha);
    void setVertexBuffer(const VertexBufferPtr &vertex_buffer);
    void setIndexBuffer(const IndexBufferPtr &index_buffer);
    void clearDepthStencil(const TexturePtr &depth_stencil);
    void setRenderTarget(const TexturePtr &render_target, const TexturePtr &depth_stencil);
    void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
    void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
    void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
    void setViewportSize(UINT width, UINT height);
    void setVertexShader(const VertexShaderPtr &vertex_shader);
    void setPixelShader(const PixelShaderPtr &pixel_shader);
    void setTexture(const VertexShaderPtr &vertex_shader, const TexturePtr *texture, unsigned int num_textures);
    void setTexture(const PixelShaderPtr &pixel_shader, const TexturePtr *texture, unsigned int num_textures);
    void setConstantBuffer(const VertexShaderPtr &vertex_shader, const ConstantBufferPtr &buffer);
    void setConstantBuffer(const PixelShaderPtr &pixel_shader, const ConstantBufferPtr &buffer);

private:
    ID3D11DeviceContext *m_device_context = nullptr;
    RenderSystem *m_system = nullptr;

private:
    friend class ConstantBuffer;
    friend class IndexBuffer;

};

#endif //INC_3DGAME_DEVICECONTEXT_H
