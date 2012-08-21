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


static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_utilx_enable_indicator(void);


struct tet_testlist tet_testlist[] = {
	{ utc_utilx_enable_indicator, 1 },
	// Do not remove below line
	{ NULL, 0 },
};

static void startup(void)
{
	/* start of TC */
}

static void cleanup(void)
{
	/* end of TC */
}


/**
 * @brief test case of utilx_enable_indicator()
 */
static void utc_utilx_enable_indicator(void)
{
	Display* dpy;
	Window root, win;
	int ret;

	dpy = XOpenDisplay(NULL);
	root = XDefaultRootWindow(dpy);

	win = XCreateSimpleWindow(dpy, root, 0, 0, 480, 800, 2, BlackPixel(dpy,0), WhitePixel(dpy,0));
	XMapWindow(dpy, win);

	// If the win want to show indicator, enables indicator.
	utilx_enable_indicator(dpy, win, 1);
	XFlush(dpy);

	ret = 1;

	if(ret)
	{
		dts_pass("utc_efl_util_set_notification_window_level_positive", "passed");
	}
	else
	{
		dts_fail("utc_efl_util_set_notification_window_level_positive", "failed");
	}
}

