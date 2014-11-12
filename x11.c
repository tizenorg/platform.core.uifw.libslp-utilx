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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

#include "utilX.h"
#include "utilX_ext.h"
#include "util_x11.h"

#include <fcntl.h>
#include <X11/extensions/Xvlib.h>
#include <X11/extensions/Xvproto.h>
#include <X11/extensions/Xdamage.h>
#include <X11/extensions/XShm.h>
#include <xf86drm.h>
#include <tbm_bufmgr.h>
#include <dri2.h>


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

static Atom _atom_comp_fake_launch_image = None;

static Atom _atom_window_opaque = None;

static Atom _atom_window_pixman = None;

const unsigned long maxlen = 1024l;

static void _utilx_set_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int num);
static int _utilx_get_window_property (Display* dpy, Window win, Atom atom, Atom type, unsigned int *val, unsigned int len);


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

	for( i=0 ; i < nr_item ; i++ )
	{
		if( key_list && (key_list[i] == keycode) )
			return;
	}

	XChangeProperty(disp, DefaultRootWindow(disp), ex_grabwin, XA_CARDINAL, 32,
	nr_item ? PropModeAppend : PropModeReplace, (unsigned char *)&keycode, 1);
	XSync(disp, False);

out:
	_free_list_of_grabbed_key(key_list);
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

	_free_new_list_of_grabbed_key(new_key_list);

out:
	_free_list_of_grabbed_key(key_list);
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
        {
	        _free_list_of_grabbed_key(key_list);
			return EXCLUSIVE_GRABBED_ALREADY;
        }
	}

out:
	_free_list_of_grabbed_key(key_list);
	return result;
}

API int utilx_grab_key (Display* disp, Window win, const char* key, int grab_mode)
{
	unsigned long cnt;
	int *key_list = NULL;
	int i, result=0, ret = 0;
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

		if( result )
		{
			goto out;
		}
	}

	keycode |= grab_mode;

	cnt = _get_list_of_grabbed_key(disp, win, &key_list);
	if (cnt > 0) {
		i = _search_grabbed_key(key_list, keycode, cnt);
		_free_list_of_grabbed_key(key_list);
		if ( i != -1 ) {
			fprintf(stderr, "Key is already grabbed\n");
			goto out;
		}
	}

	XChangeProperty(disp, win, _atom_grab_key, XA_CARDINAL, 32,
			cnt ? PropModeAppend : PropModeReplace, (unsigned char *)&keycode, 1);
	XSync(disp, False);
	keycode = keycode & (~GRAB_MODE_MASK);

	if( EXCLUSIVE_GRAB == grab_mode )
		_set_exclusive_grab_info_to_root(disp, keycode, win, grab_mode);
	if( OR_EXCLUSIVE_GRAB == grab_mode )
	{
		ret = _is_grabbed_key_exclusively(disp, keycode, grab_mode);

		if( !ret )
		{
			_set_exclusive_grab_info_to_root(disp, keycode, win, grab_mode);
		}
	}

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

API UtilxScrnConf *utilx_scrnconf_allocate (void)
{
    UtilxScrnConf *scrnconf = calloc (1, sizeof(UtilxScrnConf));
    if (!scrnconf)
    {
        fprintf (stderr, "fail to allocate UtilxScrnConf\n");
        return NULL;
    }

    return scrnconf;
}

API void utilx_scrnconf_free (UtilxScrnConf *scrnconf)
{
    if (!scrnconf)
        return;

    if (scrnconf->str_output)
        free (scrnconf->str_output);

    if (scrnconf->str_resolution)
        free (scrnconf->str_resolution);

    free(scrnconf);
    scrnconf = NULL;
}

API int utilx_scrnconf_get_info (Display *dpy, UtilxScrnConf *scrnconf)
{
    Window win;
	Atom scrnconf_atom = None;
    XTextProperty xtp;
    char *str = NULL;
    char *ptr = NULL;
    int items;
    char **list = NULL;
    int i = 0;
    int s;

    if (!dpy)
        goto fail;

    if (!scrnconf)
        goto fail;

    win = DefaultRootWindow(dpy);

    scrnconf_atom = XInternAtom (dpy, "_SCRNCONF_INFO", False);

    /* get property */
    if (XGetTextProperty (dpy, win, &xtp, scrnconf_atom))
    {
        s = XmbTextPropertyToTextList (dpy, &xtp, &list, &items);
        if ((s == XLocaleNotSupported) ||
            (s == XNoMemory) || (s == XConverterNotFound))
          str = strdup((char *)xtp.value);
        else if ((s >= Success) && (items > 0))
          str = strdup(list[0]);

        if (list)
            XFreeStringList (list);

        XFree(xtp.value);
    }

    ptr = strtok (str, ",");
    while (ptr != NULL)
    {
        if (i == 0)
        {
            scrnconf->str_output = calloc (1, strlen(ptr)+1);
            if (!scrnconf->str_output)
                goto fail;

            strcpy (scrnconf->str_output, ptr);
        }
        else if (i == 1)
        {
            if (!strcmp(ptr, "CONNECT"))
                scrnconf->status = UTILX_SCRNCONF_STATUS_CONNECT;
            else if (!strcmp(ptr, "ACTIVE"))
                scrnconf->status = UTILX_SCRNCONF_STATUS_ACTIVE;
            else
                scrnconf->status = UTILX_SCRNCONF_STATUS_NULL;
        }
        else if (i == 2)
        {
            scrnconf->str_resolution = calloc (1, strlen(ptr)+1);
            if (!scrnconf->str_resolution)
                goto fail;

            strcpy (scrnconf->str_resolution, ptr);
        }
        else if (i == 3)
        {
            if (!strcmp(ptr, "CLONE"))
                scrnconf->dispmode = UTILX_SCRNCONF_DISPMODE_CLONE;
            else if (!strcmp(ptr, "EXTENDED"))
                scrnconf->dispmode = UTILX_SCRNCONF_DISPMODE_EXTENDED;
            else
                scrnconf->dispmode = UTILX_SCRNCONF_DISPMODE_NULL;
        }
        else
           break;

        ptr = strtok (NULL, ",");
        i++;
    }

    free (str);

    return 1;
fail:
    if (str)
        free (str);

    return 0;
}

API int utilx_scrnconf_set_dispmode (Display *dpy, Utilx_Scrnconf_Dispmode dispmode)
{
    Window win = DefaultRootWindow(dpy);
	XEvent xev;
	Atom scrnconf_atom = None;
    UtilxScrnConf *scrnconf = NULL;

    scrnconf = utilx_scrnconf_allocate ();
    if (!scrnconf)
        return 0;

    if (!utilx_scrnconf_get_info (dpy, scrnconf))
    {
        utilx_scrnconf_free (scrnconf);
        return 0;
    }

    if (scrnconf->status  == UTILX_SCRNCONF_STATUS_NULL)
    {
        fprintf (stderr, "[utilx_scrnconf]: the status of screen configuration is null\n");
        utilx_scrnconf_free (scrnconf);
        return 0;
    }

    if (scrnconf->dispmode == dispmode)
    {
        fprintf (stderr, "[utilx_scrnconf]: dispmode (%d) already set\n", dispmode);
        utilx_scrnconf_free (scrnconf);
        return 1;
    }

    utilx_scrnconf_free (scrnconf);

    scrnconf_atom = XInternAtom (dpy, "_SCRNCONF_DISPMODE_SET", False);

	xev.xclient.window = win;
	xev.xclient.type = ClientMessage;
	xev.xclient.message_type = scrnconf_atom;
	xev.xclient.format = 32;
	xev.xclient.data.s[0] = dispmode;

	XSendEvent(dpy, win, False, StructureNotifyMask, &xev);
	XSync(dpy, False);

    return 1;
}

typedef struct _ShotInfo
{
    Display *dpy;

    /* PutImage */
    int      port;
    unsigned int width;
    unsigned int height;
    Pixmap   pixmap;
    GC       gc;

    /* Damage */
    Damage   damage;
    int      damage_base;

    void    *virtual;

    /* XShm */
    XImage    *image;
    XShmSegmentInfo shminfo;
} ShotInfo;

#define FOURCC(a,b,c,d) (((unsigned)d&0xff)<<24 | ((unsigned)c&0xff)<<16 | ((unsigned)b&0xff)<<8 | ((unsigned)a&0xff))

#define FOURCC_RGB32    FOURCC('R','G','B','4')
#define TIMEOUT_CAPTURE 3

    /* x error handling */
static Bool x_error_caught;

static ShotInfo *shot_info;

static int
_get_port (Display *dpy, unsigned int id, Window win)
{
    unsigned int ver, rev, req_base, evt_base, err_base;
    unsigned int adaptors;
    XvAdaptorInfo *ai = NULL;
    XvImageFormatValues *fo = NULL;
    int formats;
    int i, j, p;

    if (XvQueryExtension (dpy, &ver, &rev, &req_base, &evt_base, &err_base) != Success)
    {
        fprintf (stderr, "[UTILX] no XV extension. \n");
        return -1;
    }

    if (XvQueryAdaptors (dpy, win, &adaptors, &ai) != Success)
    {
        fprintf (stderr, "[UTILX] fail : query adaptors. \n");
        return -1;
    }

    if (!ai)
    {
        fprintf (stderr, "[UTILX] fail : get adaptor info. \n");
        return -1;
    }

    for (i = 0; i < adaptors; i++)
    {
        int support_format = False;

        if (!(ai[i].type & XvInputMask) ||
            !(ai[i].type & XvStillMask))
            continue;

        p = ai[i].base_id;

        fo = XvListImageFormats (dpy, p, &formats);
        for (j = 0; j < formats; j++)
            if (fo[j].id == (int)id)
                support_format = True;

        if (fo)
            XFree (fo);

        if (!support_format)
            continue;

        for (; p < ai[i].base_id + ai[i].num_ports; p++)
        {
            if (XvGrabPort (dpy, p, 0) == Success)
            {
                XvFreeAdaptorInfo (ai);
                return p;
            }
        }

        fprintf (stderr, "[UTILX] fail : grab port. \n");
    }

    XvFreeAdaptorInfo (ai);

    return -1;
}

static void
_deinit_screen_shot (ShotInfo *info)
{
    if (!info)
        return;

    if (info->port > 0 && info->pixmap > 0)
        XvStopVideo (info->dpy, info->port, info->pixmap);

    if (info->image)
        XDestroyImage (info->image);
    if (info->shminfo.shmid != -1)
    {
        XShmDetach (info->dpy, &info->shminfo);
        shmdt (info->shminfo.shmaddr);
        shmctl (info->shminfo.shmid, IPC_RMID, 0);
    }

    if (info->damage)
        XDamageDestroy (info->dpy, info->damage);

    if (info->gc)
        XFreeGC (info->dpy, info->gc);
    if (info->pixmap > 0)
        XFreePixmap (info->dpy, info->pixmap);
    if (info->port > 0)
        XvUngrabPort (info->dpy, info->port, 0);

    XSync (info->dpy, False);

    free (info);
    shot_info = NULL;
}

static int
_screen_shot_x_error_handle (Display *dpy, XErrorEvent *ev)
{
    if (!shot_info || (dpy != shot_info->dpy))
        return 0;

    x_error_caught = True;

    return 0;
}

static Bool
_init_screen_shot_damage (ShotInfo *info)
{
    int damage_err_base = 0;

    if (!XDamageQueryExtension(info->dpy, &info->damage_base, &damage_err_base))
    {
        fprintf (stderr, "[UTILX] no X Damage extension. \n");
        return False;
    }

    info->damage = XDamageCreate (info->dpy, info->pixmap, XDamageReportNonEmpty);
    if (info->damage <= 0)
    {
        fprintf (stderr, "[UTILX] fail : create damage \n");
        return False;
    }

    return True;
}

static Bool
_init_screen_shot_shm (ShotInfo *info)
{
    if (!XShmQueryExtension (info->dpy))
    {
        fprintf (stderr, "[UTILX] no XShm extension. !!\n");
        return False;
    }

    info->image = XShmCreateImage (info->dpy,
                                   DefaultVisual (info->dpy, DefaultScreen (info->dpy)),
                                   DefaultDepth (info->dpy, DefaultScreen (info->dpy)),
                                   ZPixmap,
                                   NULL,
                                   &info->shminfo,
                                   info->width,
                                   info->height);
    if (!info->image)
    {
        fprintf (stderr, "[UTILX] fail : XShmCreateImage \n");
        return False;
    }

    info->shminfo.shmid = shmget (IPC_PRIVATE, info->image->bytes_per_line * info->height, IPC_CREAT | 0777);
    if (info->shminfo.shmid == -1)
    {
        XDestroyImage (info->image);
        fprintf (stderr, "[UTILX] fail : shmget\n");
        return False;
    }

    info->shminfo.shmaddr = shmat (info->shminfo.shmid, 0, 0);
    if (info->shminfo.shmaddr == (void *) -1)
    {
        XDestroyImage (info->image);
        shmctl (info->shminfo.shmid, IPC_RMID, 0);
        info->shminfo.shmid = -1;
        fprintf (stderr, "[UTILX] fail : shmat\n");
        return False;
    }

    info->shminfo.readOnly = False;

    if (!XShmAttach (info->dpy, &info->shminfo))
    {
        XDestroyImage (info->image);
        shmdt (info->shminfo.shmaddr);
        shmctl (info->shminfo.shmid, IPC_RMID, 0);
        info->shminfo.shmid = -1;
        fprintf (stderr, "[UTILX] fail : XShmAttach\n");
        return False;
    }

    info->image->data = info->shminfo.shmaddr;
    info->virtual = info->shminfo.shmaddr;

    return True;
}

static ShotInfo*
_init_screen_shot (Display* dpy, unsigned int width, unsigned int height)
{
    ShotInfo *info = NULL;
    static Atom atom_capture = None;
    XErrorHandler old_handler = NULL;

    if (shot_info)
    {
        if (shot_info->width == width && shot_info->height == height)
            return shot_info;

        _deinit_screen_shot (shot_info);
    }

    info = calloc (1, sizeof (ShotInfo));
    if (!info)
        goto fail_init;

    shot_info = info;

    /* dpy */
    info->dpy = dpy;
    info->shminfo.shmid = -1;
    info->shminfo.shmaddr = (void*)-1;

    /* port */
    info->port = _get_port (info->dpy, FOURCC_RGB32, DefaultRootWindow (dpy));
    if (info->port <= 0)
        goto fail_init;

    /* width, height */
    if (atom_capture == None)
        atom_capture = XInternAtom (info->dpy, "_USER_WM_PORT_ATTRIBUTE_CAPTURE", False);

    XSync (info->dpy, 0);
    x_error_caught = False;
    old_handler = XSetErrorHandler (_screen_shot_x_error_handle);

    XvSetPortAttribute (info->dpy, info->port, atom_capture, 1);

    XSync (info->dpy, 0);

    x_error_caught = False;
    XSetErrorHandler (old_handler);

    XvQueryBestSize (info->dpy, info->port, 0, 0, 0, width, height, &width, &height);
    if (width <= 0 || height <= 0)
        goto fail_init;
    info->width = width;
    info->height = height;

    /* pixmap */
    info->pixmap = XCreatePixmap (info->dpy,
                                  DefaultRootWindow (info->dpy),
                                  width, height,
                                  DefaultDepth (info->dpy, DefaultScreen (info->dpy)));
    if (info->pixmap <= 0)
    {
        fprintf (stderr, "[UTILX] fail : create pixmap. \n");
        goto fail_init;
    }

    /* gc */
    info->gc = XCreateGC (info->dpy, info->pixmap, 0, 0);
    if (info->gc == NULL)
    {
        fprintf (stderr, "[UTILX] fail : create gc. \n");
        goto fail_init;
    }

    XSetForeground (info->dpy, info->gc, 0xFF000000);
    XFillRectangle (info->dpy, info->pixmap, info->gc, 0, 0, width, height);

    if (!_init_screen_shot_damage (info))
        goto fail_init;

    if (!_init_screen_shot_shm (info))
        goto fail_init;
    else
        fprintf (stderr, "[UTILX] XShm success. !!\n");

    if (!info->virtual)
    {
        fprintf (stderr, "[UTILX] fail : get virtual \n");
        goto fail_init;
    }

    XFlush (info->dpy);

    return info;

fail_init:
    _deinit_screen_shot (info);
    return NULL;
}

API void*
utilx_create_screen_shot (Display* dpy, int width, int height)
{
    ShotInfo *info;
    XEvent ev = {0,};
    XErrorHandler old_handler = NULL;

    if (dpy == NULL)
    {
        fprintf (stderr, "[UTILX] invalid display(%p) \n", dpy);
        return NULL;
    }

    if (width <= 0 || height <= 0)
    {
        fprintf (stderr, "[UTILX] invalid size(%dx%d) \n", width, height);
        return NULL;
    }

    XSync (dpy, 0);

    info = _init_screen_shot (dpy, width, height);

    if (!info)
    {
        fprintf (stderr, "[UTILX] fail : initialize screenshot. \n");
        return NULL;
    }

    XSync (dpy, 0);

    x_error_caught = False;
    old_handler = XSetErrorHandler (_screen_shot_x_error_handle);

    XvPutStill (info->dpy, info->port, info->pixmap, info->gc,
                0, 0, info->width, info->height,
                0, 0, info->width, info->height);

    XSync (dpy, 0);

    if (x_error_caught)
    {
        x_error_caught = False;
        XSetErrorHandler (old_handler);
        return NULL;
    }

    x_error_caught = False;
    XSetErrorHandler (old_handler);

    if (XPending (info->dpy))
        XNextEvent (info->dpy, &ev);
    else
    {
        int fd = ConnectionNumber (info->dpy);
        fd_set mask;
        struct timeval tv;
        int ret;

        FD_ZERO (&mask);
        FD_SET (fd, &mask);

        tv.tv_usec = 0;
        tv.tv_sec = TIMEOUT_CAPTURE;

        ret = select (fd + 1, &mask, 0, 0, &tv);
        if (ret < 0)
            fprintf (stderr, "[UTILX] fail: select.\n");
        else if (ret == 0)
            fprintf (stderr, "[UTILX] timeout(%d sec)!\n", TIMEOUT_CAPTURE);
        else if (XPending (info->dpy))
            XNextEvent (info->dpy, &ev);
        else
            fprintf (stderr, "[UTILX] fail: not passed a event!\n");
    }

    if (ev.type == (info->damage_base + XDamageNotify))
    {
        XDamageNotifyEvent *damage_ev = (XDamageNotifyEvent *)&ev;
        if (damage_ev->drawable == info->pixmap)
        {
            XShmGetImage (info->dpy, info->pixmap, info->image, 0, 0, AllPlanes);
            XDamageSubtract (info->dpy, info->damage, None, None );
            return info->virtual;
        }

        XDamageSubtract (info->dpy, info->damage, None, None );
    }

    utilx_release_screen_shot ();

    return NULL;
}

static ShotInfo*
_init_video_screen_shot (Display* dpy, unsigned int width, unsigned int height, Window win)
{
    ShotInfo *info = NULL;
    static Atom atom_capture = None;
    static Atom atom_capture_on_win = None;
    XErrorHandler old_handler = NULL;

    if (shot_info)
    {
        if (shot_info->width == width && shot_info->height == height)
            return shot_info;

        _deinit_screen_shot (shot_info);
    }

    info = calloc (1, sizeof (ShotInfo));
    if (!info)
        goto fail_init;

    shot_info = info;

    /* dpy */
    info->dpy = dpy;
    info->shminfo.shmid = -1;
    info->shminfo.shmaddr = (void*)-1;

    /* port */
    info->port = _get_port (info->dpy, FOURCC_RGB32, win);
    if (info->port <= 0)
        goto fail_init;

    /* width, height */
    if (atom_capture == None)
        atom_capture = XInternAtom (info->dpy, "_USER_WM_PORT_ATTRIBUTE_CAPTURE", False);

    if (atom_capture_on_win  == None)
        atom_capture_on_win = XInternAtom (info->dpy, "_USER_WM_PORT_ATTRIBUTE_CAPTURE_ON_WINDOW", False);

    XSync (info->dpy, 0);
    x_error_caught = False;
    old_handler = XSetErrorHandler (_screen_shot_x_error_handle);

    XvSetPortAttribute (info->dpy, info->port, atom_capture, 3);
    XvSetPortAttribute (info->dpy, info->port, atom_capture_on_win, 1);

    XSync (info->dpy, 0);

    x_error_caught = False;
    XSetErrorHandler (old_handler);

    XvQueryBestSize (info->dpy, info->port, 0, 0, 0, width, height, &width, &height);
    if (width <= 0 || height <= 0)
        goto fail_init;
    info->width = width;
    info->height = height;

    /* pixmap */
    info->pixmap = XCreatePixmap (info->dpy,
                                  win,
                                  width, height,
                                  DefaultDepth (info->dpy, DefaultScreen (info->dpy)));
    if (info->pixmap <= 0)
    {
        fprintf (stderr, "[UTILX] fail : create pixmap. \n");
        goto fail_init;
    }

    /* gc */
    info->gc = XCreateGC (info->dpy, info->pixmap, 0, 0);
    if (info->gc == NULL)
    {
        fprintf (stderr, "[UTILX] fail : create gc. \n");
        goto fail_init;
    }

    XSetForeground (info->dpy, info->gc, 0xFF000000);
    XFillRectangle (info->dpy, info->pixmap, info->gc, 0, 0, width, height);

    if (!_init_screen_shot_damage (info))
        goto fail_init;

    if (!_init_screen_shot_shm (info))
        goto fail_init;
    else
        fprintf (stderr, "[UTILX] XShm success. !!\n");

    if (!info->virtual)
    {
        fprintf (stderr, "[UTILX] fail : get virtual \n");
        goto fail_init;
    }

    XFlush (info->dpy);

    return info;

fail_init:
    _deinit_screen_shot (info);
    return NULL;
}

Bool
predicate_proc(Display *dpy, XEvent *event, char *arg)
{
    ShotInfo *info = (ShotInfo *)arg;

    if(event->type == (info->damage_base + XDamageNotify))
        return True;
    else
        return False;
}
API void*
utilx_create_video_screen_shot (Display* dpy, Window win, int width, int height)
{
    ShotInfo *info;
    XEvent ev = {0,};
    XErrorHandler old_handler = NULL;
    unsigned int pixmap = 0;

    if (dpy == NULL)
    {
        fprintf (stderr, "[UTILX] invalid display(%p) \n", dpy);
        return NULL;
    }

    if (width <= 0 || height <= 0)
    {
        fprintf (stderr, "[UTILX] invalid size(%dx%d) \n", width, height);
        return NULL;
    }

    XSync (dpy, 0);

    info = _init_video_screen_shot (dpy, width, height, win);

    if (!info)
    {
        fprintf (stderr, "[UTILX] fail : initialize screenshot. \n");
        return NULL;
    }

    if (!_atom_window_pixman)
    {
        _atom_window_pixman = XInternAtom (dpy, "_UTIL_WINDOW_PIXMAP_HANDLE", False);
        if (!_atom_window_pixman)
        {
            fprintf (stderr, "[UTILX] Error.. Cannot create _UTIL_WINDOW_PIXMAP_HANDLE atom.. %s (%d)\n", __func__, __LINE__);
            return 0;
        }
    }

    x_error_caught = False;
    old_handler = XSetErrorHandler (_screen_shot_x_error_handle);

    pixmap = (unsigned int)info->pixmap;
    XChangeProperty (dpy, win, _atom_window_pixman, XA_PIXMAP, 32, PropModeReplace, (unsigned char *)((unsigned int *)&pixmap), 1);
    XSync (dpy, 0);

    if (x_error_caught)
    {
        x_error_caught = False;
        XSetErrorHandler (old_handler);
        return NULL;
    }

    XvPutStill (info->dpy, info->port, info->pixmap, info->gc,
                0, 0, info->width, info->height,
                0, 0, info->width, info->height);
    XSync (dpy, 0);

    if (x_error_caught)
    {
        x_error_caught = False;
        XSetErrorHandler (old_handler);
        return NULL;
    }

    XDeleteProperty(info->dpy, win, _atom_window_pixman);
    _atom_window_pixman = None;
    XSync (dpy, 0);

    x_error_caught = False;
    XSetErrorHandler (old_handler);

    XIfEvent(info->dpy, &ev, predicate_proc, info);
    if (ev.type == (info->damage_base + XDamageNotify))
    {
        XDamageNotifyEvent *damage_ev = (XDamageNotifyEvent *)&ev;
        if (damage_ev->drawable == info->pixmap)
        {
            XShmGetImage (info->dpy, info->pixmap, info->image, 0, 0, AllPlanes);
            XDamageSubtract (info->dpy, info->damage, None, None );
            return info->virtual;
        }

        XDamageSubtract (info->dpy, info->damage, None, None );
    }

    utilx_release_screen_shot ();

    return NULL;
}

API void
utilx_release_screen_shot (void)
{
    _deinit_screen_shot (shot_info);
}

#define XRR_PROPERTY_FB_VISIBLE     "XRR_PROPERTY_FB_VISIBLE"
#define XRR_PROPERTY_VIDEO_OFFSET   "XRR_PROPERTY_VIDEO_OFFSET"

static Bool
_utilx_xrr_set_property (Display* dpy, Atom atom, unsigned char *buf, int buf_len, unsigned char **get)
{
    Window root = None;
    XRRScreenResources *res = NULL;
    RROutput rr_output = None;
    int i;

    root = XRootWindow (dpy, 0);
    if (root == None)
    {
        fprintf (stderr, "[UTILX] Warning : Root window is None.. %s (%d)\n", __func__, __LINE__);
        return False;
    }

    res = XRRGetScreenResources (dpy, root);
    if (res == NULL || res->noutput == 0)
    {
        fprintf (stderr, "[UTILX] Warning : ScreenResources is None.. %s (%d)\n", __func__, __LINE__);
        return False;
    }

    for (i = 0; i < res->noutput; i++)
    {
        XRROutputInfo *output_info = XRRGetOutputInfo (dpy, res, res->outputs[i]);
        if (output_info)
        {
            if (!strcmp (output_info->name, "LVDS1"))
            {
                rr_output = res->outputs[i];
                XRRFreeOutputInfo(output_info);
                break;
            }
            XRRFreeOutputInfo(output_info);
        }
    }

    if (rr_output == None)
    {
        fprintf (stderr, "[UTILX] Warning : output is None.. %s (%d)\n", __func__, __LINE__);
        XRRFreeScreenResources (res);
        return False;
    }

    XRRChangeOutputProperty (dpy, rr_output, atom,
                             XA_CARDINAL, 8, PropModeReplace, buf, buf_len);

    if (get)
    {
        Atom actual_type;
        int actual_format;
        unsigned long nitems, bytes_after;

        XRRGetOutputProperty (dpy, rr_output, atom,
                              0, 1024L,
                              True, False, XA_CARDINAL,
                              &actual_type, &actual_format,
                              &nitems, &bytes_after,
                              get);
    }

    XSync (dpy, 0);

    XRRFreeScreenResources (res);

    return True;
}

API void
utilx_set_fb_visible (Display* dpy, Utilx_Fb_Type fb, Bool visible)
{
    static Atom property = None;
    char buf[8192] = {0,};
    char *p = buf;
    int buf_len = 0;

    if (!dpy)
    {
        fprintf (stderr, "[UTILX] invalid display(%p).. %s (%d)\n", dpy, __func__, __LINE__);
        return;
    }

    if (fb <= UTILX_FB_TYPE_NONE || fb > UTILX_FB_TYPE_OVERLAY)
    {
        fprintf (stderr, "[UTILX] Error.. Invald fb(%d).. %s (%d)\n", fb, __func__, __LINE__);
        return;
    }

    p += sprintf (p, "%d:", 0);
    p += sprintf (p, "%d", fb + 2);
    p += sprintf (p, ":%d", (visible > 0)? 1 : 0);

    *p = '\0';
    p++;

    buf_len = p - buf;

    if (property == None)
        property = XInternAtom (dpy, XRR_PROPERTY_FB_VISIBLE, False);

    if (property == None)
    {
        fprintf (stderr, "[UTILX] Warning : FB_VISIBLE property is None.. %s (%d)\n", __func__, __LINE__);
        return;
    }

    if (!_utilx_xrr_set_property (dpy, property, (unsigned char*)buf, buf_len, NULL))
    {
        fprintf (stderr, "[UTILX] Warning : set_property failed.. %s (%d)\n", __func__, __LINE__);
        return;
    }
}

API Bool
utilx_get_fb_visible (Display* dpy, Utilx_Fb_Type fb)
{
    static Atom property = None;
    char buf[32] = {0,};
    char *p = buf;
    int buf_len = 0;
    unsigned char *prop = NULL;
    Bool visible = False;

    if (!dpy)
    {
        fprintf (stderr, "[UTILX] invalid display(%p).. %s (%d)\n", dpy, __func__, __LINE__);
        return False;
    }

    if (fb <= UTILX_FB_TYPE_NONE || fb > UTILX_FB_TYPE_OVERLAY)
    {
        fprintf (stderr, "[UTILX] Error.. Invald fb(%d).. %s (%d)\n", fb, __func__, __LINE__);
        return False;
    }

    p += sprintf (p, "%d:", 0);
    p += sprintf (p, "%d", fb + 2);

    *p = '\0';
    p++;

    buf_len = p - buf;

    if (property == None)
        property = XInternAtom (dpy, XRR_PROPERTY_FB_VISIBLE, False);

    if (property == None)
    {
        fprintf (stderr, "[UTILX] Warning : FB_VISIBLE property is None.. %s (%d)\n", __func__, __LINE__);
        return False;
    }

    if (!_utilx_xrr_set_property (dpy, property, (unsigned char*)buf, buf_len, &prop))
    {
        fprintf (stderr, "[UTILX] Warning : set_property failed.. %s (%d)\n", __func__, __LINE__);
        return False;
    }

    if (prop)
        visible = atoi((char*)prop);

    return visible;
}
