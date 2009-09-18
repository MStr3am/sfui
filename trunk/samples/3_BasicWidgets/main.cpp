
#include <SFML/Graphics.hpp>
#include <SFUI.hpp>

using namespace sf;

int main(int ac, char **av)
{
    RenderWindow myApp(VideoMode(800, 600), "Demo Basic widgets");

    ui::GuiRenderer myGui(myApp);

    // First, we load default builtin styles for basic widgets.
    ui::ResourceManager::Get()->AddStylesFromFile("data/default_style.xml");

    // Ok, we can create some non-relevant widgets ^^
    ui::Window window(L"My Window");
    ui::Label label(L"This is a very cool label !!");
    ui::CheckBox checkbox(L"Do we really need this ?");
    ui::TextInput input(L"Please enter your name here !");
    ui::TextButton btn(L"Click me !");

    ui::RadioArea area;
    ui::RadioButton opt1(L"Option 1"), opt2(L"Option 2"), opt3(L"Option 3");

    window.SetColor(Color(255, 255, 255, 123));
    window.SetSize(200, 300);
    window.SetAlignment(ui::Align::CENTER);

    label.Move(20, 40);
    checkbox.Move(20, 100);
    btn.Move(67, 170);

    area.AddRadioButton(&opt1);
    area.AddRadioButton(&opt2);
    area.AddRadioButton(&opt3);

    area.SetColor(Color(255, 255, 255, 123));
    area.SetAlignment(ui::Align::BOTTOM_CENTER);

    input.SetAlignment(ui::Align::BOTTOM_LEFT);

    // Then we add all of them to their wanted parent =)
    window.Add(&label);
    window.Add(&checkbox);
    window.Add(&area);
    window.Add(&btn);

    ui::Widget& top = myGui.GetTopWidget();

    top.Add(&input);
    top.Add(&window);

    while (myApp.IsOpened())
    {
        Event event;

        while (myApp.GetEvent(event))
        {
            if (event.Type == Event::Closed)
                myApp.Close();

            myGui.InjectEvent(event);
        }

        myApp.Clear();

        myGui.Display();

        myApp.Display();
    }

    return (EXIT_SUCCESS);
}
