#include "Engine.h"
#include "Context.h"
#include "Config.h"
#include "Window.h"
#include "Resource\ResourceManager.h"
#include "World.h"

namespace Mile
{
   Engine::Engine( Context* context ) :
      SubSystem( context )
   {
      m_context->RegisterSubSystem( this );

      m_configSys = new ConfigSystem( m_context );
      m_context->RegisterSubSystem( m_configSys );

      m_window = new Window( m_context );
      m_context->RegisterSubSystem( m_window );

      m_resourceManager = new ResourceManager( m_context );
      m_context->RegisterSubSystem( m_resourceManager );

      m_world = new World( m_context );
      m_context->RegisterSubSystem( m_world );
   }

   bool Engine::Initialize( )
   {
      // -* Initialize subsystems *-

      if ( !m_context->GetSubSystem<ConfigSystem>( ) )
      {
         return false;
      }

      if ( !m_context->GetSubSystem<Window>( ) )
      {
         return false;
      }

      // Initialize Resource manager
      if ( !m_context->GetSubSystem<ResourceManager>( )->Initialize( ) )
      {
         return false;
      }

      // Initialize World
      if ( !m_context->GetSubSystem<World>( )->Initialize( ) )
      {
         //@TODO: Add Log
         return false;
      }

      return true;
   }

   void Engine::Update( )
   {
      // Update subsystems
      m_world->Update( );
   }

   void Engine::ShutDown( )
   {
      m_world = nullptr;
      SafeDelete( m_context );
   }
}