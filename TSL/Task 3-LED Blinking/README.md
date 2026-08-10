# Task 03 – LED Blinking

## Objective

Control an LED using the ESP32 and make it blink at a fixed interval of 2 seconds.

## Task Details

| Parameter | Details    |
| --------- | ---------- |
| Task      | 03         |
| Date      | 15 May     |
| Mode      | Online     |
| Platform  | ESP32      |
| Framework | Arduino    |
| IDE       | PlatformIO |
| Output    | LED        |

## Concept Covered

* GPIO output
* Digital pin control
* LED interfacing
* Timing using `delay()`
* `HIGH` and `LOW` digital states

## Working

The LED is connected to a GPIO pin of the ESP32. The program continuously switches the GPIO between `HIGH` and `LOW`, keeping each state for 2 seconds. This produces a continuous blinking effect.

## Expected Behavior

```text
LED ON  →  2 seconds
LED OFF →  2 seconds
LED ON  →  2 seconds
LED OFF →  2 seconds
...
```

## Tools Used

* ESP32
* LED
* VS Code
* PlatformIO
* Wokwi

## Learning Outcome

This task demonstrates basic GPIO output control and introduces timing-based control of hardware peripherals using the ESP32.
