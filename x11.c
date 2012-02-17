/*
 * libslp-utilx
 *
   Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved 

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "utilX.h"
#include "util_x11.h"


#define UTILX_DEBUG 0
#if UTILX_DEBUG
#define UTILX_TRACE  printf
#else
#define UTILX_TRACE(...)
#endif

static Atom _atom_grab_key = None;
static Atom _atom_grab_excl_win = None;
static Atom _atom_grab_or_excl_win = None;

static Atom _atom_notification_level = None;
static Atom _atom_indicator_visible_state = None;

static Atom _atom_comp_effect_state = None;
static Atom _atom_comp_fake_launch = None;
static Atom _atom_comp_fake_launch_image = None;

static Atom _atom_comp_window_effect_type = None;
static Atom _atom_comp_effect_default = None;
static Atom _atom_comp_effect_none = None;
static Atom _atom_comp_effect_custom0 = None;
static Atom _atom_comp_effect_custom1 = None;
static Atom _atom_comp_effect_custom2 = None;
static Atom _atom_comp_effect_custom3 = None;
static Atom _atom_comp_effect_custom4 = None;
static Atom _atom_comp_effect_custom5 = None;
static Atom _atom_comp_effect_custom6 = None;
static Atom _atom_comp_effect_custom7 = None;
static Atom _atom_comp_effect_custom8 = None;
static Atom _atom_comp_effect_custom9 = None;

static Atom _atom_window_opaque = None;

static Atom _atom_screen_capture_disable = None;

static Atom _atom_comp_capture_effect = None;

const unsigned long maxlen = 1024l;

static void _utilx_set_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int num);
static int _utilx_get_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int len);

static void _utilx_effect_atom_check( Display* dpy );
static Atom _utilx_convert_style_to_atom( Display* dpy, Utilx_Effect_Style style );
static Utilx_Effect_Style _utilx_convert_atom_to_style( Display* dpy, Atom style );

API void utilx_set_system_notification_level (Display* dpy, Window win, Utilx_Notification_Level level)
{
	UTILX_TRACE ("[UTILX] utilx_set_system_notification_level... win = %x, level = %d\n", win, level);

	int noti_level;

	if (dpy == NULL)
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}

	switch (level)
	{
		case UTILX_NOTIFICATION_LEVEL_LOW:
			noti_level = 50;
			break;

		case UTILX_NOTIFICATION_LEVEL_NORMAL:
			noti_level = 100;
			break;

		case UTILX_NOTIFICATION_LEVEL_HIGH:
			noti_level = 150;
			break;

		default:
			noti_level = 50;
			break;
	}

	if (!_atom_notification_level)
	{
		_atom_notification_level = XInternAtom (dpy, "_E_ILLUME_NOTIFICATION_LEVEL", False);
		if (!_atom_notification_level)
		{
			fprintf (stderr, "[UTILX] Error.. Cannot create _E_ILLUME_NOTIFICATION_LEVEL atom.. %s (%d)\n", __func__, __LINE__);
			return;
		}
	}

	_utilx_set_window_property (dpy, win, _atom_notification_level, XA_CARDINAL,
			(unsigned int *)&noti_level, 1);
}


API Utilx_Notification_Level utilx_get_system_notification_level (Display* dpy, Window win)
{
	UTILX_TRACE ("[UTILX] utilx_get_system_notification_level... win = %x\n", win);

	Utilx_Notification_Level noti_level;
	unsigned int level;
	int ret;

	noti_level = UTILX_NOTIFICATION_LEVEL_LOW;

	if (dpy == NULL)
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		goto error;
	}

	if (!_atom_notification_level)
	{
		_atom_notification_level = XInternAtom (dpy, "_E_ILLUME_NOTIFICATION_LEVEL", False);
		if (!_atom_notification_level)
		{
			fprintf (stderr, "[UTILX] Error.. Cannot create _E_ILLUME_NOTIFICATION_LEVEL atom.. %s (%d)\n", __func__, __LINE__);
			goto error;
		}
	}

	ret = _utilx_get_window_property (dpy, win, _atom_notification_level, XA_CARDINAL,
			(unsigned int *)&level, 1);

	if (ret > 0)
	{
		switch (level)
		{
			case 50:
				noti_level = UTILX_NOTIFICATION_LEVEL_LOW;
				break;

			case 100:
				noti_level = UTILX_NOTIFICATION_LEVEL_NORMAL;
				break;

			case 150:
				noti_level = UTILX_NOTIFICATION_LEVEL_HIGH;
				break;

			default:
				noti_level = UTILX_NOTIFICATION_LEVEL_LOW;
				break;
		}
	}
	else
	{
		noti_level = UTILX_NOTIFICATION_LEVEL_LOW;
	}

error:
	return noti_level;
}


API void utilx_enable_indicator (Display* dpy, Window win, int enable)
{
	UTILX_TRACE ("[UTILX] utilx_indicator_set_visible_state... win = %x, show_state = %d\n", win, enable);

	if (dpy == NULL)
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}

	if (!_atom_indicator_visible_state)
	{
		_atom_indicator_visible_state = XInternAtom (dpy, "_E_ILLUME_INDICATOR_STATE", False);
		if (!_atom_indicator_visible_state)
		{
			fprintf (stderr, "[UTILX] Error.. Cannot create _E_ILLUME_INDICATOR_STATE atom.. %s (%d)\n", __func__, __LINE__);
			return;
		}
	}

	_utilx_set_window_property (dpy, win, _atom_indicator_visible_state, XA_CARDINAL,
			(unsigned int *)&enable, 1);
}


API int utilx_get_indicator_state (Display* dpy, Window win)
{
	UTILX_TRACE ("[UTILX] utilx_indicator_set_visible_state... win = %x, show_state = %d\n", win, enable);

	int ret;
	int state;

	if (dpy == NULL)
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return -1;
	}

	if (!_atom_indicator_visible_state)
	{
		_atom_indicator_visible_state = XInternAtom (dpy, "_E_ILLUME_INDICATOR_STATE", False);
		if (!_atom_indicator_visible_state)
		{
			fprintf (stderr, "[UTILX] Error.. Cannot create _E_ILLUME_INDICATOR_STATE atom.. %s (%d)\n", __func__, __LINE__);
			return -1;
		}
	}

	ret = _utilx_get_window_property (dpy, win, _atom_indicator_visible_state, XA_CARDINAL,
			(unsigned int *)&state, 1);

	if (ret > 0)
		return state;
	else
		return -1;
}

static void
_utilx_set_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int num)
{
	XChangeProperty (dpy, win, atom, type, 32, PropModeReplace, (unsigned char *)val, num);
	XSync(dpy, 0 );
}


static int
_utilx_get_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int len)
{
	unsigned char* prop_ret;
	Atom type_ret;
	unsigned long bytes_after, num_ret;
	int format_ret;
	unsigned int i;
	int num;

	prop_ret = NULL;
	if (XGetWindowProperty(dpy, win, atom, 0, 0x7fffffff, False,
				type, &type_ret, &format_ret, &num_ret,
				&bytes_after, &prop_ret) != Success)
	{
		return -1;
	}

	if (type_ret != type || format_ret != 32)
	{
		num = -1;
	}
	else if (num_ret == 0 || !prop_ret)
	{
		num = 0;
	}
	else
	{
		if (num_ret < len)
		len = num_ret;
		for (i = 0; i < len; i++)
		{
			val[i] = ((unsigned long *)prop_ret)[i];
		}
		num = len;
	}

	if (prop_ret)
		XFree(prop_ret);

	return num;

}


static unsigned long _get_list_of_grabbed_key (Display *disp, Window win, int **key_list)
{
	Atom ret_type;
	int ret_format;
	unsigned long nr_item;
	unsigned long sz_remains_data;

	if (XGetWindowProperty(disp, win,
		_atom_grab_key, 0, 0x7fffffff, False, XA_CARDINAL,
		&ret_type, &ret_format, &nr_item,
		&sz_remains_data, (unsigned char**)key_list) != Success)
	{
		nr_item = 0;
	}

//	fprintf(stderr, "[31m%d - %lu[0m\n", ret_format, nr_item);

	return nr_item;
}


static void _free_list_of_grabbed_key (int *key_list)
{
	if (key_list) {
		XFree(key_list);
	}
}


static void _free_new_list_of_grabbed_key (int *new_key_list)
{
	if (new_key_list) {
		free(new_key_list);
	}
}


static int _search_grabbed_key (int *key_list, int key, unsigned long cnt)
{
	register int i;

	for (i = cnt - 1; i >= 0; i --) {
		if (key_list[i] == key) break;
	}

	return i;
}


static int *_del_grabbed_key (int *key_list, int i, unsigned long *cnt)
{
	int *new_key_list = NULL;

	// Only one element is exists in the list of grabbed key
	(*cnt) --;

	if (*cnt == 0) return NULL;

	// Shrink the buffer
	new_key_list = malloc((*cnt) * sizeof(int));
	if (new_key_list == NULL) {
		perror(__func__);
		return NULL;
	}

	// copy head
	if (i > 0) {
		memcpy(new_key_list, key_list, sizeof(int) * i);
	}

	// copy tail
	if ((*cnt) - i > 0) {
		memcpy(new_key_list + i,
			key_list + i + 1,
			sizeof(int) * ((*cnt) - i)
		);
	}
	return new_key_list;
}


static void _set_exclusive_grab_info_to_root (Display *disp, int keycode, Window win, int grab_mode)
{
	int i;
	int *key_list = NULL;

	Atom ret_type;
	int ret_format;
	unsigned long nr_item;
	unsigned long sz_remains_data;
	Window ex_grabwin;

	if( grab_mode == EXCLUSIVE_GRAB )
	{
		if( _atom_grab_excl_win == None )
			_atom_grab_excl_win = XInternAtom(disp, STR_ATOM_GRAB_EXCL_WIN, False);
		ex_grabwin = _atom_grab_excl_win;
	}
	else if( grab_mode == OR_EXCLUSIVE_GRAB )
	{
		if( _atom_grab_or_excl_win == None )
			_atom_grab_or_excl_win = XInternAtom(disp, STR_ATOM_GRAB_OR_EXCL_WIN, False);
		ex_grabwin = _atom_grab_or_excl_win;
	}
	else
		return;

	if (XGetWindowProperty(disp, DefaultRootWindow(disp),
		ex_grabwin, 0, 0x7fffffff, False, XA_CARDINAL,
		&ret_type, &ret_format, &nr_item,
		&sz_remains_data, (unsigned char**)&key_list) != Success)
	{
		fprintf(stderr, "[utilX][%s] Fail to get root window property !\n", __FUNCTION__);
		goto out;
	}

#ifdef __DEBUG__
	printf("[%s] keycode = %d\n", __FUNCTION__, keycode);
#endif

	for( i=0 ; i < nr_item ; i++ )
	{
		if( key_list && (key_list[i] == keycode) )
			return;
	}

	XChangeProperty(disp, DefaultRootWindow(disp), ex_grabwin, XA_CARDINAL, 32,
	nr_item ? PropModeAppend : PropModeReplace, (unsigned char *)&keycode, 1);
	XSync(disp, False);

out:
	return;
}


static void _unset_exclusive_grab_info_to_root (Display *disp, int keycode, int grab_mode)
{
	int i;
	unsigned long cnt = 0;
	int *key_list = NULL;
	int *new_key_list = NULL;

	Atom ret_type;
	int ret_format;
	unsigned long nr_item;
	unsigned long sz_remains_data;
	Window ex_grabwin;

	if( grab_mode == EXCLUSIVE_GRAB )
	{
		if( _atom_grab_excl_win == None )
			_atom_grab_excl_win = XInternAtom(disp, STR_ATOM_GRAB_EXCL_WIN, False);
		ex_grabwin = _atom_grab_excl_win;
	}
	else if( grab_mode == OR_EXCLUSIVE_GRAB )
	{
		if( _atom_grab_or_excl_win == None )
			_atom_grab_or_excl_win = XInternAtom(disp, STR_ATOM_GRAB_OR_EXCL_WIN, False);
		ex_grabwin = _atom_grab_or_excl_win;
	}
	else
		return;

	if (XGetWindowProperty(disp, DefaultRootWindow(disp),
		ex_grabwin, 0, 0x7fffffff, False, XA_CARDINAL,
		&ret_type, &ret_format, &nr_item,
		&sz_remains_data, (unsigned char**)&key_list) != Success)
	{
		nr_item = 0;
	}

	if (nr_item == 0)
	{
		fprintf(stderr, "[32m[utilX][%s] keycode = %d[0m\n", __FUNCTION__, keycode);
		goto out;
	}

	for( i=0 ; i < nr_item ; i++ )
	{
		if( key_list[i] == keycode )//&& grab_mode == EXCLUSIVE_GRAB )
		{
			continue;
		}
		cnt++;
	}

#ifdef __DEBUG__
	fprintf(stderr, "[utilX][%s] cnt = %d, nr_item = %d\n", __FUNCTION__, cnt, nr_item);
#endif

	if( 0 < cnt )
	{
		new_key_list = malloc(sizeof(int)*cnt);
		cnt = 0;
	}
	else
		new_key_list = NULL;

	if( !new_key_list )
	{
		//fprintf(stderr, "[32m[utilX][%s] Fail to allocation memory for new_key_list ! [0m\n", __FUNCTION__);
		XDeleteProperty(disp, DefaultRootWindow(disp), ex_grabwin);
		XSync(disp, False);
		goto out;
	}

	for( i=0 ; i < nr_item ; i++ )
	{
		if( key_list[i] == keycode )//&& grab_mode == EXCLUSIVE_GRAB )
		{
			continue;
		}
		else
			new_key_list[cnt++] = key_list[i];
	}

	if (new_key_list) {
		XChangeProperty(disp, DefaultRootWindow(disp), ex_grabwin, XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *)new_key_list, cnt);
	}
	else {
		XDeleteProperty(disp, DefaultRootWindow(disp), ex_grabwin);
	}
	XSync(disp, False);

	if(new_key_list)
		free(new_key_list);

out:
	return;
}


static int _is_grabbed_key_exclusively (Display* disp, int keycode, int grab_mode)
{
	int i, result = 0;
	int *key_list = NULL;

	Atom ret_type;
	int ret_format;
	unsigned long nr_item;
	unsigned long sz_remains_data;
	Window ex_grabwin;

	if( grab_mode == EXCLUSIVE_GRAB )
	{
		if( _atom_grab_excl_win == None )
			_atom_grab_excl_win = XInternAtom(disp, STR_ATOM_GRAB_EXCL_WIN, False);
		ex_grabwin = _atom_grab_excl_win;
	}
	else if( grab_mode == OR_EXCLUSIVE_GRAB )
	{
		if( _atom_grab_or_excl_win == None )
			_atom_grab_or_excl_win = XInternAtom(disp, STR_ATOM_GRAB_OR_EXCL_WIN, False);
		ex_grabwin = _atom_grab_or_excl_win;
	}
	else
		return result;

	if (XGetWindowProperty(disp, DefaultRootWindow(disp),
		ex_grabwin, 0, 0x7fffffff, False, XA_CARDINAL,
		&ret_type, &ret_format, &nr_item,
		&sz_remains_data, (unsigned char**)&key_list) != Success)
	{
		fprintf(stderr, "[%s] Fail to get root window property !\n", __FUNCTION__);
		goto out;
	}

	for( i=0 ; i < nr_item ; i++ )
	{
		if( key_list[i] == keycode )
			return EXCLUSIVE_GRABBED_ALREADY;
	}

out:
	return result;
}

API int utilx_grab_key (Display* disp, Window win, const char* key, int grab_mode)
{
	unsigned long cnt;
	int *key_list = NULL;
	int i, result = 0;
	int keycode = 0;
	KeySym keysym;
	errno = EINVAL;

	if( NULL == disp )
	{
		fprintf(stderr, "[%s] Display is NULL\n", __FUNCTION__);
		return -1;
	}

	if (_atom_grab_key == None) {
		_atom_grab_key = XInternAtom(disp, STR_ATOM_GRAB_KEY, False);
	}

	if (!strncmp(key, "Keycode-", 8)) {
		keycode = atoi(key + 8);
	} else {
		keysym = XStringToKeysym(key);
		if (keysym == NoSymbol) goto out;
		keycode = XKeysymToKeycode(disp, XStringToKeysym(key));
	}
	if (keycode == 0) goto out;

	if( grab_mode == EXCLUSIVE_GRAB )
	{
		//Window grabWin;
		result = _is_grabbed_key_exclusively(disp, keycode, grab_mode);

#ifdef __DEBUG__
		printf("[%s] _is_grabbed_key_exclusively returns result = %d\n", __FUNCTION__, result);
#endif

		if( result )
		{
			fprintf(stderr, "[%s] keycode(%d) was already grabbed exclusively (grab_mode=0x%X) !\n", __FUNCTION__, keycode, grab_mode);
			goto out;
		}
	}
	else if( grab_mode == OR_EXCLUSIVE_GRAB )
	{
		result = _is_grabbed_key_exclusively(disp, keycode, grab_mode);

		if( result )
		{
			fprintf(stderr, "[%s] Keycode(%d) was already grabbed with overridable exclusive mode (grab_mode=0x%x)\n", __FUNCTION__, keycode, grab_mode);
			fprintf(stderr, "[%s] Now it will be overridden by a new window(0x%x) !\n", __FUNCTION__, win);
			utilx_ungrab_key(disp, win, key);
		}
	}

	keycode |= grab_mode;

	cnt = _get_list_of_grabbed_key(disp, win, &key_list);
	if (cnt > 0) {
		i = _search_grabbed_key(key_list, keycode, cnt);
		_free_list_of_grabbed_key(key_list);
		if ( i != -1 ) {
			if( grab_mode == OR_EXCLUSIVE_GRAB )
			{
				utilx_ungrab_key(disp, win, key);
			}
			else
			{
			fprintf(stderr, "Key is already grabbed\n");
			goto out;
			}
		}
	}

	XChangeProperty(disp, win, _atom_grab_key, XA_CARDINAL, 32,
			cnt ? PropModeAppend : PropModeReplace, (unsigned char *)&keycode, 1);
	XSync(disp, False);
	keycode = keycode & (~GRAB_MODE_MASK);
#ifdef __DEBUG__
	printf("[%s] keycode = %d\n", __FUNCTION__, keycode);
#endif

	if( EXCLUSIVE_GRAB == grab_mode || OR_EXCLUSIVE_GRAB == grab_mode )
		_set_exclusive_grab_info_to_root(disp, keycode, win, grab_mode);

	errno = 0;

out:

	return result;
}


API int utilx_ungrab_key (Display* disp, Window win, const char* key)
{
	int i;
	unsigned long cnt;
	int *key_list = NULL;
	int *new_key_list = NULL;
	long keycode = 0;
	KeySym keysym;
	int ret = -1;
	errno = EINVAL;

	if( NULL == disp )
	{
		fprintf(stderr, "[%s] Display is NULL\n", __FUNCTION__);
		return -1;
	}

	if (_atom_grab_key == None) {
		_atom_grab_key = XInternAtom(disp, STR_ATOM_GRAB_KEY, False);
	}

	if (!strncmp(key, "Keycode-", 8)) {
		keycode = atoi(key + 8);
	} else {
		keysym = XStringToKeysym(key);
		if (keysym == NoSymbol) goto out;
		keycode = XKeysymToKeycode(disp, XStringToKeysym(key));
	}
	if (keycode == 0) goto out;

	cnt = _get_list_of_grabbed_key(disp, win, &key_list);
	if (cnt == 0) goto out;

	//EXCLUSIVE mode
	i = _search_grabbed_key(key_list, keycode | EXCLUSIVE_GRAB, cnt);

	if ( i == -1)
	{
		//OR_EXCLUSIVE mode
		i = _search_grabbed_key(key_list, keycode | OR_EXCLUSIVE_GRAB, cnt);

		if ( i == -1)
		{
			//TOP_POSITION mode
			i = _search_grabbed_key(key_list, keycode | TOP_POSITION_GRAB, cnt);

			if (i == -1)
			{
				//SHARED mode
				i = _search_grabbed_key(key_list, keycode | SHARED_GRAB, cnt);

				if (i == -1)
				{
					_free_list_of_grabbed_key(key_list);
					goto out;
				}
			}
		}
		else
		{
			_unset_exclusive_grab_info_to_root(disp, keycode, OR_EXCLUSIVE_GRAB);
		}
	}
	else
	{
		_unset_exclusive_grab_info_to_root(disp, keycode, EXCLUSIVE_GRAB);
	}

	new_key_list = _del_grabbed_key(key_list, i, &cnt);
	_free_list_of_grabbed_key(key_list);

	if (new_key_list) {
		XChangeProperty(disp, win, _atom_grab_key, XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *)new_key_list, cnt);
	}
	else {
		XDeleteProperty(disp, win, _atom_grab_key);
	}
	XSync(disp, False);

	_free_new_list_of_grabbed_key(new_key_list);
	ret = 0;
	errno = 0;

out:

	return ret;
}

API Utilx_Key_Status utilx_get_key_status(Display* dpy, char *key_name)
{
	unsigned char keymap[32];
	static unsigned int masktable[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
	Utilx_Key_Status status = UTILX_KEY_STATUS_UNKNOWN;

	if( !strncmp(key_name, KEY_VOLUMEDOWN, LEN_KEY_VOLUMEDOWN) ||
		!strncmp(key_name, KEY_VOLUMEUP, LEN_KEY_VOLUMEUP) ||
		!strncmp(key_name, KEY_PAUSE, LEN_KEY_PAUSE) ||
		!strncmp(key_name, KEY_SEND, LEN_KEY_SEND) ||
		!strncmp(key_name, KEY_SELECT, LEN_KEY_VOLUMEDOWN) ||
		!strncmp(key_name, KEY_END, LEN_KEY_END) ||
		!strncmp(key_name, KEY_POWER, LEN_KEY_POWER) ||
		!strncmp(key_name, KEY_CAMERA, LEN_KEY_CAMERA) ||
		!strncmp(key_name, KEY_CONFIG, LEN_KEY_CONFIG) ||
		!strncmp(key_name, KEY_PLAYCD, LEN_KEY_PLAYCD) ||
		!strncmp(key_name, KEY_STOPCD, LEN_KEY_STOPCD) ||
		!strncmp(key_name, KEY_PAUSECD, LEN_KEY_PAUSECD) ||
		!strncmp(key_name, KEY_NEXTSONG, LEN_KEY_NEXTSONG) ||
		!strncmp(key_name, KEY_PREVIOUSSONG, LEN_KEY_PREVIOUSSONG) ||
		!strncmp(key_name, KEY_REWIND, LEN_KEY_REWIND) ||
		!strncmp(key_name, KEY_FASTFORWARD, LEN_KEY_FASTFORWARD) ||
		!strncmp(key_name, KEY_MEDIA, LEN_KEY_MEDIA) )
	{
		KeySym ks = XStringToKeysym(key_name);
		KeyCode kc = XKeysymToKeycode(dpy, ks);

		if( kc )
		{
			XQueryKeymap(dpy, (char *)keymap);
			if( keymap[kc >> 3] & masktable[kc & 7] )
				status = UTILX_KEY_STATUS_PRESSED;
			else
				status = UTILX_KEY_STATUS_RELEASED;
		}
	}

	return status;
}

API void utilx_set_window_effect_state(Display* dpy, Window win, int state)
{
	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}
	if( !_atom_comp_effect_state)
		_atom_comp_effect_state = XInternAtom(dpy, "_NET_CM_WINDOW_EFFECT_ENABLE",False);

	_utilx_set_window_property(dpy, win, _atom_comp_effect_state, XA_CARDINAL, (unsigned int *)&state, 1);

	XSync(dpy, 0 );
}

API int utilx_get_window_effect_state(Display* dpy, Window win)
{
	int state = 0;
	if( !_atom_comp_effect_state)
		_atom_comp_effect_state = XInternAtom(dpy, "_NET_CM_WINDOW_EFFECT_ENABLE",False);
	_utilx_get_window_property(dpy, win, _atom_comp_effect_state, XA_CARDINAL, (unsigned int *)&state, 1);
	return state;
}

static void
_utilx_string_set_window_property( Display *dpy, Window win, Atom atom, char *val, unsigned int num)
{
	XChangeProperty( dpy, win, atom, XA_STRING, 8, PropModeReplace, (unsigned char*)val, val ? strlen(val):0 );
}

API void utilx_set_fake_launch_img(Display* dpy, Window win, char *file_name)
{
	//UTILX_TRACE ("[UTILX] utilx_set_effect_state... win = %x, show_state = %d\n", win, enable);

	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}
	if( !_atom_comp_fake_launch_image)
		_atom_comp_fake_launch_image = XInternAtom(dpy, "_E_COMP_FAKE_LAUNCH_IMAGE",False);

	_utilx_string_set_window_property(dpy, win, _atom_comp_fake_launch_image, file_name, 1);
}

API void utilx_show_fake_effect( Display *dpy, Window win, char *fake_image_file )
{
	XEvent xev;

	_atom_comp_fake_launch = XInternAtom( dpy, "_E_COMP_FAKE_LAUNCH", False );

	if(  !_atom_comp_fake_launch )
	{
		fprintf( stderr, "XInternAtom(_E_COMP_FAKE_LAUNCH) failed.\n" );
		return;
	}

	utilx_set_fake_launch_img(dpy, win, fake_image_file);

	XSync(dpy, 0 );

	// send fake client message
	xev.xclient.type = ClientMessage;
	xev.xclient.display = dpy;
	xev.xclient.window = win;
	xev.xclient.message_type =  _atom_comp_fake_launch;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;  // 1 : start effect , 0 : end effect
	xev.xclient.data.l[1] = 0;
	xev.xclient.data.l[2] = 0;
	xev.xclient.data.l[3] = 0;
	xev.xclient.data.l[4] = 0;

	XSendEvent( dpy, win, False,
				SubstructureRedirectMask | SubstructureNotifyMask,
				&xev );
	XSync(dpy, 0 );

}


API void utilx_hide_fake_effect( Display *dpy, Window win)
{
	XEvent xev;

	_atom_comp_fake_launch = XInternAtom( dpy, "_E_COMP_FAKE_LAUNCH", False );
	if(  !_atom_comp_fake_launch )
	{
		fprintf( stderr, "XInternAtom(_E_COMP_FAKE_LAUNCH) failed.\n" );
		return;
	}

	// send fake client message
	xev.xclient.type = ClientMessage;
	xev.xclient.display = dpy;
	xev.xclient.window = win;
	xev.xclient.message_type =  _atom_comp_fake_launch;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 0;  // 1 : start effect , 0 : end effect
	xev.xclient.data.l[1] = 0;
	xev.xclient.data.l[2] = 0;
	xev.xclient.data.l[3] = 0;
	xev.xclient.data.l[4] = 0;

	XSendEvent( dpy, win, False,
				SubstructureRedirectMask | SubstructureNotifyMask,
				&xev );
	XSync(dpy, 0 );
}

static void _utilx_effect_atom_check( Display* dpy )
{
	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}

	if( !_atom_comp_window_effect_type)
		_atom_comp_window_effect_type =  XInternAtom(dpy, "_NET_CM_WINDOW_EFFECT_TYPE",False);
	if( !_atom_comp_effect_default )
		_atom_comp_effect_default = XInternAtom(dpy, "_NET_CM_EFFECT_DEFAULT",False);
	if( !_atom_comp_effect_none )
		_atom_comp_effect_none = XInternAtom(dpy, "_NET_CM_EFFECT_NONE",False);
	if( !_atom_comp_effect_custom0 )
		_atom_comp_effect_custom0 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM0",False);
	if( !_atom_comp_effect_custom1 )
		_atom_comp_effect_custom1 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM1",False);
	if( !_atom_comp_effect_custom2 )
		_atom_comp_effect_custom2 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM2",False);
	if( !_atom_comp_effect_custom3 )
		_atom_comp_effect_custom3 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM3",False);
	if( !_atom_comp_effect_custom4 )
		_atom_comp_effect_custom4 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM4",False);
	if( !_atom_comp_effect_custom5 )
		_atom_comp_effect_custom5 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM5",False);
	if( !_atom_comp_effect_custom6 )
		_atom_comp_effect_custom6 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM6",False);
	if( !_atom_comp_effect_custom7 )
		_atom_comp_effect_custom7 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM7",False);
	if( !_atom_comp_effect_custom8 )
		_atom_comp_effect_custom8 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM8",False);
	if( !_atom_comp_effect_custom9 )
		_atom_comp_effect_custom9 = XInternAtom(dpy, "_NET_CM_EFFECT_CUSTOM9",False);
}

static Atom _utilx_convert_style_to_atom( Display* dpy, Utilx_Effect_Style style )
{
	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return _atom_comp_effect_none;
	}
	_utilx_effect_atom_check(dpy);

	if ( style == UTILX_EFFECT_STYLE_DEFAULT )       return _atom_comp_effect_default;
	else if ( style == UTILX_EFFECT_STYLE_NONE )     return _atom_comp_effect_none;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM0 )  return _atom_comp_effect_custom0;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM1 )  return _atom_comp_effect_custom1;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM2 )  return _atom_comp_effect_custom2;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM3 )  return _atom_comp_effect_custom3;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM4 )  return _atom_comp_effect_custom4;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM5 )  return _atom_comp_effect_custom5;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM6 )  return _atom_comp_effect_custom6;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM7 )  return _atom_comp_effect_custom7;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM8 )  return _atom_comp_effect_custom8;
	else if ( style == UTILX_EFFECT_STYLE_CUSTOM9 )  return _atom_comp_effect_custom9;
	else                                             return _atom_comp_effect_none;

}

static Utilx_Effect_Style _utilx_convert_atom_to_style( Display* dpy, Atom style )
{
	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return UTILX_EFFECT_STYLE_NONE;
	}
	_utilx_effect_atom_check(dpy);

	if ( style == _atom_comp_effect_default )       return UTILX_EFFECT_STYLE_DEFAULT;
	else if ( style == _atom_comp_effect_none )     return UTILX_EFFECT_STYLE_NONE;
	else if ( style == _atom_comp_effect_custom0 )  return UTILX_EFFECT_STYLE_CUSTOM0;
	else if ( style == _atom_comp_effect_custom1 )  return UTILX_EFFECT_STYLE_CUSTOM1;
	else if ( style == _atom_comp_effect_custom2 )  return UTILX_EFFECT_STYLE_CUSTOM2;
	else if ( style == _atom_comp_effect_custom3 )  return UTILX_EFFECT_STYLE_CUSTOM3;
	else if ( style == _atom_comp_effect_custom4 )  return UTILX_EFFECT_STYLE_CUSTOM4;
	else if ( style == _atom_comp_effect_custom5 )  return UTILX_EFFECT_STYLE_CUSTOM5;
	else if ( style == _atom_comp_effect_custom6 )  return UTILX_EFFECT_STYLE_CUSTOM6;
	else if ( style == _atom_comp_effect_custom7 )  return UTILX_EFFECT_STYLE_CUSTOM7;
	else if ( style == _atom_comp_effect_custom8 )  return UTILX_EFFECT_STYLE_CUSTOM8;
	else if ( style == _atom_comp_effect_custom9 )  return UTILX_EFFECT_STYLE_CUSTOM9;
	else                                            return UTILX_EFFECT_STYLE_DEFAULT;
}

API void utilx_set_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type, Utilx_Effect_Style style)
{
	Atom *window_effect_type_list = NULL;
	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return;
	}
	_utilx_effect_atom_check(dpy);

	window_effect_type_list = (Atom *)malloc(sizeof(Atom) * 6);

	if ( !window_effect_type_list )
	{
		fprintf (stderr, "[UTILX] Error.. malloc().. %s (%d)\n", __func__, __LINE__);
		return;
	}

	window_effect_type_list[0] = _atom_comp_effect_default;
	window_effect_type_list[1] = _atom_comp_effect_default;
	window_effect_type_list[2] = _atom_comp_effect_default;
	window_effect_type_list[3] = _atom_comp_effect_default;
	window_effect_type_list[4] = _atom_comp_effect_default;
	window_effect_type_list[5] = _atom_comp_effect_default;

	_utilx_get_window_property(dpy, win, _atom_comp_window_effect_type, XA_ATOM, (unsigned int *)window_effect_type_list, 6);

	if ( type == UTILX_EFFECT_TYPE_MAP )             window_effect_type_list[0] = _utilx_convert_style_to_atom(dpy, style);
	else if ( type == UTILX_EFFECT_TYPE_UNMAP )      window_effect_type_list[1] = _utilx_convert_style_to_atom(dpy, style);
	else if ( type == UTILX_EFFECT_TYPE_RAISEABOVE ) window_effect_type_list[2] = _utilx_convert_style_to_atom(dpy, style);
	else if ( type == UTILX_EFFECT_TYPE_ROTATION )   window_effect_type_list[3] = _utilx_convert_style_to_atom(dpy, style);
	else if ( type == UTILX_EFFECT_TYPE_FOCUSIN )    window_effect_type_list[4] = _utilx_convert_style_to_atom(dpy, style);
	else if ( type == UTILX_EFFECT_TYPE_FOCUSOUT )   window_effect_type_list[5] = _utilx_convert_style_to_atom(dpy, style);

	_utilx_set_window_property(dpy, win, _atom_comp_window_effect_type, XA_ATOM, (unsigned int *)window_effect_type_list, 6);

	XSync(dpy, 0 );
	free(window_effect_type_list);
}

API Utilx_Effect_Style utilx_get_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type)
{
	Atom *window_effect_type_list = NULL;
	Utilx_Effect_Style style = UTILX_EFFECT_STYLE_DEFAULT;

	if ( dpy == NULL )
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return UTILX_EFFECT_STYLE_NONE;
	}
	_utilx_effect_atom_check(dpy);

	window_effect_type_list = (Atom *)malloc(sizeof(Atom) * 6);

	if ( !window_effect_type_list )
	{
		fprintf (stderr, "[UTILX] Error.. malloc().. %s (%d)\n", __func__, __LINE__);
		return UTILX_EFFECT_STYLE_NONE;
	}

	if ( _utilx_get_window_property(dpy, win, _atom_comp_window_effect_type, XA_ATOM, (unsigned int *)window_effect_type_list, 6) != 6 )
	{
		fprintf (stderr, "[UTILX] Error.. get property failed!.. %s (%d)\n", __func__, __LINE__);
		free(window_effect_type_list);
		return UTILX_EFFECT_STYLE_NONE;
	}

	if ( type == UTILX_EFFECT_TYPE_MAP )             style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[0]);
	else if ( type == UTILX_EFFECT_TYPE_UNMAP )      style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[1]);
	else if ( type == UTILX_EFFECT_TYPE_RAISEABOVE ) style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[2]);
	else if ( type == UTILX_EFFECT_TYPE_ROTATION )   style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[3]);
	else if ( type == UTILX_EFFECT_TYPE_FOCUSIN )    style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[4]);
	else if ( type == UTILX_EFFECT_TYPE_FOCUSOUT )   style = _utilx_convert_atom_to_style(dpy, window_effect_type_list[5]);

	XSync(dpy, 0 );
	free(window_effect_type_list);
	return style;
}

API int utilx_set_window_opaque_state (Display* dpy, Window win, Utilx_Opaque_State state)
{
	UTILX_TRACE ("[UTILX] utilx_set_window_opaque_state... win = %x, show_state = %d\n", win, state);

	unsigned int is_opaque;

	if (dpy == NULL)
	{
		fprintf (stderr, "[UTILX] Error.. Invald Display.. %s (%d)\n", __func__, __LINE__);
		return 0;
	}

	switch (state)
	{
		case UTILX_OPAQUE_STATE_OFF:
			is_opaque = 0;
			break;

		case UTILX_OPAQUE_STATE_ON:
			is_opaque = 1;
			break;

		default:
			fprintf (stderr, "[UTILX] Error.. Invald State.. %s (%d)\n", __func__, __LINE__);
			return 0;
	}

	if (!_atom_window_opaque)
	{
		_atom_window_opaque = XInternAtom (dpy, "_E_ILLUME_WINDOW_REGION_OPAQUE", False);
		if (!_atom_window_opaque)
		{
			fprintf (stderr, "[UTILX] Error.. Cannot create _E_ILLUME_WINDOW_REGION_OPAQUE atom.. %s (%d)\n", __func__, __LINE__);
			return 0;
		}
	}

	_utilx_set_window_property (dpy, win, _atom_window_opaque, XA_CARDINAL,
			(unsigned int *)&is_opaque, 1);

	return 1;
}

static void
_utilx_screen_capture_atom_ensure (Display* dpy)
{
	if (_atom_screen_capture_disable)
		return;

	_atom_screen_capture_disable = XInternAtom (dpy, "_CB_SCREEN_CAPTURE_DISABLE", False);
	if (_atom_screen_capture_disable)
		return;

	fprintf (stderr, "[UTILX] Error.. Cannot create _CB_SCREEN_CAPTURE_DISABLE atom.. %s (%d)\n", __func__, __LINE__);
}

API int
utilx_set_screen_capture(Display* dpy, int enable)
{
	Window root;
	int disable;

	if (!dpy)
	{
		fprintf (stderr, "[UTILX] Error.. dpy is NULL %s (%d)\n", __func__, __LINE__);
		return 0;
	}

	root = RootWindow (dpy, DefaultScreen(dpy));
	disable = (enable) ? 0 : 1;

	_utilx_screen_capture_atom_ensure (dpy);

	_utilx_set_window_property (dpy, root, _atom_screen_capture_disable, XA_CARDINAL, (unsigned int *)&disable, 1);

	return 1;
}

API int
utilx_get_screen_capture(Display* dpy)
{
	Window root;
	int disable = 0;

	if (!dpy)
	{
		fprintf (stderr, "[UTILX] Error.. dpy is NULL %s (%d)\n", __func__, __LINE__);
		return 0;
	}

	root = RootWindow (dpy, DefaultScreen(dpy));

	_utilx_screen_capture_atom_ensure (dpy);

	_utilx_get_window_property(dpy, root, _atom_screen_capture_disable, XA_CARDINAL,
	                            (unsigned int *)&disable, 1);

	return (disable) ? 0 : 1;
}

API void utilx_set_window_cardinal_property(Display* dpy, Window win, Atom atom, unsigned int *value)
{
	_utilx_set_window_property(dpy, win, atom, XA_CARDINAL, value, 1);
}

API int utilx_get_window_cardinal_property (Display* dpy, Window win, Atom atom, unsigned int *value)
{
	return _utilx_get_window_property(dpy, win, atom, XA_CARDINAL, value, 1);
}

API void utilx_show_capture_effect( Display *dpy, Window win)
{
    XEvent xev;

    _atom_comp_capture_effect = XInternAtom( dpy, "_E_COMP_CAPTURE_EFFECT", False );
    if(  !_atom_comp_capture_effect )
    {
        fprintf( stderr, "XInternAtom(_E_COMP_CAPTURE_EFFECT) failed.\n" );
        return;
    }

    // send capture effect client message
    xev.xclient.type = ClientMessage;
    xev.xclient.display = dpy;
    xev.xclient.window = win;
    xev.xclient.message_type =  _atom_comp_capture_effect;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 0;
    xev.xclient.data.l[1] = 0;
    xev.xclient.data.l[2] = 0;
    xev.xclient.data.l[3] = 0;
    xev.xclient.data.l[4] = 0;

    XSendEvent( dpy, win, False,
                SubstructureRedirectMask | SubstructureNotifyMask,
                &xev );
    XSync(dpy, 0 );
}
