# Task 01 – Continuous String Printing

## Objective

Print a string continuously using the ESP32 and display the output through the Serial Monitor.

## Task Details

| Parameter | Details        |
| --------- | -------------- |
| Task      | 01             |
| Date      | 15 May         |
| Mode      | Online         |
| Platform  | ESP32          |
| Framework | Arduino        |
| IDE       | PlatformIO     |
| Output    | Serial Monitor |

## Concept Covered

* ESP32 Serial Communication
* `Serial.begin()`
* `Serial.println()`
* Continuous program execution using `loop()`

## Working

The ESP32 initializes serial communication at a defined baud rate. A string is then continuously printed to the Serial Monitor from the `loop()` function.

## Expected Output

```text
Hello ESP32
Hello ESP32
Hello ESP32
Hello ESP32
...
```

## Tools Used

* ESP32
* VS Code
* PlatformIO
* Serial Monitor

## Learning Outcome

This task demonstrates the basic structure of an ESP32 program and introduces serial communication for monitoring program output and debugging.
