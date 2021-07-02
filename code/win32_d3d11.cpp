// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "imgui.cpp"
#include "imgui_draw.cpp"
#include "imgui_widgets.cpp"
#include "imgui_tables.cpp"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_dx11.cpp"
#include "backends/imgui_impl_win32.cpp"
#include <d3d11.h>
#include <tchar.h>

#include "types.h"

struct Renderer
{
    ID3D11Device        *device;
    ID3D11DeviceContext *context;
    IDXGISwapChain      *swap_chain;

    ID3D11RenderTargetView  *render_target_rgb;
};

global b32 global_running;
global b32 global_error;
global u32 global_width = 1280;
global u32 global_height = 720;
global Renderer *global_renderer;
global ImGuiIO *io;

#if LP_DEBUG
#define Assert(expr) do {if(!(expr)) {*(int *)0 = 0;}} while(0)
#define AssertKeep(expr) Assert(expr)
#else
#define Assert(expr)
#define AssertKeep(expr)  {(expr);}
#endif

inline void d3d11_resize_render_targets()
{
    if (global_renderer->swap_chain && global_renderer->context) {
        global_renderer->context->OMSetRenderTargets(0, 0, 0);
        if (global_renderer->render_target_rgb)
            global_renderer->render_target_rgb->Release();

        global_renderer->swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

        ID3D11Resource  *backbuffer = 0;

        global_renderer->swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backbuffer);
        global_renderer->device->CreateRenderTargetView(backbuffer, 0, &global_renderer->render_target_rgb);

        backbuffer->Release();

        // ===========================================================
        // Viewport set-up
        // ===========================================================
        D3D11_VIEWPORT viewport = {};
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width  = (r32)global_width;
        viewport.Height = (r32)global_height;
        viewport.MinDepth = 0.f;
        viewport.MaxDepth = 1.f;
        global_renderer->context->RSSetViewports(1, &viewport);
    }
}

LRESULT CALLBACK window_proc(
    HWND   handle,
    UINT   message,
    WPARAM w,
    LPARAM l
)
{
    LRESULT result = 1;
    switch(message)
    {
        case WM_LBUTTONDOWN: { io->MouseDown[0] = 1; } break;
        case WM_LBUTTONUP:   { io->MouseDown[0] = 0; } break;
        case WM_RBUTTONDOWN: { io->MouseDown[1] = 1; } break;
        case WM_RBUTTONUP:   { io->MouseDown[1] = 0; } break;
        case WM_MBUTTONDOWN: { io->MouseDown[2] = 1; } break;
        case WM_MBUTTONUP:   { io->MouseDown[2] = 0; } break;
        case WM_MOUSEWHEEL: 
        {
            io->MouseWheel = (r32)GET_WHEEL_DELTA_WPARAM(w);
        } break;

        case WM_KEYDOWN:
        {
            if (w < 256)
            {
                if (io)  io->KeysDown[w] = 1;
            }
        } break;

        case WM_KEYUP:
        {
            if (w < 256)
            {
                if (io)  io->KeysDown[w] = 0;
            }
        } break;

        case WM_CLOSE:
        {
            DestroyWindow(handle);
        } break;

        case WM_DESTROY:
        {
            global_running = false;
            PostQuitMessage(0);
        } break;

        case WM_SIZE:
        {
            global_width = LOWORD(l);
            global_height = HIWORD(l);

            if (global_renderer)  d3d11_resize_render_targets();
        } break;

        // @todo: implement this
        case WM_SETCURSOR:
        {
            if (LOWORD(l) == HTCLIENT && ImGui_ImplWin32_UpdateMouseCursor())
            {}
            else if ((LOWORD(l) == HTRIGHT) || (LOWORD(l) == HTLEFT))
                SetCursor(LoadCursor(0, IDC_SIZEWE));
            else if ((LOWORD(l) == HTTOP) || (LOWORD(l) == HTBOTTOM))
                SetCursor(LoadCursor(0, IDC_SIZENS));
            else if ((LOWORD(l) == HTBOTTOMLEFT) || (LOWORD(l) == HTTOPRIGHT))
                SetCursor(LoadCursor(0, IDC_SIZENESW));
            else if ((LOWORD(l) == HTBOTTOMRIGHT) || (LOWORD(l) == HTTOPLEFT))
                SetCursor(LoadCursor(0, IDC_SIZENWSE));
            else
                result = 0;
        } break;

        case WM_CHAR:
        {
            if (w > 0 && w < 0x10000 && io)
            {
                io->AddInputCharacterUTF16((unsigned short)w);
            }
        } break;

        default:
        {
            result = DefWindowProcA(handle, message, w, l);
        } break;
    }
    return(result);
}

// Main code
int WinMain(HINSTANCE instance,
            HINSTANCE prev_instance,
            PSTR      command_line,
            INT       show_status)
{
    s64 performance_counter_frequency = 0;
    AssertKeep(QueryPerformanceFrequency((LARGE_INTEGER *)&performance_counter_frequency));
    // @todo make this hardware-dependant
    r32 target_ms_per_frame = 1.f/60.f;

    WNDCLASSA window_class = {};
    window_class.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW;
    window_class.lpfnWndProc = window_proc;
    //window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window_class.hInstance = instance;
    window_class.lpszClassName = "LPClass";
    ATOM Result = RegisterClassA(&window_class);

    RECT WindowDimensions = {0, 0, (s32)global_width, (s32)global_height};
    AdjustWindowRect(&WindowDimensions, WS_OVERLAPPEDWINDOW, FALSE);
    WindowDimensions.right -= WindowDimensions.left;
    WindowDimensions.bottom -= WindowDimensions.top;

    HWND main_window = CreateWindowA("LPClass", "Iziwallet beta 0.1",
                                     WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                     CW_USEDEFAULT, CW_USEDEFAULT,
                                     WindowDimensions.right,
                                     WindowDimensions.bottom,
                                     0, 0, instance, 0);

    if(main_window)
    {
        global_running = true;
        global_error = false;
        Renderer d11_renderer = {};
        global_renderer = &d11_renderer;

        DXGI_MODE_DESC display_mode_desc = {};
        //DisplayModeDescriptor.Width = global_width;
        //DisplayModeDescriptor.Height = global_height;
        display_mode_desc.RefreshRate = {60, 1};
        display_mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        display_mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
        display_mode_desc.Scaling = DXGI_MODE_SCALING_CENTERED;

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferDesc = display_mode_desc;
        swap_chain_desc.SampleDesc = {1, 0};
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = 2;
        swap_chain_desc.OutputWindow = main_window;
        swap_chain_desc.Windowed = true;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swap_chain_desc.Flags;

        D3D11CreateDeviceAndSwapChain(
            0,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            0,
            0,
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &d11_renderer.swap_chain,
            &d11_renderer.device,
            0,
            &d11_renderer.context
        );

        d3d11_resize_render_targets();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        //io->Fonts->AddFontFromFileTTF("fonts/Redaction.otf", 22.f);
        ImGui_ImplWin32_Init(main_window);
        ImGui_ImplDX11_Init(d11_renderer.device, d11_renderer.context);
        ImGui::StyleColorsLight();
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowRounding = 0.f;
        style.FrameRounding = 5.f;


        MSG message = {};
        s64 last_performance_counter = 0;
        s64 current_performance_counter = 0;
        AssertKeep(QueryPerformanceCounter((LARGE_INTEGER *)&last_performance_counter));
        while(global_running && !global_error)
        {
            AssertKeep(QueryPerformanceCounter((LARGE_INTEGER *)&current_performance_counter));
            r32 dtime = (r32)(current_performance_counter - last_performance_counter) / (r32)performance_counter_frequency;
            while(dtime <= target_ms_per_frame)
            {
                while(PeekMessageA(&message, main_window, 0, 0, PM_REMOVE))
                {
                    //                        case WM_MOUSEMOVE:
                    //                        {
                    //                            // @todo: doing the division here might cause problems if a window resize
                    //                            //        happens between frames.
                    //                            input.mouse.x = (r32)(((i16*)&Message.lParam)[0]) / global_width;
                    //                            input.mouse.y = (r32)(((i16*)&Message.lParam)[1]) / global_height;
                    //                        } break;
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                AssertKeep(QueryPerformanceCounter((LARGE_INTEGER *)&current_performance_counter));
                dtime = (r32)(current_performance_counter - last_performance_counter) / (r32)performance_counter_frequency;
            }

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            char text_buffer[500] = {};

            global_renderer->context->OMSetRenderTargets(1, &global_renderer->render_target_rgb, 0);

            v3 color = {1.f, 1.f, 1.f};//{0.06f, 0.3f, 0.45f});
            r32 rgba[] = {color.x, color.y, color.z, 1.f};
            d11_renderer.context->ClearRenderTargetView(d11_renderer.render_target_rgb, rgba);

            ImGui::Begin("IziWallet", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
            ImGui::SetWindowSize(ImVec2((r32)global_width, (r32)global_height));
            ImGui::SetWindowPos(ImVec2(0, 0));

            ImGui::Text("Hello");

            ImGui::End();

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            last_performance_counter = current_performance_counter;
            d11_renderer.swap_chain->Present(0, 0);
        }
    }
    else
    {
        // TODO: Logging
        return 1;
    }

    if (global_error)
    {
        return 1;
    }
    else
    {
	return 0;
    }
}