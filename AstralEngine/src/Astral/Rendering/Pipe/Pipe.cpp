#include "Common.h"
#include "Pipe.h"
#include "Invoker/Invoker.h"
#include "Executor/Executor.h"
#include "Astral/App/Application/StartupConfig.h"


namespace Astral::Render {
    Pipe::Pipe() {}

    Invoker Pipe::CreateInvoker() {
        return Invoker(&registry, &commands);
    }

    Executor Pipe::CreateExecutor(App::Window* window, API graphics_api, const App::StartupConfig& config) {
        return Executor(&registry, &commands, window, graphics_api, config);
    }
}