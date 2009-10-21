
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

    ui::Slider slider1(ui::Slider::HORIZONTAL);
    ui::Slider slider2(ui::Slider::VERTICAL);
    slider1.Move(20, 340);
    slider2.Move(240, 20);

    window.SetSize(200, 300);
    window.SetAlignment(ui::Align::TOP_LEFT, Vector2f(20, 20));


    label.Move(20, 40);
    checkbox.Move(20, 100);
    btn.Move(67, 170);

    area.AddRadioButton(&opt1);
    area.AddRadioButton(&opt2);
    area.AddRadioButton(&opt3);

    area.SetColor(Color(255, 255, 255, 123));
    area.SetAlignment(ui::Align::BOTTOM_CENTER);

    input.SetAlignment(ui::Align::BOTTOM_LEFT, Vector2f(5, -5));

    // Then we add all of them to their wanted parent =)
    window.Add(&label);
    window.Add(&checkbox);
    window.Add(&area);
    window.Add(&btn);

    myGui.Add(&input);
    myGui.Add(&window);
    myGui.Add(&slider1);
    myGui.Add(&slider2);

    while (myApp.IsOpened())
    {
        Event event;

        while (myApp.GetEvent(event))
        {
            if (event.Type == Event::Closed)
                myApp.Close();

            myGui.InjectEvent(event);
        }

        myApp.Clear(Color(255, 255, 255));

        myGui.Display();

        myApp.Display();
    }

    return (EXIT_SUCCESS);
}
