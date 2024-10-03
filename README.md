# Project-ParkGenius

## Project Overview:

ParkGenius is an advanced parking management system designed for the City Center Mall, using SFML (Simple and Fast Multimedia Library) to create a real-time visual interface. This project aims to streamline the parking experience by providing an efficient system for tracking and managing vehicles within the mall's parking area. The system utilizes Winsock-based socket programming to enable seamless communication between entry and exit points, ensuring that parking slots are efficiently utilized.

## Key Features

### 1. Real-time Parking Layout Window
- This window offers a live view of the mall's parking status, showing which parking slots are currently occupied or vacant.
- It is intended for public display, allowing visitors and management to quickly check parking availability in real-time.

### 2. Security Desk Window
- At the security desk, this window allows personnel to input vehicle details such as weight, reason for visit, time of entry, and the car's number plate.
- Upon entry, the system automatically assigns a unique token (parking number) to the vehicle, which will serve as its identifier throughout the stay.

### 3. Exit Point Window
- This window is located at the parking exit. When a vehicle is ready to leave, the driver provides their assigned token to the security personnel.
- The token number is entered into the system, which sends a notification to the entry point confirming that the car has exited, freeing up the corresponding parking space.

## Communication and System Integration

- The *message transfer between the entry and exit points* is facilitated using Winsock-based socket programming. This ensures real-time updates on the availability of parking spaces, enabling smooth coordination across the system.
- The system is designed to provide both the security staff and visitors with up-to-date parking information, improving overall efficiency and user experience.

## Technology Stack

- *Graphics Interface:* SFML (Simple and Fast Multimedia Library)
- *Socket Programming:* Winsock library (Windows Sockets API)
- *Programming Language:* C++

## How It Works

- Vehicles entering the mall's parking area register their details at the security desk, where they receive a token.
- The parking layout updates in real-time to reflect the new status, displaying the occupied slot.
- When exiting, the token is entered at the exit point, signaling the system to update the parking layout and free up the space.

## Conclusion

ParkGenius enhances the management of mall parking areas by providing a visually intuitive layout, secure and streamlined data entry, and real-time communication between entry and exit points. This system ensures a seamless experience for both security personnel and mall visitors, optimizing parking space usage and improving overall efficiency.
