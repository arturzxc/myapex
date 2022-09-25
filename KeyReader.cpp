#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace kr
{
    bool leftShiftKeyDown()
    {
        Display *dpy = XOpenDisplay(NULL);
        char keys_return[32];
        XQueryKeymap(dpy, keys_return);
        KeyCode kc2 = XKeysymToKeycode(dpy, XK_Shift_L);
        bool shiftDown = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
        XCloseDisplay(dpy);
        return shiftDown;
    }
};
