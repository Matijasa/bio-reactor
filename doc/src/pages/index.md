---
title: Bioreactor project
date: 2020-11-05 11:20:38
draft: false
layout: ../layouts/BlogPost.astro
---

## Motivation

## Motivation

**Authors:** Matija Šavli, Lan Vukušič

My friend [Lan Vukusic](https://github.com/LanVukusic) and I are both hobby beer brewers, but we found ourselves running out of yeast. One time, we decided to use sediment from a previous batch of beer to cultivate yeast in a small jar. This worked well, but we knew there had to be a better way to optimize the process.

We began researching and came across the idea of creating our own bioreactor to cultivate yeast under controlled conditions. By controlling environmental factors like temperature, pH, and oxygen levels, we could improve the quality and yield of our beer. It would also allow us to scale up production while maintaining consistent quality.

## Designing parts

When we set out to create our bioreactor, we had a general idea of what the finished product should look like, but we made no hard plans. We were aware that most of the things we plan wouldn't work out or that better options would become obvious. However, we knew that we needed specific parts to make the bioreactor function properly:

- [Jar lid](#jar-lid)
- [Mixer](#mixer)
- Motor holder
- Temperature probe mount
- Bubbler
- Electronics housing

In the following chapters, we will describe the design of these parts, iterations, and problems that we encountered along the way.

### Jar lid

We decided to use a 5-liter glass jar as the base container for our bioreactor, which we were able to purchase for approximately `4€`. It was an ideal choice as it was large enough for our needs, inexpensive, and of good quality. Overall, it was a great buy.

To mount all the sensors and actuators, we decided to create an airtight lid that would cover the jar, help keep the reactor sterile, and allow us to mount various equipment on it. To model the jar lid, we used freeCAD and printed the models using the Creality V2 printer.

The most challenging aspect of designing the lid was creating the thread and ensuring that the diameter was accurate enough to close the lid tightly. We performed a series of test prints with different radii to find the tightest fit.

![lid test prints](/img/lid_prints.webp)

After conducting a series of test prints with various radii, we were able to find the ideal fit for the jar lid. The successful test print is shown on the bottom right in the image below.

While determining the correct radius was not overly challenging, creating the thread proved to be more difficult. We had trouble measuring the angle of the teeth that grip the jar, so we had to resort to trial and error to find the best method.

![lid design](/img/lid_autocad.webp)

The final option printed just great and allowed for a tight screw on.

### Mixer

Properly mixing the contents of the reactor is crucial for ensuring good aeration and preventing sediment formation. It is important to distribute micro-organisms evenly throughout the medium.

To design the mixer blades, we used freeCAD and based our dimensions on standard bioprocess engineering ratios found in literature (similar to a standard **Rushton Turbine** design).

The reactor has a diameter of `d = 180mm` and a height of approximately `h = 220mm`. The diameter `d_blade` and height `h_blade` of the mixer blades can be calculated as follows:

$$
d_{blade} = \frac{d}{3} = \frac{180}{3} = 60
$$
$$
h_{blade} = \frac{d_{blade}}{5} = \frac{60}{5} = 12
$$

With the sizes calculated, we had to choose the blade geometry.

Firstly we had to choose between `axial` (left) and `radial` (right) mixer heads:

![axial and radial mixer heads](/img/mixer_heads.webp)

Different positioning and angles of the blades have their own pros and cons.

| Mixer head | Type Name | Pros | Cons |
| :---: | --- | --- | --- |
| Axial | **Marine Propeller** | High Flow, Gentle mixing | Low shear (bad for bubbles) |
| Radial | **Rushton Turbine** | High Shear (great for bubbles) | "Worse" vertical circulation |

>**Why Radial? The "Shear" Factor**
> We chose the **Radial** design (Rushton Turbine) for one reason: **Gas Dispersion**.
> In a bioreactor, the limiting factor is usually how much oxygen you can dissolve into the liquid (Mass Transfer Coefficient, or $k_L a$).
>
> A radial mixer pushes fluid outward against the jar walls with high energy. This "shear force" smashes the large air bubbles coming from the bottom into tiny micro-bubbles. Smaller bubbles mean more surface area, which means more oxygen for the yeast. While high shear can damage sensitive animal cells, yeast are robust enough to handle it.

To ensure the radial head is secure, we have added a mounting piece to the design, allowing us to fit a screw to tighten it to the lead.

![mixer head design progression](/img/mixer_designs.webp)

The final assembly uses a square brass rod to transmit torque, with the 3D printed mixing heads secured at the bottom.

![printed mixer assembly](/img/rotating_rod.webp)

### Motor and Housing

**The "Free" Mistake:** Initially, we repurposed a stepper motor from an old ink printer. It was free, but mounting it was a nightmare and it became too complex.

![Old Printer Motor Setup](/img/old_motor_holder2.webp)

**The Upgrade:** We eventually upgraded to a standard **NEMA 17** stepper motor. It is the industry standard for 3D printers for a reason: it offers high torque, precise control, and standard mounting holes.

<video controls autoplay loop muted playsinline width="100%">
  <source src="/img/motor_test_silent.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

To securely attach the NEMA 17 to our lid, we designed a custom motor holder in FreeCAD.

Here is the complete assembly design. The motor attaches at the top, and the housing ensures it stays perfectly aligned with the central mixing shaft while minimizing vibration:

![Motor Housing Assembly CAD](/img/new_motor_holder.png)

Instead of a complex belt system, we opted for a direct-drive configuration. We designed a custom 3D-printed coupler to connect the motor's shaft directly to the square brass mixing rod. This simplifies the assembly and reduces the number of moving parts.

### The Scrapyard (Failed Ideas)

Science is mostly failure. Before we landed on the direct-drive tower, we tried a complex belt-drive system to keep the motor off-center.

- **The Idea:** Use a belt to reduce vibration and keep the motor cool.
- **The Reality:** It was unwieldy and overly complex. Tensioning the belt was a nightmare, and it added necessary points of failure.
- **The Lesson:** Simple is better. We scrapped it for the direct-drive approach.

### Air supply

For oxygenation, we selected a **Resun Air 2000** aquarium pump. It provides sufficient airflow to keep the medium oxygenated. To ensure sterility, the air intake passes through a **Sartorius Midisart 2000** filter.

![Air pump](/img/air_pump.webp)

**Current Limitation:** The pump runs on **220V AC** (wall power), while the rest of our system is **12V DC**.
Right now, the pump is "always on" when plugged in. We haven't tested the automated cycle yet because we need to install a **relay module** (or Solid State Relay) to let the low-voltage ESP32 safely switch the high-voltage AC pump on and off.

### Electronics and sensors

The brain of the operation is an **ESP32-WROOM-32** microcontroller. This board was chosen for its built-in WiFi and Bluetooth capabilities, which will eventually allow us to monitor the fermentation process remotely.
To keep things modular during development, we wired everything up on a breadboard first. This "Rat's Nest" includes the ESP32, a stepper driver, and the power management rails.

## Schematics and PCB

The schematics were never actualized and printed, but a Ki-Cad project for the production version is made and available on github.  

<div style="margin: 4rem -50vw; background-color: rgba(55,65,81,0.04)">
  <img src="/img/pcb-design.svg" style="width: 100%; max-width: 100vw; max-height:105vh;">
</div>

## Prototyping components
![Electronics Prototype Breadboard](/img/electronics_breadboard.jpg)


For temperature control, we are using a small immersion heating element. This allows us to maintain the precise temperature range required for specific yeast strains (typically between 18°C and 24°C).

![Heating element](/img/heating_element.webp)

Before risking a full batch of yeast, we validated the heating logic in a high-tech simulation environment (a plastic cup of water).

<video controls autoplay loop muted playsinline width="100%">
  <source src="/img/heater_logic_test_silent.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

![Heater Test Setup](/img/heater_test.jpg)

### The Power Plant

To run the heater, the stepper motor, and the ESP32, we needed a reliable 12V DC source. Instead of buying a cheap brick, we repurposed a server power supply (**HP HSTNS-PL23B**) scavenged from an old data center rack.

![Server Power Supply](/img/power_suppy.jpg)

- **Output:** 12V @ 38.3A (460W Max)
- **Role:** It powers the stepper motor, the heating element, and the microcontroller (stepped down). It is completely overkill for this project, but it guarantees stable voltage no matter how hard the motor or heater draws current.

## The Logic (Firmware)

Hardware is nothing without code. We developed the firmware using **PlatformIO** (VS Code) for its easy library management, though we plan to migrate to the native **Espressif IDF** later for more granular control.
The current version (`v0.1`) uses a **Bang-Bang control loop** (the simplest form of feedback control):

1. Read temperature.
2. Is it too cold? Turn heater **ON**.
3. Is it hot enough? Turn heater **OFF**.

We also added safety checks to ensure the sensor is actually connected (reading `-127` usually means the sensor wire is broken).

Here is the raw `v0.1` code currently running on the reactor. Note the `INVERTED PINS` logic—most relay modules are "Active Low," meaning sending a `0` (LOW) signal actually turns the switch **ON**.

```cpp
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
#define ONE_WIRE_BUS 4
#define GATE_PIN 2

// Configuration
#define TEMP_WANTED 43.0 // High temp for stress testing heater

// Sensor Setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Global Variables
int initial_time = 0;
int initial_temp = 0;
bool has_reached_temp = false;

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  delay(500);

  // GATE SETUP
  pinMode(GATE_PIN, OUTPUT);

  // Reset metrics
  initial_time = millis();
  initial_temp = sensors.getTempCByIndex(0);
}

void loop()
{
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.print(temp);
  Serial.print(" C  |  ");
  delay(500);

  // Failsafe: Check if sensor is unplugged (returns -127)
  if (temp - (-127.0) < 0.0001)
  {
    Serial.println("No sensor found");
    delay(1000);
    return;
  }

  // Bang-Bang Control Logic
  if (temp < TEMP_WANTED)
  {
    // INVERTED PINS (LOW = Relay ON)
    digitalWrite(GATE_PIN, LOW);
    Serial.print("Gate opened (Heater ON)  |  ");
  }
  else
  {
    // INVERTED PINS (HIGH = Relay OFF)
    digitalWrite(GATE_PIN, HIGH);
    Serial.print("Gate closed (Heater OFF) |  ");

    // Performance Logging: Record time to reach target
    if (!has_reached_temp)
    {
      has_reached_temp = true;
      Serial.println("");
      Serial.print("Time to reach temp: ");
      int time = millis() - initial_time;
      Serial.print(time / 1000);
      Serial.print(" s || ");
      Serial.print("Temp delta: ");
      Serial.print(temp - initial_temp);
      Serial.println(" C");
    }
  }

  // Runtime logger
  int time = millis() - initial_time;
  Serial.print(time / 1000);
  Serial.println(" s");
}
```

## The Bill of Materials

Total cost? Still cheaper than buying new yeast every weekend, even with the motor upgrade.

- **Glass Jar:** `4€` (Local hardware store)
- **Motor:** `~15€` (Upgraded to a NEMA 17 Stepper because the printer motor struggled)
- **ESP32:** `~5€` (AliExpress special)
- **Air Pump:** `15€` (Pet store)
- **Sterile Filter:** `0€` (Donated/Scavenged from a lab)
- **Filament:** `~200g` of PLA (and a lot of failed prints)

## Future Upgrades

The hardware is alive, but the brain needs work. The next steps for the project:

1. **Web Dashboard:** The ESP32 will host a local website showing live temperature graphs.
2. **PID Tuning:** Teaching the heater not to overshoot and boil the yeast.
3. **Beer Brewing:** Actually using the biomass to ferment a batch of IPA.
