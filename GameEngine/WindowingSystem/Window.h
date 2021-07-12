//
// Created by lucai on 10.07.2021.
//

#ifndef INC_3DGAME_WINDOW_H
#define INC_3DGAME_WINDOW_H

#pragma once

#include <Windows.h>

class Window {
public:
    // Initialize the window
    Window();

private:
    bool broadcast();

public:
    // Checks if the window is running
    bool isRunning();

    RECT getClientWindowRect();

    static RECT getSizeScreen();

    // EVENTS
    virtual void onCreate();

    virtual void onUpdate();

    virtual void onDestroy();

    virtual void onFocus();

    virtual void onKillFocus();

    virtual void onSize();

    // Release the window
    ~Window();

protected:
    HWND m_hwnd = nullptr;
    bool m_is_running = true;
    bool m_is_init = false;

};

#endif //INC_3DGAME_WINDOW_H
