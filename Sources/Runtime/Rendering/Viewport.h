#pragma once
#include "Rendering/RenderObject.h"

namespace Mile
{
   class RendererDX11;
   class MEAPI Viewport : public RenderObject
   {
   public:
      Viewport(RendererDX11* renderer);

      void SetWidth(float width) { m_width = width; }
      float GetWidth() const { return m_width; }

      void SetHeight(float height) { m_height = height; }
      float GetHeight() const { return m_height; }

      void SetMinDepth(float minDepth) { m_minDepth = minDepth; }
      float GetMinDepth() const { return m_minDepth; }

      void SetMaxDepth(float maxDepth) { m_maxDepth = maxDepth; }
      float GetMaxDepth() const { return m_maxDepth; }

      void SetTopLeftX(float topLeftX) { m_topLeftX = topLeftX; }
      float GetTopLeftX() const { return m_topLeftX; }

      void SetTopLeftY(float topLeftY) { m_topLeftY = topLeftY; }
      float GetTopLeftY() const { return m_topLeftY; }

      D3D11_VIEWPORT GetD3DViewport() const;

      bool Bind(ID3D11DeviceContext& deviceContext);

   public:
      float m_width;
      float m_height;
      float m_minDepth;
      float m_maxDepth;
      float m_topLeftX;
      float m_topLeftY;

   };
}
