# Tournament Simulator in C 🏆

A robust, console-based tournament simulation program written in C. This project simulates complex, multi-round tournaments by implementing dynamic player routing, customized scoring rules, and a multi-phase progression system.

## 🌟 Features

- **Automated & Manual Modes**: Quickly generate mock players or manually enter specific participant profiles.
- **Dynamic Queue System**: Manages players across different queues (Active, Winners, Losers, and waitlists based on consecutive outcomes).
- **Multi-Phase Gameplay**: 
  - **Part I**: Scoring driven by randomized digit sums and custom mathematical conditions.
  - **Part II**: Advanced logic triggered later in the game, utilizing Greatest Common Divisors (GCD) and digit-sharing analysis to determine points.
- **In-Depth Statistics**: Tracks detailed stats per player including wins, losses, consecutive streaks, and total accumulated points, displaying an end-game summary.
- **Match Records**: Automatically logs and outputs the history and results of all played rounds.

## 🛠️ Prerequisites

To compile and run this project, you will need a C compiler installed on your system. 

- **Windows**: [MinGW-w64](https://www.mingw-w64.org/) or [Visual Studio](https://visualstudio.microsoft.com/)
- **Linux**: GCC (`sudo apt install build-essential`)
- **macOS**: Clang (`xcode-select --install`)

## 🚀 Getting Started

### 1. Clone the repository
```bash
git clone https://github.com/Urfavcurlygirl/Tournament-Simulator-C.git
cd Tournament-Simulator-C
```

### 2. Compile the code
Use your preferred C compiler to build the executable. For example, using `gcc`:
```bash
gcc -o tournament_simulator main.c
```

### 3. Run the application
```bash
./tournament_simulator
```

## 🎮 How to Play

Upon running the executable, you will be prompted to choose the simulation mode:
1. **Auto-play Mode (Enter `1`)**: The system automatically generates a preset queue of players to immediately jump into the action.
2. **Manual Mode (Enter any other number)**: You will be prompted to specify the total number of players and input their respective details (Number, Name, Age).

Once initialized, the game processes rounds automatically, printing out current matchups, scores, rule applications, and final outcomes.

## 🏗️ Technical Architecture

The program relies heavily on custom data structures to govern game state:
- **`Player` Struct**: Houses all statistical metrics.
- **Linked Lists (`LP`, `LG`)**: Manage the finalized Losers and Winners.
- **Queues (`F`, `F1`, `F3`)**: Dynamically manage active gameplay loops, cycling players based on their performance (e.g., players with 3+ consecutive wins/losses are routed to specific evaluation queues).

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! 
Feel free to check out the [issues page](../../issues) if you want to contribute.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---
*Created by [Urfavcurlygirl](https://github.com/Urfavcurlygirl).*