// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/renderer/extensions/web_request_custom_bindings.h"

#include <string>

#include "base/string_number_conversions.h"
#include "grit/renderer_resources.h"
#include "v8/include/v8.h"

namespace extensions {

WebRequestCustomBindings::WebRequestCustomBindings(
    int dependency_count,
    const char** dependencies)
    : ChromeV8Extension(
          "extensions/web_request_custom_bindings.js",
          IDR_WEBREQUEST_CUSTOM_BINDINGS_JS,
          dependency_count,
          dependencies,
          NULL) {}

// Attach an event name to an object.
static v8::Handle<v8::Value> GetUniqueSubEventName(const v8::Arguments& args) {
  static int next_event_id = 0;
  DCHECK(args.Length() == 1);
  DCHECK(args[0]->IsString());
  std::string event_name(*v8::String::AsciiValue(args[0]));
  std::string unique_event_name =
      event_name + "/" + base::IntToString(++next_event_id);
  return v8::String::New(unique_event_name.c_str());
}

v8::Handle<v8::FunctionTemplate> WebRequestCustomBindings::GetNativeFunction(
    v8::Handle<v8::String> name) {
  if (name->Equals(v8::String::New("GetUniqueSubEventName")))
    return v8::FunctionTemplate::New(GetUniqueSubEventName);

  return ChromeV8Extension::GetNativeFunction(name);
}

}  // extensions

