/*
 * Copyright (C) 2011 Dmitry A.Steklenev
 *
 * $Id: pm_debuglog.cpp,v 1.1 2011/09/19 08:41:17 glass Exp $
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "pm_debuglog.h"

void
debuglog( const char* fmt, ... )
{
  va_list va;
  PTIB    ptib;
  PPIB    ppib;
  char    buffer[2048];
  int     size;
  ULONG   done;

  DosGetInfoBlocks( &ptib, &ppib );
  snprintf( buffer, sizeof( buffer ), "%08d %04X:%04d ",
            clock(), ppib->pib_ulpid, ptib->tib_ptib2->tib2_ultid );

  size = strlen( buffer );

  va_start( va, fmt );
  vsnprintf( buffer + size, sizeof( buffer ) - size, fmt, va );
  va_end( va );
  DosWrite( 2, buffer, strlen( buffer ), &done );
}

void
debugmsg( const char* prefix, HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  const char* pszMsg;
  CHAR szBuffer[32];

  switch( msg ) {
    case WM_NULL:               pszMsg = "WM_NULL";               break;
    case WM_CREATE:             pszMsg = "WM_CREATE";             break;
    case WM_DESTROY:            pszMsg = "WM_DESTROY";            break;
    case WM_ENABLE:             pszMsg = "WM_ENABLE";             break;
    case WM_SHOW:               pszMsg = "WM_SHOW";               break;
    case WM_MOVE:               pszMsg = "WM_MOVE";               break;
    case WM_SIZE:               pszMsg = "WM_SIZE";               break;
    case WM_ADJUSTWINDOWPOS:    pszMsg = "WM_ADJUSTWINDOWPOS";    break;
    case WM_CALCVALIDRECTS:     pszMsg = "WM_CALCVALIDRECTS";     break;
    case WM_SETWINDOWPARAMS:    pszMsg = "WM_SETWINDOWPARAMS";    break;
    case WM_QUERYWINDOWPARAMS:  pszMsg = "WM_QUERYWINDOWPARAMS";  break;
    case WM_HITTEST:            pszMsg = "WM_HITTEST";            break;
    case WM_ACTIVATE:           pszMsg = "WM_ACTIVATE";           break;
    case WM_SETFOCUS:           pszMsg = "WM_SETFOCUS";           break;
    case WM_SETSELECTION:       pszMsg = "WM_SETSELECTION";       break;
    case WM_PPAINT:             pszMsg = "WM_PPAINT";             break;
    case WM_PSETFOCUS:          pszMsg = "WM_PSETFOCUS";          break;
    case WM_PSYSCOLORCHANGE:    pszMsg = "WM_PSYSCOLORCHANGE";    break;
    case WM_PSIZE:              pszMsg = "WM_PSIZE";              break;
    case WM_PACTIVATE:          pszMsg = "WM_PACTIVATE";          break;
    case WM_PCONTROL:           pszMsg = "WM_PCONTROL";           break;
    case WM_COMMAND:            pszMsg = "WM_COMMAND";            break;
    case WM_SYSCOMMAND:         pszMsg = "WM_SYSCOMMAND";         break;
    case WM_HELP:               pszMsg = "WM_HELP";               break;
    case WM_PAINT:              pszMsg = "WM_PAINT";              break;
    case WM_TIMER:              pszMsg = "WM_TIMER";              break;
    case WM_SEM1:               pszMsg = "WM_SEM1";               break;
    case WM_SEM2:               pszMsg = "WM_SEM2";               break;
    case WM_SEM3:               pszMsg = "WM_SEM3";               break;
    case WM_SEM4:               pszMsg = "WM_SEM4";               break;
    case WM_CLOSE:              pszMsg = "WM_CLOSE";              break;
    case WM_QUIT:               pszMsg = "WM_QUIT";               break;
    case WM_SYSCOLORCHANGE:     pszMsg = "WM_SYSCOLORCHANGE";     break;
    case WM_SYSVALUECHANGED:    pszMsg = "WM_SYSVALUECHANGED";    break;
    case WM_APPTERMINATENOTIFY: pszMsg = "WM_APPTERMINATENOTIFY"; break;
    case WM_PRESPARAMCHANGED:   pszMsg = "WM_PRESPARAMCHANGED";   break;
    case WM_CONTROL:            pszMsg = "WM_CONTROL";            break;
    case WM_VSCROLL:            pszMsg = "WM_VSCROLL";            break;
    case WM_HSCROLL:            pszMsg = "WM_HSCROLL";            break;
    case WM_INITMENU:           pszMsg = "WM_INITMENU";           break;
    case WM_MENUSELECT:         pszMsg = "WM_MENUSELECT";         break;
    case WM_MENUEND:            pszMsg = "WM_MENUEND";            break;
    case WM_DRAWITEM:           pszMsg = "WM_DRAWITEM";           break;
    case WM_MEASUREITEM:        pszMsg = "WM_MEASUREITEM";        break;
    case 0x00000039:            pszMsg = "WM_CONTROLHEAP";        break;
    case WM_CONTROLPOINTER:     pszMsg = "WM_CONTROLPOINTER";     break;
    case WM_QUERYDLGCODE:       pszMsg = "WM_QUERYDLGCODE";       break;
    case WM_INITDLG:            pszMsg = "WM_INITDLG";            break;
    case WM_SUBSTITUTESTRING:   pszMsg = "WM_SUBSTITUTESTRING";   break;
    case WM_MATCHMNEMONIC:      pszMsg = "WM_MATCHMNEMONIC";      break;
    case WM_SAVEAPPLICATION:    pszMsg = "WM_SAVEAPPLICATION";    break;
    case WM_FLASHWINDOW:        pszMsg = "WM_FLASHWINDOW";        break;
    case WM_FORMATFRAME:        pszMsg = "WM_FORMATFRAME";        break;
    case WM_UPDATEFRAME:        pszMsg = "WM_UPDATEFRAME";        break;
    case WM_FOCUSCHANGE:        pszMsg = "WM_FOCUSCHANGE";        break;
    case WM_SETBORDERSIZE:      pszMsg = "WM_SETBORDERSIZE";      break;
    case WM_TRACKFRAME:         pszMsg = "WM_TRACKFRAME";         break;
    case WM_MINMAXFRAME:        pszMsg = "WM_MINMAXFRAME";        break;
    case WM_SETICON:            pszMsg = "WM_SETICON";            break;
    case WM_QUERYICON:          pszMsg = "WM_QUERYICON";          break;
    case WM_SETACCELTABLE:      pszMsg = "WM_SETACCELTABLE";      break;
    case WM_QUERYACCELTABLE:    pszMsg = "WM_QUERYACCELTABLE";    break;
    case WM_TRANSLATEACCEL:     pszMsg = "WM_TRANSLATEACCEL";     break;
    case WM_QUERYTRACKINFO:     pszMsg = "WM_QUERYTRACKINFO";     break;
    case WM_QUERYBORDERSIZE:    pszMsg = "WM_QUERYBORDERSIZE";    break;
    case WM_NEXTMENU:           pszMsg = "WM_NEXTMENU";           break;
    case WM_ERASEBACKGROUND:    pszMsg = "WM_ERASEBACKGROUND";    break;
    case WM_QUERYFRAMEINFO:     pszMsg = "WM_QUERYFRAMEINFO";     break;
    case WM_QUERYFOCUSCHAIN:    pszMsg = "WM_QUERYFOCUSCHAIN";    break;
    case WM_OWNERPOSCHANGE:     pszMsg = "WM_OWNERPOSCHANGE";     break;
    case WM_CALCFRAMERECT:      pszMsg = "WM_CALCFRAMERECT";      break;
    case WM_WINDOWPOSCHANGED:   pszMsg = "WM_WINDOWPOSCHANGED";   break;
    case WM_ADJUSTFRAMEPOS:     pszMsg = "WM_ADJUSTFRAMEPOS";     break;
    case WM_QUERYFRAMECTLCOUNT: pszMsg = "WM_QUERYFRAMECTLCOUNT"; break;
    case WM_VRNDISABLED:        pszMsg = "WM_VRNDISABLED";        break;
    case WM_VRNENABLED:         pszMsg = "WM_VRNENABLED";         break;
    case WM_MOUSEMOVE:          pszMsg = "WM_MOUSEMOVE";          break;
    case WM_BUTTON1DOWN:        pszMsg = "WM_BUTTON1DOWN";        break;
    case WM_BUTTON1UP:          pszMsg = "WM_BUTTON1UP";          break;
    case WM_BUTTON1DBLCLK:      pszMsg = "WM_BUTTON1DBLCLK";      break;
    case WM_BUTTON2DOWN:        pszMsg = "WM_BUTTON2DOWN";        break;
    case WM_BUTTON2UP:          pszMsg = "WM_BUTTON2UP";          break;
    case WM_BUTTON2DBLCLK:      pszMsg = "WM_BUTTON2DBLCLK";      break;
    case WM_BUTTON3DOWN:        pszMsg = "WM_BUTTON3DOWN";        break;
    case WM_BUTTON3UP:          pszMsg = "WM_BUTTON3UP";          break;
    case WM_BUTTON3DBLCLK:      pszMsg = "WM_BUTTON3DBLCLK";      break;
    case WM_CHAR:               pszMsg = "WM_CHAR";               break;

    default:
      snprintf( szBuffer, sizeof( szBuffer ), "%08X", msg );
      pszMsg = szBuffer;
      break;
  }

  debuglog( "%s: %08X %-22s %08X %08X\n", prefix, hwnd, pszMsg, mp1, mp2 );
}

