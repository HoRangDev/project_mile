#pragma once
#include "ActorComponent.h"
#include "Transform.h"

namespace Mile
{
    /**
    * SceneComponent는 ActorComponent에 Transform 정보를 확장하고 서로 붙일수있는 Component 이다.
    */
    class MILE_API SceneComponent : public ActorComponent
    {
        using ComponentList = std::vector<SceneComponent*>;
    public:
        SceneComponent( const MString& NewName ) :
            ParentPrivate( nullptr ),
            ActorComponent( NewName )
        {
        }

        void SetTransform( const Transform& NewTransform )
        {
            Transform = NewTransform;
        }

        Transform& GetTransform( )
        {
            return Transform;
        }

        bool AttachTo( SceneComponent* NewParent );
        void DetachFromComponent( );

        SceneComponent* GetParent( ) const
        {
            return ParentPrivate;
        }

    protected:
        void AddAttachedComponent( SceneComponent* Component );
        bool RemoveAttachedComponent( SceneComponent* Component );

    private:
        Transform Transform;
        SceneComponent* ParentPrivate;
        ComponentList Components;

    };
}