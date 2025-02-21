/*************************************Shortest Path Program************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_OF_CITIES 100 //maximum number of cities
#define DISTANCE_INFINITY 1000000000 //approximately distance

typedef struct //implementation of City "array of struct"
{
    char name[30]; //name of city
} City;

typedef struct  // path in other words in graph called Edge
{
    int source; //source city
    int destination; //destination city
    int distance; //distance between cities
} Path;

City cities[MAX_NUM_OF_CITIES]; // 2D array of names of cities

Path graph[MAX_NUM_OF_CITIES][MAX_NUM_OF_CITIES]; //main graph contains the cities and paths between them

int numOfCities = 0; //global var. to represent number of cities excited.

void loadFile() // loads cities and distances from Cities file.
{
    /*
    file: file of cities.
    source: source city.
    destination: destination city.
    distance: distance between cities.
    */
    FILE* file;
    char source[20];
    char destination[20];
    int distance;
    file = fopen("Cities.txt", "r");

    while (fscanf(file, "%s %s %dkm", source, destination, &distance) != EOF) //loop to load data from file
    {
        int sIndex = -333, dIndex = -333; //sIndex : source index , dIndex: destination index and -333 random number to perform other parts of th function

        for (int i = 0; i < numOfCities; i++) //loop to add different cities in array without duplication if source is not excited
        {
            if (strcmp(cities[i].name, source) == 0)
            {
                sIndex = i;
                break;
            }
        }

        if (sIndex == -333) //putting source in cities array
        {
            strcpy(cities[numOfCities].name, source);
            sIndex = numOfCities; //change index of source
            ++numOfCities;
        }

        for (int i = 0; i < numOfCities; i++) //loop to add different cities in array without duplication if destination is not excited
        {
            if (strcmp(cities[i].name, destination) == 0)
            {
                dIndex = i;
                break;
            }
        }

        if (dIndex == -333) //putting destination in cities array
        {
            strcpy(cities[numOfCities].name, destination);
            dIndex = numOfCities; //change index of destination
            ++numOfCities;
        }

        //adding path to main graph
        graph[sIndex][dIndex].source = sIndex;
        graph[sIndex][dIndex].destination = dIndex;
        graph[sIndex][dIndex].distance = distance;
    }

    fclose(file);
}

void dijkstra(int source, int destination, int printToFile) //Dijkstra's algorithm
{
    /*
    distances: array of distance between cities.
    visited: array of visited status of the city.
    path: array of previous cities that visited to print the path.
    current: to make a copy of destination.
    file: file of store path between cities.
    */
    int distances[MAX_NUM_OF_CITIES], visited[MAX_NUM_OF_CITIES], path[MAX_NUM_OF_CITIES];
    int current = destination;
    FILE* file = fopen("shortest_distance.txt", "a");

    for (int i = 0; i < numOfCities; i++) // loop to perform initial visited status , distances and previous visited cities
    {
        distances[i] = DISTANCE_INFINITY;
        visited[i] = 0;
        path[i] = -222;
    }

    distances[source] = 0; //initial distance of source is always zero

    for (int j = 0; j < numOfCities - 1; j++) //loop to calculate shortest path.
    {
        int minDistance = DISTANCE_INFINITY; //minimum distance totally.
        int minIndex = -333; //minimum index of shortest path

        for (int i = 0; i < numOfCities; i++) //loop to update distance.
        {
            if (!(visited[i]) && distances[i] < minDistance)
            {
                minDistance = distances[i];
                minIndex = i;
            }
        }

        visited[minIndex] = 1;

        for (int newCiy = 0; newCiy < numOfCities; newCiy++) //loop to update the distance
        {
            if (!visited[newCiy] && graph[minIndex][newCiy].distance != 0 ) // means if vertex is not visited and distance on the edge does not equal zero!
                if((distances[minIndex] + graph[minIndex][newCiy].distance) < distances[newCiy]) //means if current distance and new distance is less than distance of another city then update distance!
                {
                    distances[newCiy] = distances[minIndex] + graph[minIndex][newCiy].distance;
                    path[newCiy] = minIndex;
                }
        }
    }

    if(printToFile==1)
        fprintf(file,"\nShortest path by Dijkstra's algorithm:\n");
    else
        printf("\nShortest path by Dijkstra's algorithm:\n");


    while (current != -222) //loop for printing
    {
        int valid = (distances[current] - distances[path[current]]);
        if(printToFile==1)
        {
            if(valid > 0)
                fprintf(file,"%s <--(%dkm)--", cities[current].name, valid);
            else
                fprintf(file,"%s <--(0km)--", cities[current].name);
        }
        else
        {
            if(valid > 0)
                printf("%s <--(%dkm)--", cities[current].name, valid);
            else
                printf("%s <--(0km)--", cities[current].name);
        }

        current = path[current];
    }

    if(printToFile==1)
        fprintf(file,"\nTotal distance: %dkm\n", distances[destination]);
    else
        printf("\nTotal distance: %dkm\n", distances[destination]);

    if(printToFile==1)
        fprintf(file,"\n\n");
    else
        printf("\n\n");
    fclose(file);
}

void bfs(int source, int destination, int printToFile) //BFS "Breadth First Search" algorithm
{
    /*
    visited: array of visited status of the city.
    path: array of previous cities that visited to print the path.
    current: to make a copy of destination.
    queue: Q for BFS.
    front & rear : for Q.
    file: file of store path between cities.
    */
    int visited[MAX_NUM_OF_CITIES], path[MAX_NUM_OF_CITIES], queue[MAX_NUM_OF_CITIES];
    int front = 0, rear = 0;
    int current;
    FILE* file = fopen("shortest_distance.txt", "a");

    for (int i = 0; i < numOfCities; i++) //loop initializing values.
    {
        visited[i] = 0;
        path[i] = -222;
    }

    visited[source] = 1;
    path[source] = -222;

    queue[rear] = source;
    ++rear;

    while (front < rear)
    {
        int current = queue[front];
        front++;

        for (int newCity = 0; newCity < numOfCities; newCity++) //loop compare between source city and other cities.
        {
            if (!visited[newCity] && graph[current][newCity].distance != 0) //update the path.
            {
                visited[newCity] = 1;
                path[newCity] = current;
                queue[rear] = newCity;
                rear++;
            }
        }
    }
    if(printToFile==1)
        fprintf(file,"Shortest path using Breadth First Search (BFS):\n");
    else
        printf("Shortest path using Breadth First Search ""BFS"":\n");

    current = destination;
    while (current != -222) //loop for printing
    {
        if(printToFile==1)
            fprintf(file,"%s <----", cities[current].name);
        else
            printf("%s <----", cities[current].name);

        current = path[current];
    }

    if(printToFile==1)
        fprintf(file,"\n\n");
    else
        printf("\n\n");
    fclose(file);
}


int getIndex(char name[]) //return index of given city.
{
    for(int i=0; i<numOfCities; i++) //loop to check if given city is excited or not.
    {
        if(strcmp(cities[i].name,name) == 0)
            return i;
        else
            continue;
    }
    return -20;
}

void menu() //menu contents.
{
    printf("\n=========Menu===========\n");
    printf("1. Load cities from Cities.txt\n");
    printf("2. Enter source City name.\n");
    printf("3. Enter destination.\n");
    printf("4. Exit and Save Shortest Path to shortest_distance.txt.\n");
    printf("Choose number of option: ");
}

void controller() //controls
{
    /*
    op: option chosen
    s: index of source
    d: index of destination.
    name: city's name
    file: storing file
    */
    int op;
    int s = -200;
    int d = -200;
    char name[30];
    FILE* file;

    while (1) //loop control state of option
    {
        menu();
        scanf("%d", &op);

        if(op==4) //exit and save to file case
        {
            if (s != -200 && d != -200) //means source and destinations cities excited.
            {
                file = fopen("shortest_distance.txt", "a");
                fprintf(file, "Shortest path:\n");
                fprintf(file, "Source: %s\n", cities[s].name);
                fprintf(file, "Destination: %s\n", cities[d].name);
                fclose(file);
                dijkstra(s, d,1);
                bfs(s, d,1);
            }
            break;
        }

        if (op==1) //load file case
        {
            loadFile();
            printf("\nCities: \n");
            for (int i = 0; i < numOfCities; i++) //loop prints all loaded cities.
            {
                printf("%s\n",cities[i].name);
            }
        }
        else if (op==2) //entering source city name case
        {
            printf("Enter the name of the source city: ");
            scanf("%s",name);
            s = getIndex(name);

            if(s==-20)
            {
                printf("city is not excited!\n\n");
                continue;
            }

            if (s >= numOfCities)
            {
                printf("Invalid source city \n");
                s = -200;
            }
        }

        else if (op==3) //entering destination city name case
        {
            if(s < 0)
            {
                printf("Please enter the source city first\n");
                continue;
            }
            printf("Enter the name of the destination city: ");
            scanf("%s",name);
            d = getIndex(name);

            if(d==-20)
            {
                printf("city is not excited!\n\n");
                continue;
            }

            else if (s == -200)
            {
                printf("Please enter the source city first\n");
                d = -200;
            }
            else
            {
                dijkstra(s, d,0);
                bfs(s, d,0);
            }
        }

        else
            printf("Invalid option\n");
    }
}

int main()
{
    printf("\n\n===============================Welcome to Shortest Path Program=================================\n\n");

    controller();

    printf("\n\n===============================THX=================================\n\n");

    return 0;
}
