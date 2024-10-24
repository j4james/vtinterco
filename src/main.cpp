// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "capabilities.h"
#include "coloring.h"
#include "font.h"
#include "menu.h"
#include "os.h"
#include "quizzes.h"
#include "viewer.h"
#include "vt.h"

static constexpr auto application_name = "VT INTERCO";

bool check_compatibility(const capabilities& caps)
{
    if (!caps.has_soft_fonts || !caps.has_sixels || !caps.has_sixel_display_mode) {
        vtout.write(application_name);
        vtout.write(" requires a VT340-compatible terminal.\n");
        return false;
    }
    if (caps.height < 24) {
        vtout.write(application_name);
        vtout.write(" requires a minimum screen height of 24.\n");
        return false;
    }
    if (caps.width < 80) {
        vtout.write(application_name);
        vtout.write(" requires a minimum screen width of 80.\n");
        return false;
    }
    return true;
}

int main(int argc, const char* argv[])
{
    os os;
    capabilities caps;
    if (!check_compatibility(caps))
        return 1;

    // Set the window title.
    vtout.decswt(application_name);
    // Set default attributes.
    vtout.sgr();
    // Clear the screen.
    vtout.ed(2);
    // Hide the cursor.
    vtout.rm('?', 25);
    // Initialize the color palette.
    const auto colors = coloring{caps};
    // Load the soft font.
    const auto font = soft_font{};

    menu menu(caps,
        {
            "VIEW ALPHABET FLAGS",
            "VIEW NUMERAL PENNANTS",
            "TEST ALPHABET FLAGS",
            "TEST NUMERAL PENNANTS",
            "TEST SINGLE FLAG SIGNALS",
            "TEST DOUBLE FLAG SIGNALS",
            "LOOKUP FLAG SEQUENCE",
            "EXIT",
        });
    while (auto choice = menu.get_choice()) {
        switch (choice.value()) {
            case 0:
                viewer::view_alphabet_flags(caps);
                break;
            case 1:
                viewer::view_numeral_pennants(caps);
                break;
            case 2:
                quiz::code_words.run(caps);
                break;
            case 3:
                quiz::figure_words.run(caps);
                break;
            case 4:
                quiz::single_flags.run(caps);
                break;
            case 5:
                quiz::double_flags.run(caps);
                break;
            case 6:
                viewer::lookup_letter_sequence(caps);
                break;
        }
    }

    // Reset the window title.
    vtout.decswt();
    // Set default attributes.
    vtout.sgr({});
    // Clear the screen.
    vtout.cup();
    vtout.ed();
    // Show the cursor.
    vtout.sm('?', 25);

    return 0;
}
