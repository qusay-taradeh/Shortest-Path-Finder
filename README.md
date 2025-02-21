# Shortest Path Finder

An application that finds the shortest path between two cities using Dijkstra's algorithm and Breadth-First Search (BFS).

## Summary

This project implements two pathfinding algorithms—Dijkstra’s and BFS—to determine the shortest route between two cities. The application reads city data from a provided file (`cities.txt`), constructs a graph, and allows the user to specify a source and destination city. It then computes and displays the full route (including individual leg distances) for both algorithms, as well as the total distance calculated by Dijkstra’s algorithm.

## Specifications

The application should perform the following tasks:

1. **Load Cities:**  
   - Load the file `cities.txt` and construct the graph that represents the cities and their connecting routes.

2. **Enter Source:**  
   - Read the source city input provided by the user.

3. **Enter Destination:**  
   - Read the destination city input provided by the user.
   - Print the full route of the shortest path, including:
     - The distance between each pair of consecutive cities.
     - The total shortest cost computed by Dijkstra’s algorithm.
     - The full route as determined by BFS.

4. **Exit:**  
   - Save the complete route information (from step 3) to a file named `shortest_distance.txt`.
   - Exit the program gracefully.

## Usage

1. Run the program.
2. Select the option to **Load Cities** to initialize the graph from `cities.txt`.
3. Input the **Source** city when prompted.
4. Input the **Destination** city when prompted.
5. Review the displayed shortest path information.
6. Select **Exit** to write the route details to `shortest_distance.txt` and terminate the program.

## Author

Qusay Taradeh
