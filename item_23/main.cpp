#include "webbrowser.h"
#include "webbrowserutils.h"

int main()
{
    using namespace WebBrowserStuff;

    WebBrowser wb;

    std::cout << "--- Using member function ---\n";
    wb.clearEverything();

    std::cout << "\n--- Using non-member non-friend function ---\n";
    clearBrowser(wb);

    return 0;
}


/*
Non-member non-friend convenience function is the preferred approach.
This approach is better because:
1. It does not increase access to WebBrowser's private members (better encapsulation).
2. Convenience functions can be grouped into separate headers/namespaces, reducing compilation dependencies.
3. Clients can extend functionality by adding more non-member functions to the namespace (greater flexibility).
*/