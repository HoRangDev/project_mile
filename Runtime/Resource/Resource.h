#pragma once

#include "Core/SubSystem.h"
#include <fstream>
#include <string>

namespace Mile
{
   enum class ResourceType
   {
      RT_Unknown,
      RT_Texture1D,
      RT_Texture2D,
      RT_Texture3D,
      RT_Model,
      RT_Material,
      RT_Shader,
      RT_Audio,
      RT_Script,
      RT_PlainText
   };

   class MEAPI Resource
   {
   public:
      Resource( Context* context, const String& path, ResourceType resourceType = ResourceType::RT_Unknown );
      virtual ~Resource( ) { }

      virtual bool LoadMetafile( ) { }
      virtual bool Init( ) = 0;
      virtual bool Save( const String& filePath ) { return false; }
      bool Save( ) { return Save( this->m_path ); }

      ResourceType GetType( ) const { return m_resourceType; }
      String GetName( ) const { return m_name; }
      String GetFolder( ) const { return m_folder; }
      String GetPath( ) const { return m_path; }
      String GetExt( ) const { return m_ext; }

      static String GetFileNameFromPath( const String& filePath );
      static String GetFolderFromPath( const String& filePath );
      static String GetFileExtensionFromPath( const String& filePath );

   protected:
      Context*   m_context;
      String     m_path;
      String     m_name;
      String     m_folder;
      String     m_ext;
      ResourceType    m_resourceType;

   };

   using ResourcePtr = std::shared_ptr<Resource>;
   using WeakResourcePtr = std::weak_ptr<Resource>;
}