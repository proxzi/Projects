#ifndef __VSN_WINDOWS_H
#define __VSN_WINDOWS_H

#if defined(VSN_CC_BOR)
// Borland's windows.h does not set these correctly, resulting in
// unusable WinSDK standard dialogs
#ifndef WINVER
#  define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0501
#endif
#endif

#if defined(VSN_CC_MINGW)
// mingw's windows.h does not set _WIN32_WINNT, resulting breaking compilation
#ifndef WINVER
#  define WINVER 0x501
#endif
#endif

#ifndef NOMINMAX
#  define NOMINMAX
#endif
#include <windows.h>

#if defined(_WIN32_IE) && _WIN32_IE < 0x0501
#  undef _WIN32_IE
#endif
#if !defined(_WIN32_IE)
#  define _WIN32_IE 0x0501
#endif

#ifdef _WIN32_WCE
#include <ceconfig.h>
#endif

// already defined when compiled with WINVER >= 0x0500
#ifndef SPI_SETMENUANIMATION
#define SPI_SETMENUANIMATION 0x1003
#endif
#ifndef SPI_SETMENUFADE
#define SPI_SETMENUFADE 0x1013
#endif
#ifndef SPI_SETCOMBOBOXANIMATION
#define SPI_SETCOMBOBOXANIMATION 0x1005
#endif
#ifndef SPI_SETTOOLTIPANIMATION
#define SPI_SETTOOLTIPANIMATION 0x1017
#endif
#ifndef SPI_SETTOOLTIPFADE
#define SPI_SETTOOLTIPFADE 0x1019
#endif
#ifndef SPI_SETUIEFFECTS
#define SPI_SETUIEFFECTS 0x103F
#endif
#ifndef SPI_GETMENUANIMATION
#define SPI_GETMENUANIMATION 0x1002
#endif
#ifndef SPI_GETMENUFADE
#define SPI_GETMENUFADE 0x1012
#endif
#ifndef SPI_GETCOMBOBOXANIMATION
#define SPI_GETCOMBOBOXANIMATION 0x1004
#endif
#ifndef SPI_GETTOOLTIPANIMATION
#define SPI_GETTOOLTIPANIMATION 0x1016
#endif
#ifndef SPI_GETTOOLTIPFADE
#define SPI_GETTOOLTIPFADE 0x1018
#endif
#ifndef SPI_GETUIEFFECTS
#define SPI_GETUIEFFECTS 0x103E
#endif
#ifndef SPI_GETKEYBOARDCUES
#define SPI_GETKEYBOARDCUES 0x100A
#endif
#ifndef SPI_GETGRADIENTCAPTIONS
#define SPI_GETGRADIENTCAPTIONS 0x1008
#endif
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef ETO_PDY
#define ETO_PDY 0x2000
#endif
#ifndef COLOR_GRADIENTACTIVECAPTION
#define COLOR_GRADIENTACTIVECAPTION 27
#endif
#ifndef COLOR_GRADIENTINACTIVECAPTION
#define COLOR_GRADIENTINACTIVECAPTION 28
#endif

// already defined when compiled with WINVER >= 0x0600
#ifndef SPI_GETFLATMENU
#define SPI_GETFLATMENU 0x1022
#endif
#ifndef CS_DROPSHADOW
#define CS_DROPSHADOW 0x00020000
#endif
#ifndef CLEARTYPE_QUALITY
#define CLEARTYPE_QUALITY 5
#endif

#ifdef VSN_PLATFORM_WINCE
#ifndef LR_DEFAULTSIZE
#define LR_DEFAULTSIZE 0
#endif
#ifndef LR_SHARED
#define LR_SHARED 0
#endif
#endif // VSN_PLATFORM_WINCE

#endif // __VSN_WINDOWS_H
