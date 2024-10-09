# Calendar/Planner Application

## Overview

This C++ application provides a console-based calendar and planner system, allowing users to:
- View a monthly calendar for a given year and month.
- Add events to specific dates.
- View events for a specific date or month.
- Create and manage a to-do list for specific dates.

The application is a simple calendar and event management tool with linked list-based event storage and a queue-based task management system for to-do lists.

## Features

1. **View Monthly Calendar**: Display the calendar for a specified month and year.
2. **Add Event**: Create an event by specifying a date, title, and description. Events are stored using a linked list.
3. **View Events**: View all events for a specific date.
4. **View Monthly Events**: List all the events for a specified month.
5. **To-Do List Management**: 
   - Add tasks to a to-do list for a specific date.
   - View the list of tasks.
   - Mark tasks as completed (FIFO order using a queue).
6. **Exit the Application**: Close the application.

## Data Structures

- **Event Management**: Events are stored in a linked list. Each `Event` contains a date, title, and description.
- **To-Do List**: The to-do list is managed as a queue (FIFO), where tasks are added at the rear and completed tasks are removed from the front.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, Clang, or Visual Studio).
- Basic knowledge of C++.

### Installation

1. Clone or download the project files.
2. Open a terminal or command prompt and navigate to the folder containing the files.
3. Compile the code using a C++ compiler. For example, using `g++`:
   ```bash
   g++ -o calendar_planner main.cpp