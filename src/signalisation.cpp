#include <Arduino.h>
#include "signalisation.h"

RGBW color_red = {100, 0, 0, 0}; // Values from 0-255
RGBW color_green = {0, 100, 0, 0};
RGBW color_off = {0, 0, 0, 0};

Signalisation::Signalisation()
{
}

void Signalisation::positive()
{
    Hardware::buzzer.play(3000);
    Hardware::ledSignalization.set_rgbw(0, color_green);
    Hardware::ledSignalization.sync();
    delay(150);
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
    Hardware::buzzer.pause();
}

void Signalisation::positiveSound()
{
    Hardware::buzzer.play(3000);
    delay(150);
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
    Hardware::buzzer.pause();
}

void Signalisation::removedMember()
{
    for (char i = 0; i < 3; i++)
    {
        Hardware::buzzer.play(3000);
        Hardware::ledSignalization.set_rgbw(0, color_off);
        Hardware::ledSignalization.sync();
        delay(120);

        Hardware::buzzer.pause();
        delay(120);
    }
}

void Signalisation::whitelistFull()
{
    for (char i = 0; i < 8; i++)
    {
        Hardware::buzzer.play(3000);
        Hardware::ledSignalization.set_rgbw(0, color_red);
        Hardware::ledSignalization.sync();
        delay(120);

        Hardware::ledSignalization.set_rgbw(0, color_off);
        Hardware::ledSignalization.sync();
        Hardware::buzzer.pause();
        delay(120);
    }
}

void Signalisation::endKeying()
{
    Hardware::buzzer.play(3000);
    delay(700);
    Hardware::buzzer.pause();
}

void Signalisation::permDenied()
{
    for (char i = 0; i < 4; i++)
    {
        Hardware::buzzer.play(3000);
        Hardware::ledSignalization.set_rgbw(0, color_red);
        Hardware::ledSignalization.sync();
        delay(120);

        Hardware::ledSignalization.set_rgbw(0, color_off);
        Hardware::ledSignalization.sync();
        Hardware::buzzer.pause();
        delay(120);
    }
}

void Signalisation::reject()
{
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
    Hardware::buzzer.play(3000);
    delay(350);
    Hardware::ledSignalization.set_rgbw(0, color_red);
    Hardware::ledSignalization.sync();
    delay(150);
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
    Hardware::buzzer.pause();
}

void Signalisation::close()
{
    Hardware::buzzer.play(3000);
    delay(1000);
    Hardware::buzzer.pause();
}

void Signalisation::resetWhitelist()
{
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
    Hardware::buzzer.play(3000);
    delay(500);
    Hardware::buzzer.pause();
    delay(120);
    Hardware::buzzer.play(3000);
    delay(150);
    Hardware::buzzer.pause();
}

void Signalisation::fullReset()
{
    for (char i = 0; i < 2; i++)
    {
        Hardware::buzzer.play(3000);
        Hardware::ledSignalization.set_rgbw(0, color_off);
        Hardware::ledSignalization.sync();
        delay(120);

        Hardware::buzzer.pause();
        delay(120);
    }
    delay(1500);

    Hardware::ledSignalization.set_rgbw(0, color_green);
    Hardware::ledSignalization.sync();
    delay(800);
    Hardware::ledSignalization.set_rgbw(0, color_off);
    Hardware::ledSignalization.sync();
}

void Signalisation::green()
{
    Hardware::ledSignalization.set_rgbw(0, color_green);
    Hardware::ledSignalization.sync();
}