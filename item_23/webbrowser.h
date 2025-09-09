#pragma once
#include <iostream>
#include <string>

namespace WebBrowserStuff
{

class WebBrowser
{
public:
    void clearCache() {std::cout << "Cache cleared.\n";}
    void clearHistory()
    {
        visits = 0;
        std::cout << "History cleared.\n";
    }
    void removeCookies(){std::cout << "Cookies removed.\n";}
    void clearEverything()
    {
        std::cout << "Called clearEverything.\n";
        clearCache();
        clearHistory();
        removeCookies();
    }
    void visitPage(){visits++;}
private:
    int visits{0};
};

} // namespace WebBrowserStuff
