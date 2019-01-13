#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define PB(x) push_back(x)

class Phone
{
public:
    vector<string> keyboard;

    void add_button(string button_desc)
    {
        keyboard.PB(button_desc);
    }
    string return_characters(int key, int number_of_clicks)
    {
        string sequence = "";
        int number_of_characters_on_a_button = keyboard[key].size();
        while(number_of_clicks >= number_of_characters_on_a_button)
        {
            sequence += keyboard[key][number_of_characters_on_a_button - 1];
            number_of_clicks -= number_of_characters_on_a_button;
        }
        if(number_of_clicks > 0 ) sequence += keyboard[key][number_of_clicks-1];

        return sequence;
    }
};

int main()
{
    Phone phone;
    phone.add_button(" ");
    phone.add_button(".,?\"");
    phone.add_button("abc");
    phone.add_button("def");
    phone.add_button("ghi");
    phone.add_button("jkl");
    phone.add_button("mno");
    phone.add_button("pqrs");
    phone.add_button("tuv");
    phone.add_button("wxyz");

    int test_cases;
    int number_of_clicks;
    int pressed_button,
        number_of_presses;

    cin>>test_cases;
    while(test_cases--)
    {
        cin>>number_of_clicks;
        vector<int> buttons,number_of_button_clicks;
        for(int i=0;i<number_of_clicks;i++)
        {
            cin>>pressed_button;
            buttons.PB(pressed_button);
        }
        for(int i=0;i<number_of_clicks;i++)
        {
            cin>>number_of_presses;
            number_of_button_clicks.PB(number_of_presses);
        }
        for(int i=0;i<number_of_clicks;i++)
        {
            cout<<phone.return_characters(buttons[i],number_of_button_clicks[i]);
        }
        cout<<endl;
    }

    return 0;
}
