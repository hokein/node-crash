#include "third_party/node/src/node.h"
#include "third_party/node/src/env.h"
#include "third_party/node/src/env-inl.h"
#include "third_party/node/deps/v8/include/v8.h"
#include "third_party/node/deps/v8/include/libplatform/libplatform.h"

int main(int argc, char *argv[]) {
  int exec_argc;
  const char** exec_argv;
  node::Init(&argc, const_cast<const char**>(argv), &exec_argc, &exec_argv);

  // Initialize v8.
  auto* v8_platform = v8::platform::CreateDefaultPlatform();
  v8::V8::InitializePlatform(v8_platform);
  v8::V8::Initialize();

  v8::Isolate::CreateParams params;
  node::ArrayBufferAllocator allocator;
  params.array_buffer_allocator = &allocator;
  v8::Isolate* isolate = v8::Isolate::New(params);
  {
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);
    node::IsolateData* isolate_data =
        node::CreateIsolateData(isolate, uv_default_loop());
    auto* env = node::CreateEnvironment(isolate_data,
                                        context,
                                        argc,
                                        argv,
                                        exec_argc,
                                        exec_argv);
    node::LoadEnvironment(env);
    node::FreeEnvironment(env);
    node::FreeIsolateData(isolate_data);
  }
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete v8_platform;
  return 0;
  // return node::Start(argc, argv); // OK: works fine.
}
