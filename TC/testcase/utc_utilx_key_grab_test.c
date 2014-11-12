/*
 * Copyright (c) 2012 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <tet_api.h>
#include <X11/Xlib.h>
#include <Ecore_X.h>
#include <utilX.h>
#include <Ecore_Evas.h>
#include <sys/types.h>
#include <X11/X.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_utilx_grab_key_excl_p(void);
static void utc_utilx_grab_key_top_p(void);
static void utc_utilx_grab_key_share_p(void);
static void utc_utilx_grab_key_excl_n(void);
static void utc_utilx_grab_key_top_n(void);
static void utc_utilx_grab_key_share_n(void);
static void utc_utilx_ungrab_key_p(void);
static void utc_utilx_ungrab_key_n(void);

struct tet_testlist tet_testlist[] = {
	{ utc_utilx_grab_key_excl_p, 1 },
	{ utc_utilx_grab_key_top_p, 1 },
	{ utc_utilx_grab_key_share_p, 1 },
	{ utc_utilx_grab_key_excl_n, 1 },
	{ utc_utilx_grab_key_top_n, 1 },
	{ utc_utilx_grab_key_share_n, 1 },
	{ utc_utilx_ungrab_key_p, 1 },
	{ utc_utilx_ungrab_key_n, 1 },
	// Do not remove below line
	{ NULL, 0 }
};

Ecore_Evas *ee;
Ecore_X_Display *disp;
Ecore_X_Window win;

static void startup(void)
{
	/* start of TC */
	if(!ecore_init()){
		dts_fail("utilx_grab_key", "failed ecore_init");
	}
	if(!ecore_evas_init()){
		dts_fail("utilx_grab_key", "failed ecore_evas_init");
	}

	ee = ecore_evas_software_x11_new(NULL, 0, 0, 0, 720, 1280);
	if(!ee){
		dts_fail("utilx_grab_key", "failed to make window");
	}
	ecore_evas_title_set(ee, "Ecore_Evas Template");
	ecore_evas_borderless_set(ee, 0);
	ecore_evas_show(ee);

	disp = ecore_x_display_get();
	if(!disp){
		dts_fail("utilx_grab_key", "failed to get display");
	}

	win = ecore_evas_software_x11_window_get(ee);
	if(!win){
		dts_fail("utilx_grab_key", "failed to get ecore_x_window");
	}
}

static void cleanup(void)
{
	/* end of TC */
	ecore_evas_shutdown();
	ecore_shutdown();
}


/**
 * @brief test case of utilx_grab_key() / utilx_ungrab_key()
 */

static void utc_utilx_grab_key_excl_p(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(disp, win, KEY_MEDIA, EXCLUSIVE_GRAB);
	if( grab_result == 0 )
	{
		dts_pass("utilx_grab_key", "passed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_MEDIA);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");
	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
	}
}

static void utc_utilx_grab_key_top_p(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(disp, win, KEY_STOPCD, TOP_POSITION_GRAB);
	if( grab_result == 0 )
	{
		dts_pass("utilx_grab_key", "passed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");

	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
	}
}

static void utc_utilx_grab_key_share_p(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(disp, win, KEY_STOPCD, SHARED_GRAB);
	if( grab_result == 0 )
	{
		dts_pass("utilx_grab_key", "passed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");
	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
	}
}

static void utc_utilx_grab_key_excl_n(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(NULL, win, KEY_STOPCD, EXCLUSIVE_GRAB);
	if( grab_result != 0 )
	{
		dts_pass("utilx_grab_key", "passed");
	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");

	}
}

static void utc_utilx_grab_key_top_n(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(NULL, win, KEY_STOPCD, TOP_POSITION_GRAB);
	if( grab_result != 0 )
	{
		dts_pass("utilx_grab_key", "passed");
	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");

	}
}

static void utc_utilx_grab_key_share_n(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(NULL, win, KEY_STOPCD, SHARED_GRAB);
	if( grab_result != 0 )
	{
		dts_pass("utilx_grab_key", "passed");
	}
	else
	{
		dts_fail("utilx_grab_key", "failed");
		ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
		if( ungrab_result != 0)
			dts_fail("utilx_grab_key", "ungrab failed");

	}
}

static void utc_utilx_ungrab_key_p(void)
{
	int grab_result;
	int ungrab_result;

	grab_result = utilx_grab_key(disp, win, KEY_STOPCD, SHARED_GRAB);
	if( grab_result != 0 ){
		dts_fail("utilx_ungrab_key", "failed to grab the key");
	}

	ungrab_result = utilx_ungrab_key(disp, win, KEY_STOPCD);
	if(ungrab_result == 0)
	{
		dts_pass("utilx_ungrab_key", "passed");
	}
	else
	{
		dts_fail("utilx_ungrab_key", "failed");
	}
}

static void utc_utilx_ungrab_key_n(void)
{
	int grab_result;
	int ungrab_result;

	ungrab_result = utilx_ungrab_key(NULL, win, KEY_STOPCD);
	if(ungrab_result != 0)
	{
		dts_pass("utilx_ungrab_key", "passed");
	}
	else
	{
		dts_fail("utilx_ungrab_key", "failed");
	}
}
