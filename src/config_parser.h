/*
 * BSD 2-Clause License
 * Copyright (c) 2024, Yazeed Alharthi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	  1. Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	  2. Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ZWM_CONFIG_PARSER_H
#define ZWM_CONFIG_PARSER_H

#include "type.h"

#define MAX_RULES (2 << 2) // 2 << 2 = 8

// extern _key__t **conf_keys;
// extern int		 _entries_;
// extern rule_t  **_rules;
// extern int		 rule_index;
extern rule_t	  *rule_head;
extern conf_key_t *key_head;

// clang-format off
rule_t *get_window_rule(xcb_window_t win);
int     load_config(config_t *c);
void    free_keys(void);
void    free_rules(void);
int     reload_config(config_t *c);
// clang-format on
#endif // ZWM_CONFIG_PARSER_H
#include <X11/X.h>
#include <X11/keysym.h>
#include <time.h>

#ifndef CONFIG_H
#define CONFIG_H

// Moody Settings
#define WM_NAME "moody" // Set wm name for neofetch to use
#define MAX_WORKSPACES 9

// Modifier keys
#define MODIFIER Mod1Mask // Mod1Mask = alt, Mod4Mask = Super key(Windows key)

// Moving and Resizing buttons
#define MOVE_BUTTON Button1   // left mouse button
#define RESIZE_BUTTON Button3 // right mouse button

// Windows
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 800
#define MAX_WINDOWS 500 // Set max windows per workspace
#define BORDER_WIDTH 4
#define BORDER_COLOR "#ffffff"          // Set active border color to white
#define INACTIVE_BORDER_COLOR "#333333" // Set inactive border color to grey

// Gaps
#define INNER_GAP 20 // Gap between windows
#define OUTER_GAP 30 // Gap between windows and screen edge

// Keybindings

// Dont care about this
typedef struct {
  KeySym keysym;
  unsigned int modifier;
  const char *command; // Command to execute, NULL for workspace switching
  int workspace;       // Workspace number, -1  for now workspace change
} Keybinding;

// Care about this :)
#define KILL_KEY XK_q        // mod+q for killing the current window
#define NEXT_WINDOW_KEY XK_k // mod+k to focus next window
#define PREV_WINDOW_KEY XK_j // mod+j to focus previous window

static Keybinding keybindings[] = {
    {XK_Return, MODIFIER, "xterm", -1}, // mod+return to open xterm (terminal)
    {XK_b, MODIFIER, "firefox", -1},    // mod+b to open firefox
    {XK_space, MODIFIER, "rofi -show drun",
     -1}, // mod+space to open rofi (app launcher)

    {XK_F12, MODIFIER, "pactl set-sink-volume @DEFAULT_SINK@ +5%",
     -1}, // mod+f12 to increase volume by 5%
    {XK_F11, MODIFIER, "pactl set-sink-volume @DEFAULT_SINK@ -5%",
     -1}, // mod+f11 to increase volume by 5%
    {XK_F10, MODIFIER, "pactl set-sink-mute @DEFAULT_SINK@ toggle",
     -1}, // mod+f10 to mute

    // Quit moody
    {XK_c, MODIFIER | ShiftMask, "killall moody",
     -1}, // mod+shift+c to quit moody

    // Workspace
    // Switching
    {XK_1, MODIFIER, NULL, 0}, // mod+1 to switch to workspace 0
    {XK_2, MODIFIER, NULL, 1}, // mod+2 to switch to workspace 1
    {XK_3, MODIFIER, NULL, 2}, // mod+3 to switch to workspace 2
    {XK_4, MODIFIER, NULL, 3}, // mod+4 to switch to workspace 3
    {XK_5, MODIFIER, NULL, 4}, // mod+5 to switch to workspace 4
    {XK_6, MODIFIER, NULL, 5}, // mod+6 to switch to workspace 5
    {XK_7, MODIFIER, NULL, 6}, // mod+7 to switch to workspace 6
    {XK_8, MODIFIER, NULL, 7}, // mod+8 to switch to workspace 7
    {XK_9, MODIFIER, NULL, 8}, // mod+9 to switch to workspace 8

    // Moving window to
    {XK_1, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 0)",
     -1}, // mod+shift+1 to move window to workspace 0
    {XK_2, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 1)",
     -1}, // mod+shift+2 to move window to workspace 1
    {XK_3, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 2)",
     -1}, // mod+shift+3 to move window to workspace 2
    {XK_4, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 3)",
     -1}, // mod+shift+4 to move window to workspace 3
    {XK_5, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 4)",
     -1}, // mod+shift+5 to move window to workspace 4
    {XK_6, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 5)",
     -1}, // mod+shift+6 to move window to workspace 5
    {XK_7, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 6)",
     -1}, // mod+shift+7 to move window to workspace 6
    {XK_8, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 7)",
     -1}, // mod+shift+8 to move window to workspace 7
    {XK_9, MODIFIER | ShiftMask, "move_window_to_workspace(dpy, 8)",
     -1}, // mod+shift+9 to move window to workspace 8
};

#define NUM_KEYBINDINGS (sizeof(keybindings) / sizeof(Keybinding))

#endif
