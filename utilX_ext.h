/*
 * libslp-utilx
 *
   Copyright (c) 2012 Samsung Electronics Co., Ltd All Rights Reserved

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 *
 */

#ifndef __SAMSUNG_LINUX_UTIL_X11_EXT_H__
#define __SAMSUNG_LINUX_UTIL_X11_EXT_H__

#include <sys/types.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STR_ATOM_SCRNCONF_STATUS "_SCRNCONF_STATUS"

typedef enum _Utilx_Scrnconf_Status
{
	UTILX_SCRNCONF_STATUS_NULL,
	UTILX_SCRNCONF_STATUS_CONNECT,
	UTILX_SCRNCONF_STATUS_ACTIVE
} Utilx_Scrnconf_Status;

typedef enum _Utilx_Scrnconf_Dispmode
{
	UTILX_SCRNCONF_DISPMODE_NULL,
	UTILX_SCRNCONF_DISPMODE_CLONE,
	UTILX_SCRNCONF_DISPMODE_EXTENDED
} Utilx_Scrnconf_Dispmode;

typedef enum _Utilx_Fb_Type
{
	UTILX_FB_TYPE_NONE,
	UTILX_FB_TYPE_UI,
	UTILX_FB_TYPE_OVERLAY,
} Utilx_Fb_Type;

typedef struct _UtilxScrnConf
{
	char *str_output;
	Utilx_Scrnconf_Status status;
	char *str_resolution;
	Utilx_Scrnconf_Dispmode dispmode;
} UtilxScrnConf;

UtilxScrnConf *utilx_scrnconf_allocate (void);
void utilx_scrnconf_free (UtilxScrnConf *scrnconf);
int utilx_scrnconf_get_info (Display *dpy, UtilxScrnConf *scrnconf);
int utilx_scrnconf_set_dispmode (Display *dpy, Utilx_Scrnconf_Dispmode dispmode);

void* utilx_create_video_screen_shot (Display* dpy, Window win, int width, int height);
void  utilx_set_fb_visible (Display* dpy, Utilx_Fb_Type fb_type, Bool visible);
Bool  utilx_get_fb_visible (Display* dpy, Utilx_Fb_Type fb_type);

#ifdef __cplusplus
}
#endif

#endif /* __SAMSUNG_LINUX_UTIL_X11_EXT_H__ */

