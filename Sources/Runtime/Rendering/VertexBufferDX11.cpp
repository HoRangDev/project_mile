#include "Rendering/VertexBufferDX11.h"

namespace Mile
{
   VertexBufferDX11::VertexBufferDX11(RendererDX11* renderer) :
      m_stride(0),
      BufferDX11(renderer)
   {
   }

   bool VertexBufferDX11::Bind(ID3D11DeviceContext& deviceContext, unsigned int startSlot)
   {
      if (RenderObject::IsBindable())
      {
         unsigned int offset = 0;
         deviceContext.IASetVertexBuffers(startSlot, 1, reinterpret_cast<ID3D11Buffer**>(&m_resource), &m_stride, &offset);

         return true;
      }

      return false;
   }
}