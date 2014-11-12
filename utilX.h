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

#ifndef __TIZEN_LINUX_UTIL_X11_H__
#define __TIZEN_LINUX_UTIL_X11_H__

#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#else
#define DEPRECATED
#endif

/**
* @internal
* @addtogroup CAPI_UI_UTILX_MODULE
* @{
*/

#include <sys/types.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @internal
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Volume Up' key.
 */
#define KEY_VOLUMEUP		"XF86AudioRaiseVolume"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Volume Down' key.
 */
#define KEY_VOLUMEDOWN		"XF86AudioLowerVolume"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Half-Press of Camera' key.
 */
#define KEY_CAMERA		"XF86WebCam"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Full-Press of Camera' key.
 */
#define KEY_CONFIG		"XF86Pictures"

/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Power' key.
 */
#define KEY_POWER		"XF86PowerOff"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Pause' key.
 */
#define KEY_PAUSE		"XF86Standby"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Cancel' key.
 */
#define KEY_CANCEL              "Cancel"

// Earjack/BT Headset/Multimedia keys
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Play Audio' key.
 */
#define KEY_PLAYCD		"XF86AudioPlay"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Stop Audio' key.
 */
#define KEY_STOPCD		"XF86AudioStop"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Pause Audio' key.
 */
#define KEY_PAUSECD		"XF86AudioPause"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Next Song' key.
 */
#define KEY_NEXTSONG		"XF86AudioNext"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Previous Song' key.
 */
#define KEY_PREVIOUSSONG	"XF86AudioPrev"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Rewind Song' key.
 */
#define KEY_REWIND		"XF86AudioRewind"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Forward Song' key.
 */
#define KEY_FASTFORWARD		"XF86AudioForward"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Media' key.
 */
#define KEY_MEDIA		"XF86AudioMedia"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'PlayPause' key.
 */
#define KEY_PLAYPAUSE		"XF86AudioPlayPause"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Mute' key.
 */
#define KEY_MUTE			"XF86AudioMute"

// 3-Touch key
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Send' key.
 */
#define KEY_SEND		"XF86Send"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Home' key.
 */
#define KEY_SELECT		"XF86Phone"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'End' key.
 */
#define KEY_END			"XF86Stop"

// Renamed 3-Touch key
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Send' key.
 */
#define KEY_MENU		"XF86Send"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Home' key.
 */
#define KEY_HOME		"XF86Phone"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'End' key.
 */
#define KEY_BACK		"XF86Stop"

//Other functions keys
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'HomePage' key.
 */
#define KEY_HOMEPAGE		"XF86HomePage"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'WWW' key.
 */
#define KEY_WEBPAGE		"XF86WWW"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Mail' key.
 */
#define KEY_MAIL			"XF86Mail"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'ScreenSaver' key.
 */
#define KEY_SCREENSAVER	"XF86ScreenSaver"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'BrightnessUp' key.
 */
#define KEY_BRIGHTNESSUP 	"XF86MonBrightnessUp"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'BrightnessDown' key.
 */
#define KEY_BRIGHTNESSDOWN	"XF86MonBrightnessDown"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Soft keyboard(toggle)' key.
 */
#define KEY_SOFTKBD			"XF86MenuKB"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Quick panel(toggle)' key.
 */
#define KEY_QUICKPANEL		"XF86Tools"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Task switcher(toggle)' key.
 */
#define KEY_TASKSWITCH		"XF86TaskPane"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Apptray(toggle)' key.
 */
#define KEY_APPS		"XF86Launch0"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Search(toggle)' key.
 */
#define KEY_SEARCH		"XF86Search"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Voice(toggle)' key.
 */
#define KEY_VOICE		"XF86Launch2"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Language(toggle)' key.
 */
#define KEY_LANGUAGE		"Hangul"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Call(toggle)' key.
 */
#define KEY_CONNECT			"XF86Go"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Play(toggle)' key.
 */
#define KEY_GAMEPLAY		"XF86Game"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Voice Wakeup LPSD' key.
 */
#define KEY_VOICEWAKEUP_LPSD		"XF86Launch3"
/**
 * @brief Definition for XKeySym (XServer Key Symbol) corresponding to the 'Voice Wakeup' key.
 */
#define KEY_VOICEWAKEUP		"XF86Launch4"

/**
 * @brief Definition for the length of a string corresponding to the 'Volume Up' key.
 */
#define LEN_KEY_VOLUMEUP		20
/**
 * @brief Definition for the length of a string corresponding to the 'Volume Down' key.
 */
#define LEN_KEY_VOLUMEDOWN	20

/**
 * @brief Definition for the length of a string corresponding to the 'Half-Press of Camera' key.
 */
#define LEN_KEY_CAMERA		10
/**
 * @brief Definition for the length of a string corresponding to the 'Full-Press of Camera' key.
 */
#define LEN_KEY_CONFIG		12

/**
 * @brief Definition for the length of a string corresponding to the 'Power' key.
 */
#define LEN_KEY_POWER		12
/**
 * @brief Definition for the length of a string corresponding to the 'Pause' key.
 */
#define LEN_KEY_PAUSE		11

// Earjack/BT Headset/Multimedia keys
/**
 * @brief Definition for the length of a string corresponding to the 'Play Audio' key.
 */
#define LEN_KEY_PLAYCD		13
/**
 * @brief Definition for the length of a string corresponding to the 'Stop Audio' key.
 */
#define LEN_KEY_STOPCD		13
/**
 * @brief Definition for the length of a string corresponding to the 'Pause Audio' key.
 */
#define LEN_KEY_PAUSECD		14
/**
 * @brief Definition for the length of a string corresponding to the 'Next Song' key.
 */
#define LEN_KEY_NEXTSONG	13
/**
 * @brief Definition for the length of a string corresponding to the 'Previous Song' key.
 */
#define LEN_KEY_PREVIOUSSONG		13
/**
 * @brief Definition for the length of a string corresponding to the 'Rewind Song' key.
 */
#define LEN_KEY_REWIND		15
/**
 * @brief Definition for the length of a string corresponding to the 'Forwand Song' key.
 */
#define LEN_KEY_FASTFORWARD		16
/**
 * @brief Definition for the length of a string corresponding to the 'Media' key.
 */
#define LEN_KEY_MEDIA		14
/**
 * @brief Definition for the length of a string corresponding to the 'PlayPause' key.
 */
#define LEN_KEY_PLAYPAUSE	13
/**
 * @brief Definition for the length of a string corresponding to the 'Mute' key.
 */
#define LEN_KEY_MUTE		13

// 3-Touch key
/**
 * @brief Definition for the length of a string corresponding to the 'Send' key.
 */
#define LEN_KEY_SEND		8
/**
 * @brief Definition for the length of a string corresponding to the 'Home' key.
 */
#define LEN_KEY_SELECT		9
/**
 * @brief Definition for the length of a string corresponding to the 'End' key.
 */
#define LEN_KEY_END		8

// Renamed 3-Touch key
/**
 * @brief Definition for the length of a string corresponding to the 'Send' key.
 */
#define LEN_KEY_MENU		8
/**
 * @brief Definition for the length of a string corresponding to the 'Home' key.
 */
#define LEN_KEY_HOME		9
/**
 * @brief Definition for the length of a string corresponding to the 'End' key.
 */
#define LEN_KEY_BACK		8

//Other functions keys
/**
 * @brief Definition for the length of a string corresponding to the 'HomePage' key.
 */
#define LEN_KEY_HOMEPAGE	12
/**
 * @brief Definition for the length of a string corresponding to the 'WWW' key.
 */
#define LEN_KEY_WEBPAGE	7
/**
 * @brief Definition for the length of a string corresponding to the 'Mail' key.
 */
#define LEN_KEY_MAIL		8
/**
 * @brief Definition for the length of a string corresponding to the 'ScreenSaver' key.
 */
#define LEN_KEY_SCREENSAVER	15
/**
 * @brief Definition for the length of a string corresponding to the 'BrightnessUp' key.
 */
#define LEN_KEY_BRIGHTNESSUP	19
/**
 * @brief Definition for the length of a string corresponding to the 'BrightnessDown' key.
 */
#define LEN_KEY_BRIGHTNESSDOWN	21
/**
 * @brief Definition for the length of a string corresponding to the 'Soft keyboard(toggle)' key.
 */
#define LEN_KEY_SOFTKBD		10
/**
 * @brief Definition for the length of a string corresponding to the 'Quick panel(toggle)' key.
 */
#define LEN_KEY_QUICKPANEL		9
/**
 * @brief Definition for the length of a string corresponding to the 'Task switcher(toggle)' key.
 */
#define LEN_KEY_TASKSWITCH	12
/**
 * @brief Definition for the length of a string corresponding to the 'Apptray(toggle)' key.
 */
#define LEN_KEY_APPS			11
/**
 * @brief Definition for the length of a string corresponding to the 'Search(toggle)' key.
 */
#define LEN_KEY_SEARCH			10
/**
 * @brief Definition for the length of a string corresponding to the 'Voice(toggle)' key.
 */
#define LEN_KEY_VOICE			11
/**
 * @brief Definition for the length of a string corresponding to the 'Language(toggle)' key.
 */
#define LEN_KEY_LANGUAGE		6
/**
 * @brief Definition for the length of a string corresponding to the 'Call(toggle)' key.
 */
#define LEN_KEY_CONNECT			6
/**
 * @brief Definition for the length of a string corresponding to the 'Play(toggle)' key.
 */
#define LEN_KEY_GAMEPLAY		8
/**
 * @brief Definition for the length of a string corresponding to the 'Voice Wakeup LPSD' key.
 */
#define LEN_KEY_VOICEWAKEUP_LPSD	11
/**
 * @brief Definition for the length of a string corresponding to the 'Voice Wakeup' key.
 */
#define LEN_KEY_VOICEWAKEUP			11

/**
 * @brief Definition for getting the grabbed-key exclusively regardless of its position on the window stack with the possibility of overriding the grab by the other client window mode.
 */
#define OR_EXCLUSIVE_GRAB	0xf00000
/**
 * @brief Definition for getting the grabbed-key exclusively regardless of its position on the window stack mode.
 */
#define EXCLUSIVE_GRAB		0x0f0000
/**
 * @brief Definition for getting the grabbed-key only when on the top of the grabbing-window stack mode.
 */
#define TOP_POSITION_GRAB	0x00f000
/**
 * @brief Definition for getting the grabbed-key together with the other client window(s) mode.
 */
#define SHARED_GRAB		0x000f00
/**
 * @brief Definition for getting the key-grab mode of a client window.
 */
#define GRAB_MODE_MASK	0xffff00

/**
 * @brief Definition for the client window grabbing the key which is already in the EXCLUSIVE mode.
 */
#define EXCLUSIVE_GRABBED_ALREADY	1

/**
 * @brief Definition for getting/setting the property while grabbing a key for a window.
 */
#define STR_ATOM_GRAB_KEY	"_GRAB_KEY"
/**
 * @brief Definition for the key grabbed by a client window in the EXCLUSIVE mode.
 */
#define STR_ATOM_GRAB_EXCL_WIN	"_GRAB_EXCL_WIN_KEYCODE"
/**
 * @brief Definition for the key grabbed by a client window in the OR_EXCLUSIVE mode.
 */
#define STR_ATOM_GRAB_OR_EXCL_WIN	"_GRAB_OR_EXCL_WIN_KEYCODE"

/**
 * @brief Enumeration for notification window's priority level.
 */
typedef enum _Utilx_Notification_Level
{
	UTILX_NOTIFICATION_LEVEL_LOW, /**< Low level notification */
	UTILX_NOTIFICATION_LEVEL_NORMAL, /**< Normal level notification*/
	UTILX_NOTIFICATION_LEVEL_HIGH /**< High level notification */
} Utilx_Notification_Level;

/**
 * @brief Enumeration for the opaque state.
 */
typedef enum _Utilx_Opaque_State
{
	UTILX_OPAQUE_STATE_OFF = 0, /**< Transparent state */
	UTILX_OPAQUE_STATE_ON  = 1, /**< Opaque state */
} Utilx_Opaque_State;

/**
 * @brief Sets the priority level for the specified notification window, asynchronously.
 *
 * @details This function sets the priority level of notification windows.\n
 *          Every notification window has a base priority level by the notification window's priority value (default priority is #UTILX_NOTIFICATION_LEVEL_LOW).
 *
 *          The priority is used for ordering of notification windows.\n
 *          The notification window with the priority set to #UTILX_NOTIFICATION_LEVEL_HIGH will be placed at the top of the notification windows.\n
 *          If there are notification windows which have same priorities, the last created notification window will be placed on the other window.
 *
 * @since_tizen 2.3
 * @remarks This is used only for notification windows.
 * @param[in] dpy The connection to the X server
 * @param[in] win The window to set
 * @param[in] level The level (#UTILX_NOTIFICATION_LEVEL_LOW, #UTILX_NOTIFICATION_LEVEL_NORMAL, #UTILX_NOTIFICATION_LEVEL_HIGH)
 * @pre The window should be a notification type window.
 * @see #Utilx_Notification_Level
 * @see utilx_get_system_notification_level()
 * @par Example
  @code
  #include <utilX.h>

  ...

  Evas_Object *win;
  Ecore_X_Window xwin;

  win = create_mwnd();
  xwin = elm_win_xwindow_get(win);

  // Set Notification type
  ecore_x_netwm_window_type_set (xwin, ECORE_X_WINDOW_TYPE_NOTIFICATION);

  // Set Notification's priority
  utilx_set_system_notification_level (ecore_x_display_get(), xwin, UTILX_NOTIFICATION_LEVEL_HIGH);

  ...
  @endcode
 */
void utilx_set_system_notification_level (Display* dpy, Window win, Utilx_Notification_Level level);

/**
 * @brief Gets the priority level for the specified notification window.
 *
 * @details This function returns the priority level of notification windows.\n
 *          If a user didn't set the notification's priority level, this function returns the default value (#UTILX_NOTIFICATION_LEVEL_LOW).
 *
 *          This function is a synchronous call.
 *
 * @since_tizen 2.3
 * @remarks This is used only for notification windows.
 * @param[in] dpy The connection to the X server
 * @param[in] win The window to get
 * @return The current notification level (#UTILX_NOTIFICATION_LEVEL_LOW, #UTILX_NOTIFICATION_LEVEL_NORMAL, #UTILX_NOTIFICATION_LEVEL_HIGH)
 * @pre The window should be a notification type window.
 * @see utilx_set_system_notification_level()
 * @par Example
  @code
  #include <utilX.h>

  ...

  Evas_Object *win;
  Ecore_X_Window xwin;
  Utilx_Notification_Level level;

  win = elm_win_add (NULL, "test", ELM_WIN_NOTIFICATION);
  xwin = elm_win_xwindow_get(win);

  level = utilx_get_system_notification_level (ecore_x_display_get(), xwin);

  ...
  @endcode
 */
Utilx_Notification_Level utilx_get_system_notification_level (Display* dpy, Window win);

/**
 * @brief Grabs the key specfied by @a key_name for a window in the @a grab_mode.
 *
 * @details This function establishes a grab of the specified key for the specified window.\n
 *          Once a key is grabbed, all events originating from the key will only be reported to the specfied window.\n
 *          The grab of the key can be released by calling utilx_ungrab_key().
 *
 *          This function is synchronous.
 *
 * @since_tizen 2.3
 * @remarks If utilx_grab_key() returns @c 0, the specified window will get the events of the specified key.\n
 *          However, delivery of a key can always be changed by other applications grabbing the key with higher priority.\n
 *          It can also be changed by the changes of window stacks.\n
 *          A trial for choosing a proper grab mode will be needed.
 * @param[in] dpy The connection to the X server
 * @param[in] win The window to grab a key
 * @param[in] key_name The name of a key in the string (ex> #KEY_VOLUMEUP, #KEY_VOLUMEDOWN, #KEY_SEND, and so on)
 * @param[in] grab_mode The grab mode (such as #EXCLUSIVE_GRAB, #TOP_POSITION_GRAB, and #SHARED_GRAB)
 * @return @c 0 on success,
 *         otherwise failure
 * @pre This API must be called after the window 'win' has been mapped.
 * @post This API adds/changes the window property related to the grabbed key.
 * @see utilx_ungrab_key()
 * @par Example (using X11 APIs)
  @code

  // EXCLUSIVE_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	int grab_result;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      grab_result = utilx_grab_key(disp, w, KEY_POWER, EXCLUSIVE_GRAB);
		      if( EXCLUSIVE_GRABBED_ALREADY == grab_result )
		            return -1;
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  // TOP_POSITION_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      utilx_grab_key(disp, w, KEY_POWER, TOP_POSITION_GRAB);
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  // SHARED_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      utilx_grab_key(disp, w, KEY_POWER, SHARED_GRAB);
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  @endcode
   * @par Example (using EFL APIs)
  @code

  // EXCLUSIVE_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	int grab_result = utilx_grab_key(disp, win, KEY_POWER, EXCLUSIVE_GRAB);
	if( EXCLUSIVE_GRABBED_ALREADY == grab_result )
		return -1;

	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to
	return 0;
  }

  // TOP_POSITION_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	utilx_grab_key(disp, win, KEY_POWER, TOP_POSITION_GRAB);

	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to
	return 0;
  }

  // SHARED_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	utilx_grab_key(disp, win, KEY_POWER, SHARED_GRAB);

	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to
	return 0;
  }
  @endcode
 */
int utilx_grab_key (Display* dpy, Window win, const char* key_name, int grab_mode);

/**
 * @brief Ungrabs the key specfied by @a key_name for a window.
 *
 * @details This function releases the already established grab of the specfied key for the specified window.\n
 *          Once the grab of the key is released, delivery of the key events for the specfied window is going to be stopped.
 *
 *          This function is synchronous.
 *
 * @since_tizen 2.3
 * @param[in] dpy The connection to the X server
 * @param[in] win The window to grab a key
 * @param[in] key_name The name of a key in the string (ex> #KEY_VOLUMEUP, #KEY_VOLUMEDOWN, #KEY_SEND, and so on)
 * @return @c 0 on success,
 *         otherwise failure
 * @pre This API must be called after the window 'win' is mapped.
 * @post This API changes/removes the window property related to the grabbed key.
 * @see utilx_grab_key()
 * @par Example (using X11 APIs)
  @code

  // EXCLUSIVE_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	int grab_result;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      grab_result = utilx_grab_key(disp, w, KEY_POWER, EXCLUSIVE_GRAB);
		      if( EXCLUSIVE_GRABBED_ALREADY == grab_result )
		            return -1;
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  // TOP_POSITION_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      utilx_grab_key(disp, w, KEY_POWER, TOP_POSITION_GRAB);
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  // SHARED_GRAB //

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	XEvent e;
	Window w = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 5,5, 470, 780, 2, BlackPixel(d,0), WhitePixel(d,0));
	XSelectInput(disp, w, StructureNotifyMask | KeyPressMask | KeyReleaseMask);
	XMapWindow(disp, w);

	while(1)
	{
	      XNextEvent(disp, &e);
	      switch(e.type)
	      {
	             case MapNotify:
		      utilx_grab_key(disp, w, KEY_POWER, SHARED_GRAB);
		      break;
	      }
	      ...
	}
	...

	utilx_ungrab_key(disp, win, KEY_POWER);
	return 0;
  }

  @endcode
   * @par Example (using EFL APIs)
  @code

  // EXCLUSIVE_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	int grab_result = utilx_grab_key(disp, win, KEY_POWER, EXCLUSIVE_GRAB);
	if( EXCLUSIVE_GRABBED_ALREADY == grab_result )
		return -1;
	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to
	return 0;
  }

  // TOP_POSITION_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	utilx_grab_key(disp, win, KEY_POWER, TOP_POSITION_GRAB);

	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to

	return 0;
  }

  // SHARED_GRAB //

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Ecore_X_Window win = ecore_evas_software_x11_window_get(ee);

	utilx_grab_key(disp, win, KEY_POWER, SHARED_GRAB);

	...

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever a user wants to
	return 0;
  }
  @endcode
 */
int utilx_ungrab_key (Display* dpy, Window win, const char* key_name);

/**
 * @brief Sets the window's opaque state.
 *
 * @details This function sets the window's visibility to opaque even if the window is an alpha window.
 *          This function is available only for an alpha window.
 *          An alpha window's default opaque state is #UTILX_OPAQUE_STATE_OFF.
 *
 *          This function is an asynchronous call.
 *
 * @since_tizen 2.3
 * @remarks This is used only for alpha windows.
 * @param[in] dpy The connection to the X server
 * @param[in] win The window handle
 * @param[in] state The value that indicates whether the window has set a visible state to opaque(#UTILX_OPAQUE_STATE_ON) or not(#UTILX_OPAQUE_STATE_OFF)
 * @return @c 1 on success,
           otherwise failure
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>

  ...

  Display* dpy;
  Window root, win;
  int ret;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  win = XCreateSimpleWindow (dpy, root, 0, 0, 480, 800, 2, BlackPixel (dpy,0), WhitePixel(dpy,0));
  XMapWindow (dpy, win);

  ret = utilx_set_window_opaque_state (dpy, win, UTILX_OPAQUE_STATE_ON);
  if (!ret)
  {
    printf ("Error! Failed to set opaque state.\n");
  }

  XFlush (dpy);

  ...
  @endcode
 */
int utilx_set_window_opaque_state (Display* dpy, Window win, Utilx_Opaque_State state);

/**
 * @brief Creates a screenshot image.
 *
 * @details This function creates a screenshot image of the display.\n
 *          To use this function, you should get the permission first.\n
 *          In addition, device LCD must be turned on; otherwise, this function fails.\n
 *          Once this functions is called, utilx_release_screen_shot() should be called after it.
 *
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/screenshot
 * @remarks You should get the permission to use. Device LCD must be on.
 * @param[in] dpy The connection to the X server
 * @param[in] width The root window handle
 * @param[in] height The root window handle
 * @see utilx_release_screen_shot()
 * @par Example
  @code
    Display* dpy;
    int width, height;
    void *dump;

    dpy = XOpenDisplay (NULL);
    width = DisplayWidth (dpy, DefaultScreen (dpy));
    height = DisplayHeight (dpy, DefaultScreen (dpy));

    dump = utilx_create_screen_shot (dpy, width, height);
    if (dump)
    {
        // do_something (dump);
    }
    else
    {
        // utilx_create_screen_shot can return NULL in some cases.
        // Even if it returns NULL, utilx_release_screen_shot should be called.
    }

    utilx_release_screen_shot ();
  @endcode
 */
void* utilx_create_screen_shot (Display* dpy, int width, int height);

/**
 * @brief Releases screenshot resources.
 *
 * @details This function releases resources associated with screenshot
 *          image of the display. utilx_release_screen_shot() should be called once
 *          utilx_create_screen_shot() is called.
 *
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/screenshot
 * @see utilx_create_screen_shot()
 * @par Example
  @code
    Display* dpy;
    int width, height;
    void *dump;

    dpy = XOpenDisplay (NULL);
    width = DisplayWidth (dpy, DefaultScreen (dpy));
    height = DisplayHeight (dpy, DefaultScreen (dpy));

    dump = utilx_create_screen_shot (dpy, width, height);
    if (dump)
    {
        // do_something (dump);
    }
    else
    {
        // utilx_create_screen_shot can return NULL in some cases.
        // Even if it returns NULL, utilx_release_screen_shot should be called.
    }

    utilx_release_screen_shot ();
  @endcode
 */
void  utilx_release_screen_shot (void);

#ifdef __cplusplus
}
#endif

/**
*@}
*/

#endif /* __TIZEN_LINUX_UTIL_X11_H__ */

