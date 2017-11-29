#pragma once

#include "Resource.h"

namespace Mile
{
   enum class TextureType
   {
      DiffuseMap,
      NormalMap
   };

   class Texture2D;
   class MEAPI Material : public Resource
   {
   public:
      Material( Context* context, const String& filePath ) :
         m_specExp( 1.0f ),
         m_specIntensity( 0.0f ),
         Resource( context, filePath, ResourceType::RT_Material )
      {
      }

      virtual bool Init( ) override;
      virtual bool SaveTo( const String& filePath ) override;

      // Specular Exponential
      float GetSpecularExp( ) const { return m_specExp; }
      void SetSpecularExp( float specExp ) { m_specExp = specExp; }
      // Specular Intensity
      float GetSpecularIntensity( ) const { return m_specIntensity; }
      void SetSpecularIntensity( float specIntensity ) { m_specIntensity = specIntensity; }
      // Diffuse map/Texture
      std::weak_ptr<Texture2D> GetDiffuseMap( ) const { return m_diffuseMap; }
      void SetDiffuseMap( std::weak_ptr<Texture2D> diffuseMap ) { m_diffuseMap = diffuseMap; }
      // Normal map/Texture
      std::weak_ptr<Texture2D> GetNormalMap( ) const { return m_normalMap; }
      void SetNormalMap( std::weak_ptr<Texture2D> normalMap ) { m_normalMap = normalMap; }

   private:
      float                      m_specExp;
      float                      m_specIntensity;
      std::weak_ptr<Texture2D>   m_diffuseMap;
      std::weak_ptr<Texture2D>   m_normalMap;

   };
}