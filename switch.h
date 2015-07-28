#ifndef SWITCH_H
#define SWITCH_H


class Switch
{
public:
    Switch(int relaisPin, int lightButtonPin, int modifyButtonPin);
    void handle();

private:
    int relais;
    int lightButton;
    int modifyButton;
    int lightCount;
    int modifyCount;
    int lightDuration;
    int ticker;
    int tickerDefault;

    bool isOn;

    void readButtons();
    void debounce();
    void checkModify();
};

#endif
