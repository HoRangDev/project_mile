#include "RasterizerState.h"
#include "RendererDX11.h"

namespace Mile
{
   RasterizerState::RasterizerState( RendererDX11* renderer ) :
      m_renderer( renderer ),
      m_rasterizerState( nullptr ),
      m_bIsDirty( true ),
      m_bIsWireframe( false ),
      m_cullMode( CullMode::CULL_BACK ),
      m_bFrontCounterClockwise( false ),
      m_depthBias( 0 ),
      m_slopeScaledDepthBias( 0.0f ),
      m_depthBiasClamp( 0.0f ),
      m_bIsDepthClipEnable( false )
   {
   }

   RasterizerState::~RasterizerState( )
   {
      SafeRelease( m_rasterizerState );
   }

   bool RasterizerState::Init( )
   {
      if ( m_renderer == nullptr )
      {
         return false;
      }

      D3D11_RASTERIZER_DESC desc;
      ZeroMemory( &desc, sizeof( desc ) );
      desc.FillMode = ( m_bIsWireframe ) ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
      
      switch ( m_cullMode )
      {
      case CullMode::CULL_NONE:
         desc.CullMode = D3D11_CULL_NONE;
         break;

      case CullMode::CULL_BACK:
         desc.CullMode = D3D11_CULL_BACK;
         break;

      case CullMode::CULL_FRONT:
         desc.CullMode = D3D11_CULL_FRONT;
         break;
      }

      desc.FrontCounterClockwise = m_bFrontCounterClockwise;
      desc.DepthBias = m_depthBias;
      desc.SlopeScaledDepthBias = m_slopeScaledDepthBias;
      desc.DepthBiasClamp = m_depthBiasClamp;
      desc.DepthClipEnable = m_bIsDepthClipEnable;
      desc.ScissorEnable = false;
      desc.MultisampleEnable = false;
      desc.AntialiasedLineEnable = false;

      auto device = m_renderer->GetDevice( );
      auto result = device->CreateRasterizerState( &desc, &m_rasterizerState );
      if ( FAILED( result ) )
      {
         m_bIsDirty = true;
         return false;
      }

      m_bIsDirty = false;
      return true;
   }

   bool RasterizerState::Bind( )
   {
      if ( m_renderer == nullptr )
      {
         return false;
      }

      if ( m_bIsDirty )
      {
         SafeRelease( m_rasterizerState );
         if ( !Init( ) )
         {
            return false;
         }
      }

      auto deviceContext = m_renderer->GetDeviceContext( );
      deviceContext->RSSetState( m_rasterizerState );

      return true;
   }
}