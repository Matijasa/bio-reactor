---
title: Bioreactor project
date: 2020-11-05 11:20:38
draft: false
layout: ../layouts/BlogPost.astro
---

# Bioreactor

## Motivation

Author:  **Matija Šavli**, **Lan Vukušič**  
My friend [Lan Vukusic](https://github.com/LanVukusic) and I are both hobby beer brewers, but we found ourselves running out of yeast. One time, we decided to use sediment from a previous batch of beer to cultivate yeast in a small jar. This worked well, but we knew there had to be a better way to optimize the process.

We began researching and came across the idea of creating our own bioreactor to cultivate yeast under controlled conditions. By controlling environmental factors like temperature, pH, and oxygen levels, we could improve the quality and yield of our beer. It would also allow us to scale up production while maintaining consistent quality.

## Designing parts

When we set out to create our bioreactor, we had a general idea of what the finished product should look like, but we made no hard plans. We were aware that most of the things we plan wouldn't work out or that better options would become obvious. However, we knew that we needed specific parts to make the bioreactor function properly:

- [Jar lid](#jar-lid)
- [Mixer](#mixer)
  - and many pieces for it to work
- Motor holder
- Temperature probe mount
- Bubbler
- Sample retreving mechanism
- Electronics housing

In the following chapters, we will describe the design of these parts, iterations, and problems that we encountered along the way.

### Jar lid
We decided to use a 5-liter glass jar as the base container for our bioreactor, which we were able to purchase for approximately `4€`. It was an ideal choice as it was large enough for our needs, inexpensive, and of good quality. Overall, it was a great buy.

To mount all the sensors and actuators, we decided to create an airtight lid that would cover the jar, help keep the reactor sterile, and allow us to mount various equipment on it. To model the jar lid, we used freeCAD and printed the models using the Creality V2 printer.

The most challenging aspect of designing the lid was creating the thread and ensuring that the diameter was accurate enough to close the lid tightly. We performed a series of test prints with different radii to find the tightest fit.

![lid test prints](/public/img/lid_prints.png)

After conducting a series of test prints with various radii, we were able to find the ideal fit for the jar lid. The successful test print is shown on the bottom right in the image below.

While determining the correct radius was not overly challenging, creating the thread proved to be more difficult. We had trouble measuring the angle of the teeth that grip the jar, so we had to resort to trial and error to find the best method. 

![lid design](/public/img/lid_autocad.png)

The final option printed just great and allowed for a tight screw on.

### Mixer

Properly mixing the contents of the reactor is crucial for ensuring good aeration and preventing sediment formation. It is important to distribute micro-organisms evenly throughout the medium.

To design the mixer blades, we used freeCAD and based our dimensions on a sketch that I had seen in one of my university classes. We chose the dimensions somewhat arbitrarily.

The reactor has a diameter of `d = 180mm` and a height of approximately `h = 220mm`. The diameter `d_blade` and height `h_blade` of the mixer blades can be calculated as follows:

$$
d_{blade} = \frac{d}{3} = \frac{180}{3} = 60
$$
$$
h_{blade} = \frac{d_{blade}}{5} = \frac{60}{5} = 12
$$

With the sizes calculated, only thing left to choose was the shape of the mixer.  

Firstly we had to choose between `axial` (left) and `radial` (right) mixer heads:  

![axial and radial mixer heads](/public/img/mixer_heads.png)

 Different positioning and angles of the blades have their own pros and cons.  

| Mixer head | pros | cons |
| :---: | --- | --- |
| Axial | More efficient, good for sensitive microorganisms, better vertical circulation | lower sheer forces |
| Radial | High sheer forces | less efficient, worse vertical circulation |

>**Shear forces** are essential for generating turbulence and breaking apart air bubbles into smaller ones, which improves the aeration of the medium. This increased surface area also allows for better diffusion of gases, which is crucial for microorganisms to grow and thrive in the bioreactor.
>However, one downside of shear forces is that they can easily damage sensitive organisms such as filamentous fungi cells and some animal cells. It's important to be aware of this and adjust the mixing speed accordingly to minimize the risk of damage while still achieving optimal aeration. It's also worth noting that not all organisms require the same level of aeration, so it's important to tailor the mixing speed and shear forces to the specific needs of the microorganisms being cultured in the bioreactor.

We have opted for the radial head design as it is best suited for growing yeast in the presence of oxygen. This design offers good shear forces that break apart air bubbles into smaller ones, allowing for better aeration of the medium. Although this design may have some efficiency loss and worse vertical circulation, it is negligible for a reactor of this size.

To ensure the radial head is secure, we have added a mounting piece to the design, allowing us to fit a screw to tighten it to the lead.

![mixer head design progression](/public/img/mixer_designs.png)

The final part was printed from the last (right most) design:  

![printed mixer head](/public/img/mixer_print.jpg)  

### Motor
We repurposed a stepper motor from an old ink printer to drive the mixer. However, we needed a driver board to properly control the motor. After researching various options, we settled on a reliable and affordable board that would allow us to easily adjust the motor speed and direction.
### Transfer of power
We used a belt system.  
### Mixer
For the axel shaft we used a 1mm * 1mm metal rod to which we attached the rotor heads. The rod is mounted on the lid. It passes through a bearing which allows for free rotational movement.
### Air supply
We decided to buy a aquarium air pump to fulfil the need for oxygen.  
### Main housing for electronics
Under construction
### Electronics and sensors
Under construction
### 