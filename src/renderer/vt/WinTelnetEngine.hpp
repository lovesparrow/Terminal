/*++
Copyright (c) Microsoft Corporation

Module Name:
- WinTelnetEngine.hpp

Abstract:
- This is the definition of the VT specific implementation of the renderer.
    This is the win-telnet implementation, which does NOT support advanced 
    sequences such as inserting and deleting lines, and only supports 16 colors.

Author(s):
- Mike Griese (migrie) 01-Sept-2017
--*/

#include "vtrenderer.hpp"
#pragma once
namespace Microsoft
{
    namespace Console
    {
        namespace Render
        {
            class WinTelnetEngine;
        }
    }
};

class Microsoft::Console::Render::WinTelnetEngine : public VtEngine
{
public:
    WinTelnetEngine(_In_ wil::unique_hfile hPipe,
                    _In_reads_(cColorTable) const COLORREF* const ColorTable,
                    _In_ const WORD cColorTable);
    HRESULT UpdateDrawingBrushes(_In_ COLORREF const colorForeground,
                                 _In_ COLORREF const colorBackground,
                                 _In_ WORD const legacyColorAttribute,
                                 _In_ bool const fIncludeBackgrounds) override;
    HRESULT ScrollFrame() override;
    HRESULT InvalidateScroll(_In_ const COORD* const pcoordDelta) override;
protected:
    HRESULT _MoveCursor(_In_ const COORD coord);
private:
    const COLORREF* const _ColorTable;
    const WORD _cColorTable;
    
#ifdef UNIT_TESTING
    friend class VtRendererTest;
#endif
};
