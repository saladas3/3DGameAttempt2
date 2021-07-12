//
// Created by lucai on 10.07.2021.
//

#include "Window.h"
#include <stdexcept>

// Main message handler for the program
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

Window::Window() {
    // Setting up WNDCLASSEX object - holds information for the window class
    WNDCLASSEX wc;

    // Clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = nullptr;
    wc.lpszClassName = (LPCSTR)"MyWindowClass";
    wc.lpszMenuName = (LPCSTR)"";
    wc.style = NULL;
    wc.lpfnWndProc = WndProc;

    if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
        throw std::exception("Window not created successfully");

    // Creation of the window
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, (LPCSTR)"MyWindowClass",
                              (LPCSTR)"Yes Hello",
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
                              nullptr, nullptr, nullptr, nullptr);

    // If the creation fail return false
    if (!m_hwnd)
        throw std::exception("Window not created successfully");

    // Show up the window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    // Set this flag to true to indicate that the window is initialized and running
    m_is_running = true;
}

bool Window::broadcast() {
    MSG msg;

    if (!this->m_is_init) {
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR) this);
        this->onCreate();
        this->m_is_init = true;
    }

    if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    this->onUpdate();

    Sleep(1);

    return true;
}

bool Window::isRunning() {
    if (m_is_running)
        broadcast();
    return m_is_running;
}

RECT Window::getClientWindowRect() {
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    ::ClientToScreen(this->m_hwnd, (LPPOINT) &rc.left);
    ::ClientToScreen(this->m_hwnd, (LPPOINT) &rc.right);
    return rc;
}

RECT Window::getSizeScreen() {
    RECT rc;
    rc.right = ::GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);
    return rc;
}

void Window::onCreate() {

}

void Window::onUpdate() {

}

void Window::onDestroy() {
    m_is_running = false;
}

void Window::onFocus() {

}

void Window::onKillFocus() {

}

void Window::onSize() {

}

Window::~Window() = default;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CREATE: {
            // Event fired when the window is created
            // collected here..

            break;
        }
        case WM_SIZE: {
            // Event fired when the windows is resized
            auto *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (window) window->onSize();
            break;
        }
        case WM_SETFOCUS: {
            // Event fired when the window get focus
            auto *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (window) window->onFocus();
            break;
        }
        case WM_KILLFOCUS: {
            // Event fired when the window lost focus
            auto *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            window->onKillFocus();
            break;
        }
        case WM_DESTROY: {
            // Event fired when the window is destroyed
            auto *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            window->onDestroy();
            ::PostQuitMessage(0);
            break;
        }

        default:
            return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
}
