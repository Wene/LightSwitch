#ifndef SWITCH_H
#define SWITCH_H


class Switch
{
public:
    Switch(int relayPin, int lightButtonPin, int modifyButtonPin);
    void handle();

private:
    int relay;
    int lightButton;
    int modifyButton;
    int lightBtnPushed;
    int modifyBtnPushed;
    int cycleCount;
    int cycleTicker;
    int tickerDefault;

    bool isOn;

    void readButtons();
    void waitForRelease();
    void checkModify();
};

#endif
