#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>
#include <windows.h>

#include "flutter_window.h"
#include "utils.h"


int main(int argc, char** argv) {
  return wWinMain(nullptr, nullptr, nullptr, SW_SHOW);
}

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
                      _In_ wchar_t *command_line, _In_ int show_command) {

    // ======= add =======
    // Check if we're running in cmd mode
    bool is_cmd_mode = false;
    int argc;
    wchar_t** argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);
    if (argv != nullptr) {
      for (int i = 1; i < argc; i++) {
        std::wstring arg = argv[i];
        if (arg == L"-cmd") {
          is_cmd_mode = true;
          break;
        }
      }
      ::LocalFree(argv);
    }

    // For cmd mode, attach to the parent console
    if (is_cmd_mode) {
      // Try to attach to the parent console
      if (!::AttachConsole(ATTACH_PARENT_PROCESS)) {
          // If no parent console, create a new one
          CreateAndAttachConsole();
      }
      // Resync output streams
      FlutterDesktopResyncOutputStreams();
    } else {
    // For UI mode, attach to console only if present or debugging
      if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
        CreateAndAttachConsole();
      }
    }

    // ===================

  // Attach to console when present (e.g., 'flutter run') or create a
  // new console when running with a debugger.
  //if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
  //  CreateAndAttachConsole();
  //}

  // Initialize COM, so that it is available for use in the library and/or
  // plugins.
  ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

  flutter::DartProject project(L"data");

  std::vector<std::string> command_line_arguments =
      GetCommandLineArguments();

  project.set_dart_entrypoint_arguments(std::move(command_line_arguments));

  FlutterWindow window(project);
  Win32Window::Point origin(10, 10);
  Win32Window::Size size(800, 720);
  if (!window.Create(L"danmakufactory_flutter", origin, size)) {
    return EXIT_FAILURE;
  }
  window.SetQuitOnClose(true);

  ::MSG msg;
  while (::GetMessage(&msg, nullptr, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }

  ::CoUninitialize();
  return EXIT_SUCCESS;
}
