#pragma once
#include "Mile.h"
#include "MileString.h"

namespace Mile
{
    /*
    * @todo: �⺻ �ɷ� Ȯ�� ( ����ȭ, UUID, RTTI, �޸𸮰���<�����غ���> ) 
    */
    class MILE_API Object
    {
    public:
        inline Object( const MString& NewName = MString( TEXT("") ), bool IsValid = true ) :
            Name( NewName ),
            bIsValid( IsValid )
        {
        }

        void SetName( const MString& NewName )
        {
            Name = NewName;
        }

        MString GetName( ) const
        {
            return Name;
        }

    private:
        MString                      Name;
        bool                         bIsValid;

    };
}