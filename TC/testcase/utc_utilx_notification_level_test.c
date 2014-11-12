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

static void utc_utilx_system_notification_level_test_positive_1(void);
static void utc_utilx_system_notification_level_test_positive_2(void);
static void utc_utilx_system_notification_level_test_positive_3(void);
static void utc_utilx_system_notification_level_test_positive_4(void);
static void utc_utilx_system_notification_level_test_negative_1(void);
static void utc_utilx_system_notification_level_test_negative_2(void);


struct tet_testlist tet_testlist[] = {
	{ utc_utilx_system_notification_level_test_positive_1, 1 },
	{ utc_utilx_system_notification_level_test_positive_2, 1 },
	{ utc_utilx_system_notification_level_test_positive_3, 1 },
	{ utc_utilx_system_notification_level_test_positive_4, 1 },
	{ utc_utilx_system_notification_level_test_negative_1, 1 },
	{ utc_utilx_system_notification_level_test_negative_2, 1 },
	// Do not remove below line
	{ NULL, 0 },
};

Display* dpy;
Window root, win;

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");

	dpy = XOpenDisplay(NULL);
	root = XDefaultRootWindow(dpy);

	win = XCreateSimpleWindow(dpy, root, 0, 0, 480, 800, 2, BlackPixel(dpy,0), WhitePixel(dpy,0));
	XMapWindow(dpy, win);
}

static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");

	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

/**
 * @brief test case of utc_utilx_system_notification_level_test_positive_1()
 */
static void utc_utilx_system_notification_level_test_positive_1(void)
{
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_HIGH;

	utilx_set_system_notification_level(dpy, win, UTILX_NOTIFICATION_LEVEL_LOW);
	XFlush(dpy);

	level = utilx_get_system_notification_level(dpy, win);

	if (level == UTILX_NOTIFICATION_LEVEL_LOW)
	{
		dts_pass("utc_utilx_system_notification_level_test_positive_1", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_positive_1", "failed");
	}
}


/**
 * @brief test case of utc_utilx_system_notification_level_test_positive_2()
 */
static void utc_utilx_system_notification_level_test_positive_2(void)
{
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_HIGH;

	utilx_set_system_notification_level(dpy, win, UTILX_NOTIFICATION_LEVEL_NORMAL);
	XFlush(dpy);

	level = utilx_get_system_notification_level(dpy, win);

	if (level == UTILX_NOTIFICATION_LEVEL_NORMAL)
	{
		dts_pass("utc_utilx_system_notification_level_test_positive_2", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_positive_2", "failed");
	}
}


/**
 * @brief test case of utc_utilx_system_notification_level_test_positive_3()
 */
static void utc_utilx_system_notification_level_test_positive_3(void)
{
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_NORMAL;

	utilx_set_system_notification_level(dpy, win, UTILX_NOTIFICATION_LEVEL_HIGH);
	XFlush(dpy);

	level = utilx_get_system_notification_level(dpy, win);

	if (level == UTILX_NOTIFICATION_LEVEL_HIGH)
	{
		dts_pass("utc_utilx_system_notification_level_test_positive_3", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_positive_3", "failed");
	}
}


/**
 * @brief test case of utc_utilx_system_notification_level_test_positive_4()
 */
static void utc_utilx_system_notification_level_test_positive_4(void)
{
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_HIGH;

	utilx_set_system_notification_level(dpy, win, 100);
	XFlush(dpy);

	level = utilx_get_system_notification_level(dpy, win);

	if (level == UTILX_NOTIFICATION_LEVEL_LOW)
	{
		dts_pass("utc_utilx_system_notification_level_test_positive_4", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_positive_4", "failed");
	}
}


/**
 * @brief test case of utc_utilx_system_notification_level_test_negative_1()
 */
static void utc_utilx_system_notification_level_test_negative_1(void)
{
	Ecore_X_Display *dpy2 = NULL;
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_HIGH;

	// invalid display parameter
	utilx_set_system_notification_level(dpy2, win, UTILX_NOTIFICATION_LEVEL_NORMAL);
	XFlush(dpy);

	level = utilx_get_system_notification_level(dpy, win);

	if (level == UTILX_NOTIFICATION_LEVEL_LOW)
	{
		dts_pass("utc_utilx_system_notification_level_test_negative_1", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_negative_1", "failed");
	}
}


/**
 * @brief test case of utc_utilx_system_notification_level_test_negative_2()
 */
static void utc_utilx_system_notification_level_test_negative_2(void)
{
	Ecore_X_Display *dpy2 = NULL;
	Utilx_Notification_Level level = UTILX_NOTIFICATION_LEVEL_HIGH;

	utilx_set_system_notification_level(dpy, win, UTILX_NOTIFICATION_LEVEL_NORMAL);
	XFlush(dpy);

	// invalid display parameter
	level = utilx_get_system_notification_level(dpy2, win);

	if (level == UTILX_NOTIFICATION_LEVEL_LOW)
	{
		dts_pass("utc_utilx_system_notification_level_test_negative_2", "passed");
	}
	else
	{
		dts_fail("utc_utilx_system_notification_level_test_negative_2", "failed");
	}
}

