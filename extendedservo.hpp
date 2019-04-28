#ifndef EXTENDEDSERVO_H_
#define EXTENDEDSERVO_H_

#include <stdint.h>
#include <Servo.h>

template <uint8_t _Servo, uint8_t _Delay = 1, uint16_t _Min = 544, uint16_t _Max = 2400>
class ExtendedServo : Servo
{
private:
    /* data */
    Servo _servo;
    uint8_t _angle;

public:
    ExtendedServo(){
        _angle = 0;
    };

    void begin()
    {
        _servo.attach(_Servo, _Min, _Max);
        _servo.write(_angle);
    }

    uint8_t getAngle() const { return _angle; }

    void servoWriteAngle(uint8_t angle)
    {
        if (angle <= 180)
        {
            for (uint8_t i = _angle; i <= angle; i++)
            {
                _servo.write(i);
                delay(_Delay);
            }
        }
        else if (angle >= 0)
        {
            for (uint8_t i = _angle; i >= angle; i--)
            {
                _servo.write(i);
                delay(_Delay);
            }
        }
    }

    ExtendedServo &operator++()
    {
        if (_angle >= 0 && _angle < 180)
        {
            servoWriteAngle(++_angle);
        }
        return *this;
    }

    ExtendedServo operator++(int)
    {
        ExtendedServo temp = *this;
        ++*this;
        return temp;
    }

    ExtendedServo &operator--()
    {
        if (_angle > 0 && _angle <= 180)
        {
            servoWriteAngle(--_angle);
        }
        return *this;
    }

    ExtendedServo operator--(int)
    {
        ExtendedServo temp = *this;
        --*this;
        return temp;
    }
};

#endif