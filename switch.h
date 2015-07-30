#ifndef SWITCH_H
#define SWITCH_H


class Switch
{
public:
    Switch(int relayPin, int lightButtonPin, int modifyButtonPin, int ticker, int delay);
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
    int delayTime;
    bool isOn;

    void readButtons();
    void waitForRelease(int &button);
    void checkModify();
};

#endif
