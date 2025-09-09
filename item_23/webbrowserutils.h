#pragma once
#include "webbrowser.h"

namespace WebBrowserStuff
{

void clearBrowser(WebBrowser& wb)
{
    std::cout << "Calling clearBrowser.\n";
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}

} // namespace WebBrowserStuff