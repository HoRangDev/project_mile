#include "Rendering/Texture2DBaseDX11.h"
#include "Rendering/RendererDX11.h"

namespace Mile
{
   Texture2DBaseDX11::Texture2DBaseDX11(RendererDX11* renderer) :
      m_texture(nullptr),
      m_srv(nullptr),
      m_mipLevels(1),
      m_width(0),
      m_height(0),
      ResourceDX11(renderer)
   {
   }

   Texture2DBaseDX11::~Texture2DBaseDX11()
   {
      SafeRelease(m_srv);
      SafeRelease(m_texture);
   }

   bool Texture2DBaseDX11::Bind(ID3D11DeviceContext& deviceContext, unsigned int bindSlot, EShaderType bindShader)
   {
      if (RenderObject::IsBindable())
      {
         switch (bindShader)
         {
         case EShaderType::VertexShader:
            deviceContext.VSSetShaderResources(bindSlot, 1, &m_srv);
            break;
         case EShaderType::DomainShader:
            deviceContext.DSSetShaderResources(bindSlot, 1, &m_srv);
            break;
         case EShaderType::HullShader:
            deviceContext.HSSetShaderResources(bindSlot, 1, &m_srv);
            break;
         case EShaderType::GeometryShader:
            deviceContext.GSSetShaderResources(bindSlot, 1, &m_srv);
            break;
         case EShaderType::PixelShader:
            deviceContext.PSSetShaderResources(bindSlot, 1, &m_srv);
            break;
         }

         return true;
      }

      return false;
   }

   void Texture2DBaseDX11::Unbind(ID3D11DeviceContext& deviceContext, unsigned int boundSlot, EShaderType boundShader)
   {
      if (RenderObject::IsBindable())
      {
         ID3D11ShaderResourceView* nullSRV = nullptr;
         switch (boundShader)
         {
         case EShaderType::VertexShader:
            deviceContext.VSSetShaderResources(boundSlot, 1, &nullSRV);
            break;
         case EShaderType::HullShader:
            deviceContext.HSSetShaderResources(boundSlot, 1, &nullSRV);
            break;
         case EShaderType::DomainShader:
            deviceContext.DSSetShaderResources(boundSlot, 1, &nullSRV);
            break;
         case EShaderType::GeometryShader:
            deviceContext.GSSetShaderResources(boundSlot, 1, &nullSRV);
            break;
         case EShaderType::PixelShader:
            deviceContext.PSSetShaderResources(boundSlot, 1, &nullSRV);
            break;
         }
      }
   }

   void Texture2DBaseDX11::GenerateMips(ID3D11DeviceContext& deviceContext)
   {
      if (RenderObject::IsBindable())
      {
         if (m_srv != nullptr)
         {
            deviceContext.GenerateMips(m_srv);
         }
      }
   }

   bool Texture2DBaseDX11::InitSRV(D3D11_TEXTURE2D_DESC desc, bool bIsCubemap)
   {
      /* InitSRV 가 불려진다는것은 아직 Texture2dDX11의 초기화가 완전히 끝나지 않았단 것 이기 때문에. **/
      if (RenderObject::IsInitializable())
      {
         RendererDX11* renderer = GetRenderer();
         auto& device = renderer->GetDevice();
         D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
         ZeroMemory(&srvDesc, sizeof(srvDesc));
         srvDesc.Format = desc.Format;
         if (bIsCubemap)
         {
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
            srvDesc.TextureCube.MipLevels = -1;
            srvDesc.TextureCube.MostDetailedMip = 0;
         }
         else
         {
            srvDesc.Texture2D.MipLevels = m_mipLevels;
            srvDesc.Texture2D.MostDetailedMip = 0;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
         }

         auto result = device.CreateShaderResourceView(m_texture, &srvDesc, &m_srv);
         if (!FAILED(result))
         {
            return true;
         }
      }

      return false;
   }
}
