//
// Created by lucai on 7/12/2021.
//

#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext *device_context, RenderSystem *system) : m_system(system),
                                                                                          m_device_context(
                                                                                                  device_context) {}

DeviceContext::~DeviceContext() {
    m_device_context->Release();
}

void DeviceContext::clearRenderTargetColor(const SwapChainPtr &swap_chain,
                                           float red, float green, float blue, float alpha) {
    FLOAT clear_color[] = {red, green, blue, alpha};
    m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
    m_device_context->ClearDepthStencilView(swap_chain->m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, swap_chain->m_dsv);
}

void DeviceContext::setVertexBuffer(const VertexBufferPtr &vertex_buffer) {

}

void DeviceContext::setIndexBuffer(const IndexBufferPtr &index_buffer) {

}

void DeviceContext::clearRenderTargetColor(const TexturePtr &render_target,
                                           float red, float green, float blue, float alpha) {

}

void DeviceContext::clearDepthStencil(const TexturePtr &depth_stencil) {

}

void DeviceContext::setRenderTarget(const TexturePtr &render_target, const TexturePtr &depth_stencil) {

}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index) {
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location) {
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_device_context->DrawIndexed(index_count, start_index_location, (int)start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index) {
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height) {
    D3D11_VIEWPORT vp = {};
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_device_context->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(const VertexShaderPtr &vertex_shader) {

}

void DeviceContext::setPixelShader(const PixelShaderPtr &pixel_shader) {

}

void DeviceContext::setTexture(const VertexShaderPtr &vertex_shader,
                               const TexturePtr *texture, unsigned int num_textures) {

}

void DeviceContext::setTexture(const PixelShaderPtr &pixel_shader,
                               const TexturePtr *texture, unsigned int num_textures) {

}

void DeviceContext::setConstantBuffer(const VertexShaderPtr &vertex_shader, const ConstantBufferPtr &buffer) {

}

void DeviceContext::setConstantBuffer(const PixelShaderPtr &pixel_shader, const ConstantBufferPtr &buffer) {

}
