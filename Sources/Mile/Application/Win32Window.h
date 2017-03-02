#pragma once
#include "MileWindow.h"

namespace Mile
{
    /**
    * Win32 플랫폼에서 동작하는 윈도우를 나타내는 클래스
    */
    class MILE_API Win32Window : public MileWindow
    {
    public:
        Win32Window( const MString& NewTitle, 
            uint64 NewWidth = 800, 
            uint64 NewHeight = 600,
            EWindowMode NewWindowMode = EWindowMode::Windowed) :
            MileWindow(
                NewTitle,
                NewWidth, NewHeight,
                NewWindowMode )
        {
        }

        FORCEINLINE HWND GetHandle( ) const { return Handle; }

        virtual bool Initialize( ) override;
        virtual void DeInitialize( ) override;
        virtual void OnResize( uint64 NewWidth, uint64 NewHeight ) override;
        virtual void OnWindowModeChange( EWindowMode NewWindowMode ) override;

    private:
        HWND Handle;

    };
}