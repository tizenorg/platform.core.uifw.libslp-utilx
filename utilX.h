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

#ifndef __SAMSUNG_LINUX_UTIL_X11_H__
#define __SAMSUNG_LINUX_UTIL_X11_H__

#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#else
#define DEPRECATED
#endif

/**
 * @defgroup utilX X11 utilities
 * @ingroup lib
 * @brief Samsung Linux platform X11 utilties
 *
 * Common X11 utilities
 * You can use this API with #include <utilX.h>
 */

/**
 * @addtogroup utilX
 * @{
 */

#include <sys/types.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#ifdef __cplusplus
extern "C" {
#endif


#define KEY_VOLUMEUP		"XF86AudioRaiseVolume"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Volume Up' key */
#define KEY_VOLUMEDOWN		"XF86AudioLowerVolume"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Volume Down' key */

#define KEY_CAMERA		"XF86WebCam"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Half-Press of Camera' key */
#define KEY_CONFIG		"XF86Pictures"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Full-Press of Camera' key */

#define KEY_POWER		"XF86PowerOff"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Power' key */
#define KEY_PAUSE		"XF86Standby"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Pause' key */
#define KEY_CANCEL              "Cancel"        /**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Cancel' key */

// Earjack/BT Headset/Multimedia keys
#define KEY_PLAYCD		"XF86AudioPlay"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Play Audio' key */
#define KEY_STOPCD		"XF86AudioStop"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Stop Audio' key */
#define KEY_PAUSECD		"XF86AudioPause"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Pause Audio' key */
#define KEY_NEXTSONG		"XF86AudioNext"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Next Song' key */
#define KEY_PREVIOUSSONG	"XF86AudioPrev"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Previous Song' key */
#define KEY_REWIND		"XF86AudioRewind"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Rewind Song' key */
#define KEY_FASTFORWARD		"XF86AudioForward"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Forward Song' key */
#define KEY_MEDIA		"XF86AudioMedia"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Media' key */
#define KEY_PLAYPAUSE		"XF86AudioPlay"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'PlayPause' key */
#define KEY_MUTE			"XF86AudioMute"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Mute' key */

// 3-Touch key
#define KEY_SEND		"XF86Send"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Send' key */
#define KEY_SELECT		"XF86Phone"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Home' key */
#define KEY_END			"XF86Stop"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'End' key */

// Renamed 3-Touch key
#define KEY_MENU		"XF86Send"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Send' key */
#define KEY_HOME		"XF86Phone"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Home' key */
#define KEY_BACK		"XF86Stop"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'End' key */

//Other functions keys
#define KEY_HOMEPAGE		"XF86HomePage"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'HomePage' key */
#define KEY_WEBPAGE		"XF86WWW"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'WWW' key */
#define KEY_MAIL			"XF86Mail"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Mail' key */
#define KEY_SCREENSAVER	"XF86ScreenSaver"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'ScreenSaver' key */
#define KEY_BRIGHTNESSUP 	"XF86MonBrightnessUp"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'BrightnessUp' key */
#define KEY_BRIGHTNESSDOWN	"XF86MonBrightnessDown"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'BrightnessDown' key */
#define KEY_SOFTKBD			"XF86MenuKB"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Soft keyboard(toggle)' key */
#define KEY_QUICKPANEL		"XF86Tools"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Quick panel(toggle)' key */
#define KEY_TASKSWITCH		"XF86TaskPane"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Task switcher(toggle)' key */
#define KEY_APPS		"XF86Launch0"	/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Apptray(toggle)' key */
#define KEY_SEARCH		"XF86Search"		/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Search(toggle)' key */
#define KEY_VOICE		"XF86Launch2"		/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Voice(toggle)' key */
#define KEY_LANGUAGE		"Hangul"		/**< this macro means the XKeySym (XServer Key Symbol) corresponds to 'Language(toggle)' key */

#define LEN_KEY_VOLUMEUP		20	/**< this macro is the length of string corresponds to 'Volume Up' key */
#define LEN_KEY_VOLUMEDOWN	20	/**< this macro is the length of string corresponds to 'Volume Down' key */

#define LEN_KEY_CAMERA		10	/**< this macro is the length of string corresponds to 'Half-Press of Camera' key */
#define LEN_KEY_CONFIG		12	/**< this macro is the length of string corresponds to 'Full-Press of Camera' key */

#define LEN_KEY_POWER		12	/**< this macro is the length of string corresponds to 'Power' key */
#define LEN_KEY_PAUSE		11	/**< this macro is the length of string corresponds to 'Pause' key */

// Earjack/BT Headset/Multimedia keys
#define LEN_KEY_PLAYCD		13/**< this macro is the length of string corresponds to 'Play Audio' key */
#define LEN_KEY_STOPCD		13/**< this macro is the length of string corresponds to 'Stop Audio' key */
#define LEN_KEY_PAUSECD		14/**< this macro is the length of string corresponds to 'Pause Audio' key */
#define LEN_KEY_NEXTSONG	13/**< this macro is the length of string corresponds to 'Next Song' key */
#define LEN_KEY_PREVIOUSSONG		13/**< this macro is the length of string corresponds to 'Previous Song' key */
#define LEN_KEY_REWIND		15/**< this macro is the length of string corresponds to 'Rewind Song' key */
#define LEN_KEY_FASTFORWARD		16/**< this macro is the length of string corresponds to 'Forwand Song' key */
#define LEN_KEY_MEDIA		14/**< this macro is the length of string corresponds to 'Media' key */
#define LEN_KEY_PLAYPAUSE	13	/**< this macro is the length of string corresponds to 'PlayPause' key */
#define LEN_KEY_MUTE		13	/**< this macro is the length of string corresponds to 'Mute' key */

// 3-Touch key
#define LEN_KEY_SEND		8	/**< this macro is the length of string corresponds to 'Send' key */
#define LEN_KEY_SELECT		9	/**< this macro is the length of string corresponds to 'Home' key */
#define LEN_KEY_END		8	/**< this macro is the length of string corresponds to 'End' key */

// Renamed 3-Touch key
#define LEN_KEY_MENU		8	/**< this macro is the length of string corresponds to 'Send' key */
#define LEN_KEY_HOME		9	/**< this macro is the length of string corresponds to 'Home' key */
#define LEN_KEY_BACK		8	/**< this macro is the length of string corresponds to 'End' key */

//Other functions keys
#define LEN_KEY_HOMEPAGE	12	/**< this macro is the length of string corresponds to 'HomePage' key */
#define LEN_KEY_WEBPAGE	7	/**< this macro is the length of string corresponds to 'WWW' key */
#define LEN_KEY_MAIL		8	/**< this macro is the length of string corresponds to 'Mail' key */
#define LEN_KEY_SCREENSAVER	15	/**< this macro is the length of string corresponds to 'ScreenSaver' key */
#define LEN_KEY_BRIGHTNESSUP	19	/**< this macro is the length of string corresponds to 'BrightnessUp' key */
#define LEN_KEY_BRIGHTNESSDOWN	21	/**< this macro is the length of string corresponds to 'BrightnessDown' key */

#define LEN_KEY_SOFTKBD		10	/**< this macro is the length of string corresponds to 'Soft keyboard(toggle)' key */
#define LEN_KEY_QUICKPANEL		9	/**< this macro is the length of string corresponds to 'Quick panel(toggle)' key */
#define LEN_KEY_TASKSWITCH	12	/**< this macro is the length of string corresponds to 'Task switcher(toggle)' key */
#define LEN_KEY_APPS			11	/**< this macro is the length of string corresponds to 'Apptray(toggle)' key */
#define LEN_KEY_SEARCH			10	/**< this macro is the length of string corresponds to 'Search(toggle)' key */
#define LEN_KEY_VOICE			11	/**< this macro is the length of string corresponds to 'Voice(toggle)' key */
#define LEN_KEY_LANGUAGE		6	/**< this macro is the length of string corresponds to 'Language(toggle)' key */

#define OR_EXCLUSIVE_GRAB	0xf00000	/**< this means that the client window will always get the grabbed-key exclusively regardless of the position on the window stack but the grab is overridable by the other client window */
#define EXCLUSIVE_GRAB		0x0f0000	/**< this means that the client window will always get the grabbed-key exclusively regardless of the position on the window stack */
#define TOP_POSITION_GRAB	0x00f000	/**< this means that the client window will get the grabbed-key only when on the top of the grabbing-window stack */
#define SHARED_GRAB		0x000f00	/**< this means that the client window will get the grabbed-key together with the other client window(s) */
#define GRAB_MODE_MASK	0xffff00	/**< this mask will be used for getting the key-grab mode of a client window */

#define EXCLUSIVE_GRABBED_ALREADY	1	/**< this means that the client window is grabbing the key already in EXCLUSIVE mode */

#define STR_ATOM_GRAB_KEY	"_GRAB_KEY"	/**< this is an XATOM for getting/setting the property for grabbing a key for a window */
#define STR_ATOM_GRAB_EXCL_WIN	"_GRAB_EXCL_WIN_KEYCODE"	/**< this means that the key was grabbed by a client window in EXCLUSIVE mod */
#define STR_ATOM_GRAB_OR_EXCL_WIN	"_GRAB_OR_EXCL_WIN_KEYCODE"	/**< this means that the key was grabbed by a client window in OR_EXCLUSIVE mod */

#define STR_ATOM_SCRNCONF_STATUS "_SCRNCONF_STATUS" /**< this is an XATOM for getting the status of the screen configuration through the client message */

/**
 * @brief Enumeration of screen configuration status
 */
typedef enum _Utilx_Scrnconf_Status
{
	UTILX_SCRNCONF_STATUS_NULL,    /**< screen configuration status is null */
	UTILX_SCRNCONF_STATUS_CONNECT, /**< screen configuration status is connect */
	UTILX_SCRNCONF_STATUS_ACTIVE   /**< screen configuration status is active */
} Utilx_Scrnconf_Status;

/**
 * @brief Enumeration of screen configuration display mode
 */
typedef enum _Utilx_Scrnconf_Dispmode
{
	UTILX_SCRNCONF_DISPMODE_NULL,    /**< display mode of screen configuration is null */
	UTILX_SCRNCONF_DISPMODE_CLONE,   /**< display mode of screen configuration is clone */
	UTILX_SCRNCONF_DISPMODE_EXTENDED /**< display mode of screen configuration is extended */
} Utilx_Scrnconf_Dispmode;


/**
 * @brief Enumeration of key status
 */
typedef enum _Utilx_Key_Status
{
	UTILX_KEY_STATUS_PRESSED, /**< key status is pressed */
	UTILX_KEY_STATUS_RELEASED, /**< key status is released */
	UTILX_KEY_STATUS_UNKNOWN /** < key status is unknown or error happened */
} Utilx_Key_Status;

/**
 * @brief Enumeration of notification window's priority level
 */
typedef enum _Utilx_Notification_Level
{
	UTILX_NOTIFICATION_LEVEL_LOW, /**< low level notification */
	UTILX_NOTIFICATION_LEVEL_NORMAL, /**< normal level notification*/
	UTILX_NOTIFICATION_LEVEL_HIGH /**< high level notification */
} Utilx_Notification_Level;

/**
 * @brief Enumeration of Compositing Window Manager's Effect Type
 */
typedef enum _Utilx_Effect_Type
{
	UTILX_EFFECT_TYPE_MAP, /**< Effect for Window's Map Notify Event */
	UTILX_EFFECT_TYPE_UNMAP, /**< Effect for Window's UnMap Notify Event */
	UTILX_EFFECT_TYPE_RAISEABOVE, /**< Effect for Window's Configure Notify ( RaiseAbove case ) Event */
	UTILX_EFFECT_TYPE_ROTATION, /**< Effect for Window's Rotation Property Change Notify Event ( X Property: ECORE_X_ATOM_E_ILLUME_ROTATE_WINDOW_ANGLE ) */
	UTILX_EFFECT_TYPE_FOCUSIN, /**< Effect for Window's FocusIn Event ( E17's Event: E_EVENT_BORDER_FOCUS_IN ) */
	UTILX_EFFECT_TYPE_FOCUSOUT /**< Effect for Window's FocusOut Event ( E17's Event : E_EVENT_BORDER_FOCUS_OUT ) */
} Utilx_Effect_Type;

/**
 * @brief Enumeration of Compositing Window Manager's Effect Style
 */
typedef enum _Utilx_Effect_Style
{
	UTILX_EFFECT_STYLE_DEFAULT, /**< Default Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_NONE, /**< None of Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM0, /**< Custom0 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM1, /**< Custom1 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM2, /**< Custom2 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM3, /**< Custom3 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM4, /**< Custom4 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM5, /**< Custom5 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM6, /**< Custom6 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM7, /**< Custom7 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM8, /**< Custom8 Effect Style for Effect Type */
	UTILX_EFFECT_STYLE_CUSTOM9 /**< Custom9 Effect Style for Effect Type */
} Utilx_Effect_Style;

/**
 * @brief Enumeration of opaque state
 */
typedef enum _Utilx_Opaque_State
{
	UTILX_OPAQUE_STATE_OFF = 0, /**< Transparent state */
	UTILX_OPAQUE_STATE_ON  = 1, /**< Opaque state */
} Utilx_Opaque_State;

/**
 * @brief Enumeration of Fb's type
 */
typedef enum _Utilx_Fb_Type
{
	UTILX_FB_TYPE_NONE     = 0, /**< None type */
	UTILX_FB_TYPE_UI       = 1, /**< Framebuffer type is 'UI' */
	UTILX_FB_TYPE_OVERLAY  = 2, /**< Framebuffer type is 'Overlay' */
} Utilx_Fb_Type;

/**
 * @brief Structure of screen configuration information
 */
typedef struct _UtilxScrnConf
{
	char *str_output;                 /**< string value for the connector type */
	Utilx_Scrnconf_Status status;     /**< status of screen configurtaion */
	char *str_resolution;             /**< string value for the resolution to be active status */
	Utilx_Scrnconf_Dispmode dispmode; /**< display mode of screen configuration to be active status */
} UtilxScrnConf;

/**
 * @fn ScrnConf *utilx_scrnconf_allocate(void)
 * @brief allocate the UtilxScrnConf structure
 *
 * This function allocate the UtilxScrnConf structure.\n
 *
 * @remark This is used only application which want to know the screen configuration info.
 * @pre  This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_scrnconf_allocate
 * @par Example
  @code
  #include <utilX.h>
  ...

  UtilxScrnConf *scrnconf = NULL;

  // Allocate the UtilxScrnConf structure
  scrnconf = utilx_scrnconf_allocate();
   ...
  @endcode
 */
UtilxScrnConf *utilx_scrnconf_allocate (void);

/**
 * @fn void utilx_scrnconf_free (UtilxScrnConf *scrnconf)
 * @brief free the UtilxScrnConf structure
 *
 * This function free the UtilxScrnConf structure.\n
 *
 * @param[in] scrnconf Specifies the UtilxScrnConf structure
 * @return instance of the UtilxScrnConf structure
 * @remark This is used only application which want to know the screen configuration info.
 * @pre  This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_scrnconf_free
 * @par Example
  @code
  #include <utilX.h>
  ...

  UtilxScrnConf *scrnconf = NULL;

  // Allocate the UtilxScrnConf structure
  scrnconf = utilx_scrnconf_allocate();
   ...

  // Free the UtilxScrnConf structure
  utilx_scrnconf_free(scrnconf);
   ...
  @endcode
 */
void utilx_scrnconf_free (UtilxScrnConf *scrnconf);

/**
 * @fn void utilx_scrnconf_get_info (Display *dpy, UtilxScrnConf *scrnconf)
 * @brief get the information of the screen configuration
 *
 * This function get the information of the screen configuration.\n
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] scrnconf Specifies the information structure of the screen configuration
 * @remark This is used only application which want to know the screen configuration info.
 * @pre  This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_scrnconf_get_info
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;
  UtilxScrnConf *scrnconf = NULL;
  int ret = 0;

  dpy = XOpenDisplay (NULL);

  // Allocate the UtilxScrnConf structure
  scrnconf = utilx_scrnconf_allocate();
  ...

  // Set the display mode for the screen configuration
  ret = utilx_scrnconf_get_info (dpy, scrnconf);
  ...

  // Free the UtilxScrnConf structure
  utilx_scrnconf_free(scrnconf);
   ...

  @endcode
 */
int utilx_scrnconf_get_info (Display *dpy, UtilxScrnConf *scrnconf);


/**
 * @fn void utilx_scrnconf_set_dispmode (Display *dpy, Utilx_Scrnconf_Dispmode dispmode)
 * @brief set the display mode for the screen configuration
 *
 * This function set the display mode for the screen configuration.\n
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] dipmode Specifies the display mode of the screen configuration
 * @return 1 if setting the dispmode is succeeded, 0 if setting the dispmode is failed.
 * @remark This is used only application which want to set the display mode of the screen configuration.
 * @pre  This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_scrnconf_set_dispmode
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;

  dpy = XOpenDisplay (NULL);

  // Set the display mode for the screen configuration
  utilx_scrnconf_set_dispmode (dpy, UTILX_SCRNCONF_DISPMODE_CLONE);
   ...
  @endcode
 */
int utilx_scrnconf_set_dispmode (Display *dpy, Utilx_Scrnconf_Dispmode dispmode);


/**
 * @fn void utilx_set_system_notification_level (Display* dpy, Window win, Utilx_Notification_Level level)
 * @brief Sets the priority level for the specified notification window
 *
 * This function sets the priority level of the notification windows.\n
 * Every notification window has a base priority level by the notification window's priority value. (Default priority is UTILX_NOTIFICATION_LEVEL_LOW)
 *
 * The priority is used for ordering of notification windows.\n
 * The notification window which is set UTILX_NOTIFICATION_LEVEL_HIGH priority will be placed to the top of notification windows.\n
 * If there are notification windows that have same priorities, the latest created notification window is placed on the other window.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to be set
 * @param[in] level Specifies the level (UTILX_NOTIFICATION_LEVEL_LOW, UTILX_NOTIFICATION_LEVEL_NORMAL, UTILX_NOTIFICATION_LEVEL_HIGH)
 * @remark This is used only notification window.
 * @pre The win should be notification type window
 * @post None
 * @see utilx_get_system_notification_level
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
 * @fn Utilx_Notification_Level utilx_get_system_notification_level (Display* dpy, Window win)
 * @brief Gets the priority level for the specified notification window
 *
 * This function returns the priority level of the notification windows.\n
 * If a user didn't set the notification's priority level, this function returns default value (UTILX_NOTIFICATION_LEVEL_LOW).
 *
 * This function is a synchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to be get
 * @return current notication level (UTILX_NOTIFICATION_LEVEL_LOW, UTILX_NOTIFICATION_LEVEL_NORMAL, UTILX_NOTIFICATION_LEVEL_HIGH)
 * @remark This is used only notification window.
 * @pre The win should be notification type window
 * @post None
 * @see utilx_set_system_notification_level
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
 * @fn void utilx_enable_indicator (Display* dpy, Window win, int enable)
 * @brief Sets the window to show/hide the indicator
 *
 * This function enables or disables the indicator.
 *
 * If an application wants to show the window with the indicator, the application must call this function with 1 as the enable parameter.\n
 * Otherwise, the application must call this function with 0 as the enable parameter.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to use indicator
 * @param[in] enable Specifies whether the window use indicator or not
 * @remark None
 * @pre None
 * @post If the enable is 1, then the indicator window should be shown on the screen. Otherwise, the indicator window should be hidden from the screen.
 * @see elm_win_indicator_state_set, utilx_get_indicator_state
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>

  ...

  Display* dpy;
  Window root, win;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  win = XCreateSimpleWindow (dpy, root, 0, 0, 480, 800, 2, BlackPixel (dpy,0), WhitePixel(dpy,0));
  XMapWindow (dpy, win);

  // If the win want to show indicator, enables indicator.
  utilx_enable_indicator (dpy, win, 1);
  XFlush (d);

  // If the win want to hide indicator, disables indicator.
  utilx_enable_indicator (dpy, win, 0);
  XFlush (d);

  ...
  @endcode
 */
void utilx_enable_indicator (Display* dpy, Window win, int enable);

/**
 * @fn int utilx_get_indicator_state (Display* dpy, Window win)
 * @brief Gets the indicator's state of the specified window
 *
 * This function gets the indicator's state of the specified window.
 *
 * An application can set the indicator's state using utilx_enable_indicator or elm_win_indicator_state_set.
 * If an application sets enables the indicator, this returns 1.\n
 * If an application disables the indicator, this returns 0.\n
 * If an application doesn't set the indicator's state, in other words,
 * an application doesn't call utilx_enable_indicator or elm_win_indicator_state_set,
 * this returns -1.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to get the indicator's state
 * @return 1 if the indicator is enabled, 0 if the indicator is disabled, otherwise -1
 * @remark None
 * @pre None
 * @post None
 * @see elm_win_indicator_state_set, utilx_enable_indicator
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>

  ...

  Display* dpy;
  Window root, win;
  int state;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  win = XCreateSimpleWindow (dpy, root, 0, 0, 480, 800, 2, BlackPixel (dpy,0), WhitePixel(dpy,0));
  XMapWindow (dpy, win);

  state = utilx_get_indicator_state (dpy, win)
  // state is -1 (unknown)

  // If the win want to show indicator, enables indicator.
  utilx_enable_indicator (dpy, win, 1);
  XFlush (d);

  state = utilx_get_indicator_state (dpy, win)
  // state is 1 (enabled)

  // If the win want to hide indicator, disables indicator.
  utilx_enable_indicator (dpy, win, 0);
  XFlush (d);

  state = utilx_get_indicator_state (dpy, win)
  // state is 0 (disabled)

  ...
  @endcode
 */
int utilx_get_indicator_state (Display* dpy, Window win);


/**
 * @fn int utilx_grab_key (Display* dpy, Window win, const char* key_name, int grab_mode)
 * @brief Grabs a key specfied by key_name for win in grab_mode
 *
 * This function establishs a grab of the specified key for the specified window.\n
 * Once a key was grabbed, all events originated from the key will only be reported to the specfied window.\n
 * The grab of the key will be released by calling utilx_ungrab_key.
 *
 * This function is synchronous.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to grab a key
 * @param[in] key_name Name of a key in string (ex> KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_SEND and so on)
 * @param[in] grab_mode Grab mode (such as EXCLUSIVE_GRAB, TOP_POSITION_GRAB and SHARED_GRAB)
 * @return 0 on Success, otherwise Fail
 * @remark If utilx_grab_key() returns 0, the specified window will get the events of the specified key.\n
                  However, delivery of a key can always be changed by other applications grabbing the key with higher priority.\n
                  It can also be changed by the changes of window stacks.\n
                  Trial for choosing a proper grab mode will be needed.
 * @pre This API must be called after the window 'win' has been mapped
 * @post This API adds/changes the window property related to grabbed key
 * @see utilx_ungrab_key
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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・
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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・
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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・
	return 0;
  }
  @endcode
 */
int utilx_grab_key (Display* dpy, Window win, const char* key_name, int grab_mode);

/**
 * @fn int utilx_ungrab_key (Display* dpy, Window win, const char* key_name)
 * @brief Ungrabs a key specfied by key_name for win
 *
 * This function releases the already established grab of the specfied key for the specified window.\n
 * Once the grab of the key was released, delivery of the key events for the specfied window is going to be stopped.
 *
 * This function is synchronous.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window to grab a key
 * @param[in] key_name Name of a key in string (ex> KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_SEND and so on)
 * @return 0 on Success, otherwise Fail
 * @remark No additional information
 * @pre This API must be called after the window 'win' has been mapped
 * @post This API changes/removes the window property related to grabbed key
 * @see utilx_grab_key
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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・
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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・

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

	utilx_ungrab_key(disp, win, KEY_POWER);//Ungrab whenever you want to ・
	return 0;
  }
  @endcode
 */
int utilx_ungrab_key (Display* dpy, Window win, const char* key_name);

/**
 * @fn int utilx_get_key_status(Display* dpy, char *key_name)
 * @brief Gets a status of a key specified by key_name
 *
 * This function gets a status of a key.\n
 * ex>UTILX_KEY_STATUS_PRESSED, UTILX_KEY_STATUS_RELEASED and UTILX_KEY_STATUS_UNKNOWN
 *
 * This function is synchronous.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] key_name Name of a key in string (ex> KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_SEND and so on)
 * @return 0 on Success, otherwise Fail
 * @remark No additional information
 * @pre This API must be called for H/W keys specified in this header file(utilX.h).
 * @par Example (using X11 APIs)
  @code

  #include <X11/Xlib.h>
  #include <utilX.h>

  int main()
  {
	Display *disp = XOpenDisplay(NULL);
	Utilx_Key_Status status;

	status = utilx_get_key_status(disp, KEY_PLAYCD);

	switch( status )
	{
		case UTILX_KEY_STATUS_PRESSED:
			//The key is pressed.
			break;

		case UTILX_KEY_STATUS_RELEASED:
			//The key is released.
			break;

		case UTILX_KEY_STATUS_UNKNOWN:
		default:
			//The key status is unknown;
			break;
	}

	return 0;
  }

  @endcode
   * @par Example (using EFL APIs)
  @code

  #include <utilX.h>
  #include <Ecore_Evas.h>
  #include <Ecore_X.h>

  int main()
  {
	...

	Ecore_X_Display* disp = ecore_x_display_get();
	Utilx_Key_Status status;

	status = utilx_get_key_status(disp, KEY_PLAYCD);

	switch( status )
	{
		case UTILX_KEY_STATUS_PRESSED:
			//The key is pressed.
			break;

		case UTILX_KEY_STATUS_RELEASED:
			//The key is released.
			break;

		case UTILX_KEY_STATUS_UNKNOWN:
		default:
			//The key status is unknown;
			break;
	}
	return 0;
  }
  @endcode
 */
Utilx_Key_Status utilx_get_key_status(Display* dpy, char *key_name);

/* Window Effect APIs */
/**
 * @fn void utilx_set_window_effect_state(Display* dpy, Window win, int state)
 * @brief Sets a window's effect state ( enable or disable )
 *
 * This function sets window's effect state. if effect is not enabled by composite manager, \n
 * window's effect could not be enabled.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window handle
 * @param[in] state Enables/disables the window effect
 * @remark This is used only client window. ( not root window )
 * @pre This api must be called before fist show ( XMapWindow Event ).
 * @post This changes Client Window's Effect related property.
 * @see utilx_get_window_effect_state
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;
  Window root, win;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  win = XCreateSimpleWindow (dpy, root, 0, 0, 480, 800, 2, BlackPixel (dpy,0), WhitePixel(dpy,0));

  // Sets a window's effect state to enable ( enable : 1, disable 0 )
  utilx_set_window_effect_state(dpy, win, 1);

  XMapWindow (dpy, win);
  ...
  @endcode
 */
void utilx_set_window_effect_state(Display* dpy, Window win, int state);

/**
* @fn int utilx_get_window_effect_state(Display* dpy, Window win)
* @brief Gets a window's effect state ( enable or disable )
*
* This function returns windows's effect state.\n
* If effect is not enabled by composite manager, then this return value is unusable or meanless.
*
* This function is a asynchronous call.
*
* @param[in] dpy Specifies the connection to the X server
* @param[in] win Specifies the window handle
* @return Current window effect state
* @remark This is used only client window. ( not root window )
* @pre This api does not require any pre-condition.
* @post This api does not change any condition.
* @see utilx_set_window_effect_state
* @par Example
 @code
 #include <X11/Xlib.h>
 #include <utilX.h>
 ...

 Display* dpy;
 Window root, win;

 dpy = XOpenDisplay (NULL);
 root = XDefaultRootWindow (dpy);

 win = XCreateSimpleWindow (dpy, root, 0, 0, 480, 800, 2, BlackPixel (dpy,0), WhitePixel(dpy,0));

 XMapWindow (dpy, win);

 // Gets a window's effect state ( enable : 1, disable 0 )
 printf( "current window's effect state = %d\n", utilx_get_window_effect_state(dpy, win) ) ;
 ...
 @endcode
*/
int utilx_get_window_effect_state(Display* dpy, Window win);

/**
 * @fn void utilx_show_fake_effect(Display* dpy, Window win, char *fake_image_file)
 * @brief Shows a window's "fake show effect" animation
 *
 * This function show's application fake show image.\n
 * This function is only used by application launching program.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the root window handle
 * @param[in] fake_image_file Specifies the fake window image and file format is png type.
 * @remark This is used only menu-screen window.
 * @pre  This api must be called before client's fist show ( XMapWindow Event ). you must call this api then run application.
 * @post This changes root window's fake effect related property.
 * @see utilx_hide_fake_effect
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;
  Window root;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  // Shows a window's "fake show effect" animation, and if you want to see animation, /root/fake_window_image.png file must be exited.
  utilx_show_fake_effect( dpy, root, "/root/fake_window_image.png");
   ...
  @endcode
 */
void utilx_show_fake_effect(Display *dpy, Window win, char *fake_image_file);

/**
 * @fn void utilx_hide_fake_effect(Display* dpy, Window win)
 * @brief Shows a window's "fake hide effect" animation, and this animation uses "fake show effect" 's window image.
 *
 * This function shoes a window's fake hide effect.\n
 * This function is only used by application launching program.\n
 * When application was not executed by any error.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the root window handle
 * @remark This is used only menu-screen window.
 * @pre This api must be called after "utilx_show_fake_effect()".
 * @post This changes root window's fake effect related property.
 * @see utilx_show_fake_effect
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;
  Window root;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  // Shows a window's "fake hide effect" animation. and if you wnat to see animation, utilx_show_fake_effect() function must be excuted before utilx_show_fake_effect()
  // and if real window is showed , then fake hide effect could not be showed.
  utilx_hide_fake_effect( dpy, root );
   ...
  @endcode
 */
void utilx_hide_fake_effect(Display *dpy, Window win);

/**
 * @fn void utilx_set_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type, Utilx_Effect_Style style)
 * @brief Sets a window's effect style with effect type.
 *
 * This function sets a window's effect style with effect type.\n
 * Default Window Effect is setted by Window Type and Window Class.\n
 * And then, you could change custom effecct.\n
 * Custom Effect is available max 10. ( CUSTOM0 ~ CUSTOM9 )\n
 * If you didn't set custom effect, then compositing window manger provides Default Window Effect.\n
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window handle
 * @param[in] type Specifies the window's effect type ( ex. UTILX_EFFECT_TYPE_MAP, UTILX_EFFECT_TYPE_UNMAP, etc )
 * @param[in] style Specifies  the window's effect style ( ex. UTILX_EFFECT_STYLE_DEFAULT, UTILX_EFFECT_STYLE_NONE, UTILX_EFFECT_STYLE_CUSTOM0, etc )
 * @remark This is used only client window. ( not root window )
 * @pre This api does not require any pre-condition.
 * @post This changes window's effect type related property ( _NET_CM_WINDOW_EFFECT_TYPE  ).
 * @see utilx_get_window_effect_style
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;
  Window win, root ;
  unsigned long black, white;

  dpy = XOpenDisplay(NULL) ;

  black = BlackPixel(dpy, 0);
  white = WhitePixel(dpy, 0);

  root = XDefaultRootWindow (dpy);
  win = XCreateSimpleWindow ( dpy, root, 0, 0, 100, 100, 2, BlackPixel (d,0), WhitePixel(d,0) );

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_MAP, UTILX_EFFECT_STYLE_CUSTOM0); //  window's show effet type change to UTILX_EFFECT_STYLE_CUSTOM0

  XMapWindow(dpy, win);

  ...

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_UNMAP, UTILX_EFFECT_STYLE_CUSTOM0); // window's hide effet type change to UTILX_EFFECT_STYLE_CUSTOM0

  XUnmapWindow (dpy, win);

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_MAP, UTILX_EFFECT_STYLE_DEFAULT); // window's show effet type change to UTILX_EFFECT_STYLE_DEFAULT
  XMapWindow (dpy, win);

  ...

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_UNMAP, UTILX_EFFECT_STYLE_DEFAULT); // window's hide effet type change to UTILX_EFFECT_STYLE_DEFAULT
  XUnmapWindow (dpy, win);

  ...

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_MAP, UTILX_EFFECT_STYLE_NONE); // window's show effet type change to UTILX_EFFECT_STYLE_NONE
  XMapWindow (dpy, win);

  ...

  utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_UNMAP, UTILX_EFFECT_STYLE_NONE); // window's hide effet type change to UTILX_EFFECT_STYLE_NONE
  XUnmapWindow (dpy, win);

  ...
  @endcode
 */
void utilx_set_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type, Utilx_Effect_Style style);

/**
 * @fn Utilx_Effect_Style utilx_get_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type)
 * @brief Gets a window's effect style with effect type.
 *
 * This function gets a window's effect style with effect type.\n
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window handle
 * @param[in] type Specifies the window's effect type ( ex. UTILX_EFFECT_TYPE_MAP, UTILX_EFFECT_TYPE_UNMAP, etc )
 * @return Current window's effect style ( ex. UTILX_EFFECT_STYLE_DEFAULT, UTILX_EFFECT_STYLE_NONE, UTILX_EFFECT_STYLE_CUSTOM0, etc )
 * @remark This is used only client window. ( not root window )
 * @pre This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_set_window_effect_style
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;
  Window win, root ;
  unsigned long black, white;
  Utilx_Effect_Style style;

  dpy = XOpenDisplay(NULL) ;

  black = BlackPixel(dpy, 0);
  white = WhitePixel(dpy, 0);

  root = XDefaultRootWindow (dpy);
  win = XCreateSimpleWindow ( dpy, root, 0, 0, 100, 100, 2, BlackPixel (d,0), WhitePixel(d,0) );

  style = utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_MAP); //  get effect style with window's show effet type

  ...

  style = utilx_set_window_effect_style(dpy, win, UTILX_EFFECT_TYPE_UNMAP); //  get effect style with window's show effet type

  ...
  @endcode
 */
Utilx_Effect_Style utilx_get_window_effect_style(Display* dpy, Window win, Utilx_Effect_Type type);

/**
 * @fn void utilx_set_window_opaque_state (Display* dpy, Window win, int opaque)
 * @brief Sets the window's opaque state
 *
 * This function sets window's visibility to opaque even if the window is an alpha window.
 * This function is available only alpha window.
 * An alpha window's default opaque state is UTILX_OPAQUE_STATE_OFF.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the window handle
 * @param[in] state Specifies whether the window set a visible state to opaque(UTILX_OPAQUE_STATE_ON) or not(UTILX_OPAQUE_STATE_OFF)
 * @return 1 on Success, otherwise Fail
 * @remark This is used only alpha window.
 * @pre None
 * @post
 * @see
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
 * @fn int utilx_set_screen_capture(Display* dpy, int enable)
 * @brief Specifies whether the screen capture functionality is enable or not.
 *
 * This function makes the screen capture functionality of CBHM enable or disable.
 * CBHM = Clipboard History Manager.
 *
 * This function is synchronous.
 *
 * @param[in] dpy    Specifies the connection to the X server
 * @param[in] enable Specifies the window handle. (1:Enable, 0:Disable)
 * @pre This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_get_screen_capture
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;

  dpy = XOpenDisplay(NULL) ;

  utilx_set_screen_capture (dpy, 1);

  ...
  @endcode
 */
int utilx_set_screen_capture(Display* dpy, int enable);

/**
 * @fn int utilx_get_screen_capture(Display* dpy, int enable)
 * @brief Gets whether the screen capture functionality is enable or not.
 *
 * This function gets whether the screen capture functionality of CBHM is enable or not.
 * CBHM = Clipboard History Manager.
 *
 * This function is synchronous.
 *
 * @param[in] dpy    Specifies the connection to the X server
 * @pre This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_set_screen_capture
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;
  int enable;

  dpy = XOpenDisplay(NULL) ;

  enable = utilx_set_screen_capture (dpy);

  ...
  @endcode
 */
int utilx_get_screen_capture(Display* dpy);

/**
 * @fn void utilx_set_window_cardinal_property(Display* dpy, Window win, Atom atom, unsigned int *value)
 * @brief Sets the cardinal property to Window
 *
 * This function Sets the cardinal property to Window.
 *
 * This function is synchronous.
 *
 * @param[in] dpy    Specifies the connection to the X server
 * @param[in] win    Specifies the window handle
 * @param[in] atom   Specifies the atom of cardinal property
 * @param[in] value  the value of cardinal property to set.
 * @pre This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_get_window_cardinal_property
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;
  Window root;
  Atom atom = None;
  int value = 1;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  atom = XInternAtom(dpy, "TEST_ATOM", False);

  utilx_set_window_cardinal_property (dpy, root, atom, (unsigned int*)&value);

  ...
  @endcode
 */
void utilx_set_window_cardinal_property(Display* dpy, Window win, Atom atom, unsigned int *value);

/**
 * @fn int utilx_get_window_cardinal_property(Display* dpy, Window win, Atom atom, unsigned int *value)
 * @brief Gets the value of cardinal property.
 *
 * This function gets the value of cardinal property.
 *
 * This function is synchronous.
 *
 * @param[in] dpy    Specifies the connection to the X server
 * @param[in] win    Specifies the window handle
 * @param[in] atom   Specifies the atom of cardinal property
 * @param[out] value  the value of cardinal property to get.
 * @pre This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_set_window_cardinal_property
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <utilX.h>
  ...

  Display *dpy ;
  Window root;
  Atom atom = None;
  int value;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  atom = XInternAtom(dpy, "TEST_ATOM", False);

  if (utilx_set_window_cardinal_property (dpy, root, atom, (unsigned int*)&value) > 0)
  {
    success;
  }

  ...
  @endcode
 */
int utilx_get_window_cardinal_property(Display* dpy, Window win, Atom atom, unsigned int *value);

/**
 * @fn void utilx_show_capture_effect(Display *dpy, Window win )
 * @brief Shows a capture effect animation
 *
 * This function show capture effect animation.\n
 * This function is only used by Screen Capture Application.
 *
 * This function is a asynchronous call.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] win Specifies the root window handle
 * @remark This is used only screen capture application.
 * @pre  This api does not require any pre-condition.
 * @post This api does not change any condition.
 * @see utilx_set_screen_capture
 * @par Example
  @code
  #include <X11/Xlib.h>
  #include <utilX.h>
  ...

  Display* dpy;
  Window root;

  dpy = XOpenDisplay (NULL);
  root = XDefaultRootWindow (dpy);

  // Shows a  Shows a capture effect animation
  utilx_show_capture_effect( dpy, root);
   ...
  @endcode
 */
void utilx_show_capture_effect(Display *dpy, Window win );

/**
 * @fn void* utilx_create_screen_shot (Display* dpy, int width, int height)
 * @brief Create a screenshot image.
 *
 * This function create a screenshot image.\n
 * To use this function, you should get the permission first. Once this functions
 * is called, utilx_release_screen_shot should be called after it.
 *
 * @param[in] dpy Specifies the connection to the X server
 * @param[in] width Specifies the root window handle
 * @param[in] height Specifies the root window handle
 * @remark You should get the permission to use.
 * @post This api does not change any condition.
 * @see utilx_release_screen_shot
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
 * @fn void  utilx_release_screen_shot (void)
 * @brief Release screenshot resources.
 *
 * This function release screenshot resources.\n
 * utilx_release_screen_shot should be called once utilx_create_screen_shot is
 * called.
 *
 * @see utilx_create_screen_shot
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

/**
 * @fn void  utilx_set_fb_visible (Display* dpy, Utilx_Fb_Type fb_type, Bool visible)
 * @brief Set fb's visibility.
 *
 * This function can make a framebuffer visible or non-visible. \n
 * By the way, in case of UTILX_FB_TYPE_UI, if there is the request for UI update,
 * the visibility of UI framebuffer will be changed from False to True automatically.
 * Please note this.
 *
 * @param[in] dpy      Specifies the connection to the X server
 * @param[in] fb_type  Specifies the fb type to set visibility of a framebuffer
 * @param[in] visible  Visible/Non-Visible
 * @see utilx_get_fb_visible
 * @par Example
  @code
  #include <utilX.h>
  ...
  Display* dpy = XOpenDisplay (NULL);

  // Hide the UI framebuffer of main lcd.
  utilx_set_fb_visible (dpy, UTILX_FB_TYPE_UI, False);
  ...
  @endcode
 */
void  utilx_set_fb_visible (Display* dpy, Utilx_Fb_Type fb_type, Bool visible);

/**
 * @fn Bool  utilx_get_fb_visible (Display* dpy, Utilx_Fb_Type fb_type)
 * @brief Get framebuffer's visibility.
 *
 * This function get the visibility of a framebuffer. \n
 *
 * @param[in] dpy       Specifies the connection to the X server
 * @param[in] fb_type   Specifies the fb type to get visibility of a framebuffer
 * @return Current visibility of a framebuffer
 * @see utilx_set_fb_visible
 * @par Example
  @code
  #include <utilX.h>
  ...
  Display* dpy = XOpenDisplay (NULL);
  Bool visible;

  visible = utilx_get_fb_visible (dpy, UTILX_FB_TYPE_UI);
  ...
  @endcode
 */
Bool  utilx_get_fb_visible (Display* dpy, Utilx_Fb_Type fb_type);

/**
 * @fn void  utilx_set_video_offset (Display* dpy, int x, int y)
 * @brief Set the offset of video.
 *
 * This function sets the offset of video layer. \n
 *
 * @param[in] dpy   Specifies the connection to the X server
 * @param[in] x     x offset
 * @param[in] y     y offset
 * @par Example
  @code
  #include <utilX.h>
  ...
  Display* dpy = XOpenDisplay (NULL);

  utilx_set_video_offset (dpy, 0, 100);
  ...
  @endcode
 */
void  utilx_set_video_offset (Display* dpy, int x, int y);

#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif /* __SAMSUNG_LINUX_UTIL_X11_H__ */

