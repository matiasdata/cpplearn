#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>

// Fake Image class that might throw during loading
class Image
{
public:
    explicit Image(const std::string& filename)
    {
        if(filename == "bad")
        {
            throw std::runtime_error("Failed to load image: " + filename);
        }
        name = filename;
    }
    std::string getName() const {return name;}
private:
    std::string name;
};

class ImageGallery
{
public:
    // basic guarantee: exception safe but function may leave the object in a different state
    void addImage_basic(const std::string& filename)
    {
        images.push_back(std::make_shared<Image>(filename)); // may throw
        ++count;
    }
    // strong guarantee: exception safe and leaves the object unchanged in case of an exception
    void addImage_strong(const std::string& filename)
    {
        std::shared_ptr<Image> sptr = std::make_shared<Image>(filename); // may throw
        images.push_back(sptr); // only gets executed if there is no throw.
        ++count;
    }

    // no throw guarantee: the function is guaranteed not to throw an exception
    int getCount() noexcept { return count; }

        void print() const {
        std::cout << "Gallery (" << count << " images): ";
        for (auto& img : images) {
            std::cout << img->getName() << " ";
        }
        std::cout << "\n";
    }

private:
    std::vector<std::shared_ptr<Image>> images;
    int count = 0;
};


// --- Demo ---
int main() {
    ImageGallery gallery;

    try {
        std::cout << "\nAdding good image with basic guarantee...\n";
        gallery.addImage_basic("sunrise");
        gallery.print();

        std::cout << "\nAdding bad image with basic guarantee...\n";
        gallery.addImage_basic("bad"); // throws!
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
        gallery.print(); // state may have partially changed
    }

    try {
        std::cout << "\nAdding good image with strong guarantee...\n";
        gallery.addImage_strong("mountain");
        gallery.print();

        std::cout << "\nAdding bad image with strong guarantee...\n";
        gallery.addImage_strong("bad"); // throws!
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
        gallery.print(); // unchanged, all-or-nothing
    }

    std::cout << "\nNothrow count check: " << gallery.getCount() << "\n";
}