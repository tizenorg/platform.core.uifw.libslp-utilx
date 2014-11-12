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

static void utc_utilx_screen_shot_test_positive_1(void);
static void utc_utilx_screen_shot_test_positive_2(void);
static void utc_utilx_screen_shot_test_positive_3(void);
static void utc_utilx_screen_shot_test_negative_1(void);
static void utc_utilx_screen_shot_test_negative_2(void);
static void utc_utilx_screen_shot_test_negative_3(void);

struct tet_testlist tet_testlist[] = {
	{ utc_utilx_screen_shot_test_positive_1, 1 },
	{ utc_utilx_screen_shot_test_positive_2, 1 },
	{ utc_utilx_screen_shot_test_positive_3, 1 },
	{ utc_utilx_screen_shot_test_negative_1, 1 },
	{ utc_utilx_screen_shot_test_negative_2, 1 },
	{ utc_utilx_screen_shot_test_negative_3, 1 },
	// Do not remove below line
	{ NULL, 0 },
};

Display *dpy;
int width, height;
void *dump;

static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
}

static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
}

/**
 * @brief test case of utc_utilx_screen_shot_test_positive_1()
 */
static void utc_utilx_screen_shot_test_positive_1(void)
{
	dpy = XOpenDisplay (NULL);

	dump = utilx_create_screen_shot (dpy, 720, 1280);

	dts_pass ("utc_utilx_screen_shot_test_positive_1", "passed");

    utilx_release_screen_shot ();

	XCloseDisplay(dpy);
}


/**
 * @brief test case of utc_utilx_screen_shot_test_positive_2()
 */
static void utc_utilx_screen_shot_test_positive_2(void)
{
	dpy = XOpenDisplay (NULL);

	dump = utilx_create_screen_shot (dpy, 400, 400);

	dts_pass ("utc_utilx_screen_shot_test_positive_2", "passed");

    utilx_release_screen_shot ();

	XCloseDisplay(dpy);
}


/**
 * @brief test case of utc_utilx_screen_shot_test_positive_3()
 */
static void utc_utilx_screen_shot_test_positive_3(void)
{
	dpy = XOpenDisplay (NULL);

	dump = utilx_create_screen_shot (dpy, 1280, 720);

	dts_pass ("utc_utilx_screen_shot_test_positive_3", "passed");

    utilx_release_screen_shot ();

	XCloseDisplay(dpy);
}

/**
 * @brief test case of utc_utilx_screen_shot_test_negative_1()
 */
static void utc_utilx_screen_shot_test_negative_1(void)
{
	dump = utilx_create_screen_shot (NULL, 720, 720);

    if (dump == NULL)
		dts_pass ("utc_utilx_screen_shot_test_negative_1", "passed");
	else
		dts_fail ("utc_utilx_screen_shot_test_negative_1", "failed");
}


/**
 * @brief test case of utc_utilx_screen_shot_test_negative_2()
 */
static void utc_utilx_screen_shot_test_negative_2(void)
{
	dpy = XOpenDisplay (NULL);

	dump = utilx_create_screen_shot (dpy, 0, 720);

    if (dump == NULL)
		dts_pass ("utc_utilx_screen_shot_test_negative_2", "passed");
	else
		dts_fail ("utc_utilx_screen_shot_test_negative_2", "failed");

	XCloseDisplay(dpy);
}


/**
 * @brief test case of utc_utilx_screen_shot_test_negative_3()
 */
static void utc_utilx_screen_shot_test_negative_3(void)
{
	dpy = XOpenDisplay (NULL);

	dump = utilx_create_screen_shot (dpy, 720, 0);

    if (dump == NULL)
		dts_pass ("utc_utilx_screen_shot_test_negative_3", "passed");
	else
		dts_fail ("utc_utilx_screen_shot_test_negative_3", "failed");

	XCloseDisplay(dpy);
}
