#pragma once

template <typename T, typename... Ts>
CefRefPtr<T> MakeCefRefPtr(Ts && ... args)
{
	return new T(std::forward<Ts>(args)...);
}