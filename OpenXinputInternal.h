/* Copyright (C) Nemirtingas
 * This file is part of the OpenXinput project.
 *
 * OpenXinput project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXinput project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXinput project.  If not, see <https://www.gnu.org/licenses/>
 */

#pragma once

#ifdef OPENXINPUT_STATIC_GUIDS
    // Build guids, don't need to link against other dll
    #define INITGUID
#endif

#define VC_EXTRALEAN
#define NOMINMAX

#include "OpenXinput.h"
#include <strsafe.h>
#include <SetupAPI.h>

///////////////////////////////////////
// api-ms-win-core-quirks-l1-1-0
extern "C" {
BOOL WINAPI QuirkIsEnabled(ULONG quirk);
}

///////////////////////////////////////
// api-ms-win-devices-query-l1-1-0
#include <devpropdef.h>

typedef struct _DEV_QUERY_RESULT_ACTION_DATA
{
    DWORD field_0;
    PVOID field_4;
    PVOID field_8;
} DEV_QUERY_RESULT_ACTION_DATA, * PDEV_QUERY_RESULT_ACTION_DATA;

typedef HANDLE HDEVQUERY;

extern "C" {
HRESULT WINAPI DevCreateObjectQuery(DWORD a, DWORD b, DWORD c, PDEVPROPKEY PropKey, DWORD e, PVOID f, void(CALLBACK* ObjectQueryCallback)(HDEVQUERY, PVOID, PDEV_QUERY_RESULT_ACTION_DATA), PVOID user_param, HDEVQUERY* pQuery);
void WINAPI DevCloseObjectQuery(HDEVQUERY h);
}

///////////////////////////////////////
///////////////////////////////////////

#include "DEVOBJ/DEVOBJ.h"

DECLARE_INTERFACE_(IXInputDevice, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)   (THIS_ _In_ REFIID, _Outptr_ LPVOID*) PURE;
    STDMETHOD_(ULONG, AddRef)    (THIS) PURE;
    STDMETHOD_(ULONG, Release)   (THIS) PURE;

    // IXInputDevice methods
    STDMETHOD_(ULONG, CreateFileW)(THIS_ LPCWSTR DevicePath, DWORD dwDesiredAccess, DWORD dwSharedMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, LPHANDLE lpHandle) PURE;
};

DECLARE_INTERFACE_(IInputHostClient, IUnknown)
{
    // IUnknown methods
    STDMETHOD(QueryInterface)   (THIS_ _In_ REFIID, _Outptr_ LPVOID*) PURE;
    STDMETHOD_(ULONG, AddRef)    (THIS) PURE;
    STDMETHOD_(ULONG, Release)   (THIS) PURE;

    // IInputHostClient methods
    STDMETHOD_(ULONG, unk0)(THIS) PURE;
    STDMETHOD_(ULONG, unk1)(THIS) PURE;
    STDMETHOD_(ULONG, unk2)(THIS_ DWORD) PURE;
};

#define DEVICE_STATUS_ACTIVE 1
#define DEVICE_STATUS_BUS_ACTIVE 2

typedef HRESULT(WINAPI DllGetClassObject_t)(const GUID*, const GUID*, LPVOID*);

#define DEFINE_HIDDEN_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        static const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }

DEFINE_HIDDEN_GUID(static_XINPUT_GUID_DEVCLASS_MEDIA, 0x4d36e96c, 0xe325, 0x11ce, 0x0b, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
#define XINPUT_GUID_DEVCLASS_MEDIA static_XINPUT_GUID_DEVCLASS_MEDIA

#ifdef OPENXINPUT_STATIC_GUIDS
    DEFINE_HIDDEN_GUID(static_XINPUT_IID_IClassFactory            , 0x00000001, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
    DEFINE_HIDDEN_GUID(static_XINPUT_IID_IKsPropertySet           , 0x31efac30, 0x515c, 0x11d0, 0xa9, 0xaa, 0x00, 0xaa, 0x00, 0x61, 0xbe, 0x93);

    #define XINPUT_IID_IClassFactory             static_XINPUT_IID_IClassFactory
    #define XINPUT_IID_IKsPropertySet            static_XINPUT_IID_IKsPropertySet
#else
    #define XINPUT_IID_IClassFactory             IID_IClassFactory
    #define XINPUT_IID_IKsPropertySet            IID_IKsPropertySet
#endif