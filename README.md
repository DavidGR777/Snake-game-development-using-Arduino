## Description
This repository presents the design and development of a multiplayer Snake game implemented on an Arduino platform. The project integrates both hardware and software components to create an interactive embedded system capable of handling multiple players simultaneously.

The system combines real-time input processing, concurrent game logic, and graphical display using an OLED screen. Special attention is given to task organization, responsiveness, and efficient resource usage within the constraints of a microcontroller environment.

## Objective
The main objective of this project is to develop a fully functional Snake game on Arduino that supports multiple players and real-time interaction. This includes:

- Implementing concurrent game logic for multiple snakes.
- Processing analog input signals from joysticks.
- Rendering the game state on an OLED display.
- Integrating sound feedback through a speaker.
- Ensuring responsive and stable performance under hardware constraints.

## Features
<details>
<summary>Click to expand</summary>

- Multiplayer support (up to 4 players simultaneously)
- Real-time movement and input handling
- Dynamic difficulty (speed increases over time)
- Score tracking for each player
- Collision detection (self, other players, and walls)
- Sound effects and game feedback
- OLED-based visual interface
</details>
 
## Game Logic Overview

<details>
<summary>Click to expand</summary>

The gameplay includes the following mechanics:

- Each player controls a snake using a joystick.
- Snakes grow after consuming fruit.
- Game speed increases as time progresses.
- Players are eliminated upon collision:
  - With themselves
  - With other players
  - With boundaries
- The game ends when all players are defeated.
- Final scores are displayed at the end.
</details>

## Hardware Components
- Arduino Uno
- OLED display (visual interface)
- Joysticks (player input)
- Speaker (audio feedback)

### Key Considerations
- Joystick inputs are processed as analog signals.
- The speaker is connected via PWM output.
- OLED display integration affects rendering logic and performance.
- Pin limitations may arise depending on the display used.

## Observations and Recommendations
- OLED display significantly impacts display logic design.
- Some functions can be optimized to reduce power consumption.
- Hardware limitations affect performance (e.g., speaker output).
- Collision detection logic can be further improved.

## Conclusions
This project demonstrates the feasibility of implementing a multiplayer interactive game on a constrained embedded system. It highlights the importance of efficient resource management, modular software design, and careful hardware integration.

## Usage
This repository is intended for:

- Embedded systems students
- Arduino developers
- Game development enthusiasts
- Anyone interested in hardware-software integration

## Contributions
Contributions are welcome. Feel free to open issues or submit pull requests to improve the project.

## Project Members
Juan Pablo Ruiz Puente  
David Esteban González Rozo  
Luisa Fernanda Coronado Mora  
