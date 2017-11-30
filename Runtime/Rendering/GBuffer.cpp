#include "GBuffer.h"
#include "RenderTargetDX11.h"
#include "DepthStencilBufferDX11.h"

namespace Mile
{
   GBuffer::GBuffer( RendererDX11* renderer ) :
      m_renderer( renderer ),
      m_depthStencilBuffer( nullptr ),
      m_normalBuffer( nullptr ),
      m_positionBuffer( nullptr )
   {
   }

   GBuffer::~GBuffer( )
   {
      SafeDelete( m_normalBuffer );
      SafeDelete( m_positionBuffer );
   }

   bool GBuffer::Init( unsigned int width, unsigned int height )
   {
      bool bIsInitialized = m_normalBuffer != nullptr || m_positionBuffer != nullptr;
      if ( m_renderer == nullptr || bIsInitialized )
      {
         return false;
      }

      m_normalBuffer = new RenderTargetDX11( m_renderer );
      m_positionBuffer = new RenderTargetDX11( m_renderer );

      if ( !m_normalBuffer->Init( width, height ) )
      {
         return false;
      }

      if ( !m_positionBuffer->Init( width, height ) )
      {
         return false;
      }

      return true;
   }

   bool GBuffer::BindAsRenderTarget( )
   {
      bool bIsInitialized = m_normalBuffer != nullptr && m_positionBuffer != nullptr;
      if ( m_renderer == nullptr || !bIsInitialized )
      {
         return false;
      }

      auto deviceContext = m_renderer->GetDeviceContext( );

      ID3D11DepthStencilView* dsv = nullptr;
      if ( m_depthStencilBuffer != nullptr )
      {
         dsv = m_depthStencilBuffer->GetDSV( );
      }

      std::array<ID3D11RenderTargetView*, 2> targets{
         m_normalBuffer->GetRTV( ),
         m_positionBuffer->GetRTV( )
      };

      deviceContext->OMSetRenderTargets( 2, targets.data( ), dsv );
      return true;
   }

   bool GBuffer::BindAsShaderResource( unsigned int startSlot )
   {
      bool bIsInitialized = m_normalBuffer != nullptr && m_positionBuffer != nullptr;
      if ( m_renderer == nullptr || !bIsInitialized )
      {
         return false;
      }

      m_normalBuffer->BindAsShaderResource( startSlot + 0, ShaderType::PixelShader );
      m_positionBuffer->BindAsShaderResource( startSlot + 1, ShaderType::PixelShader );

      return true;
   }

   void GBuffer::Unbind( )
   {
      bool bIsInitialized = m_normalBuffer != nullptr && m_positionBuffer != nullptr;
      if ( bIsInitialized )
      {
         m_normalBuffer->Unbind( );
         m_positionBuffer->Unbind( );
      }
   }
}