#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class X11Utils
{
private:
    Display *display = XOpenDisplay(NULL);

public:
    bool keyDown(int keyCode)
    {
        char keys_return[32];
        XQueryKeymap(display, keys_return);
        KeyCode kc2 = XKeysymToKeycode(display, keyCode);
        bool buttonDown = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
        return buttonDown;
    }
    void mouseClick(int button)
    {
        XEvent event;
        memset(&event, 0x00, sizeof(event));
        event.type = ButtonPress;
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
        event.xbutton.subwindow = event.xbutton.window;
        while (event.xbutton.subwindow)
        {
            event.xbutton.window = event.xbutton.subwindow;
            XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
        }
        if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
            fprintf(stderr, "Error\n");
        XFlush(display);
        usleep(100000);
        event.type = ButtonRelease;
        event.xbutton.state = 0x100;
        if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
            fprintf(stderr, "Error\n");
        XFlush(display);
    }
};