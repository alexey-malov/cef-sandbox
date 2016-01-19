// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"

class MyV8Handler : public CefV8Handler
{

private:
	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(MyV8Handler);

	virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override
	{
		if (arguments.size() == 1)
		{
			auto & arg0 = arguments.front();
			if (arg0->IsValid() && arg0->IsArray())
			{
				auto len = arg0->GetArrayLength();
				for (int i = 0; i < len; ++i)
				{
					arg0->SetValue(i, CefV8Value::CreateInt(i));
				}
			}
			retval = arg0;
		}
		return true;
	}

};

// Implement application-level callbacks for the browser process.
class SimpleApp
	: public CefApp
	, public CefBrowserProcessHandler
	, public CefRenderProcessHandler
{
public:
	SimpleApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE
	{
		return this;
	}

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override
	{
		browser;
		frame;
		context;
		auto global = context->GetGlobal();
		auto fn = CefV8Value::CreateFunction("my42", new MyV8Handler);
		global->SetValue("my42", fn, V8_PROPERTY_ATTRIBUTE_READONLY);
	}

		// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SimpleApp);
};



#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
