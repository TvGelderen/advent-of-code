package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

type City struct {
	Name     string
	Distance int
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("Unable to open file: %v", err)
	}
	defer file.Close()

	cities := make(map[string][]City)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.Split(scanner.Text(), " = ")
        lhs := strings.Split(line[0], " ")
        firstCity := lhs[0]
        secondCity := lhs[2]
		distance, err := strconv.ParseInt(line[1], 10, 32)
		if err != nil {
			log.Fatalf("Error parsing distance: %v", err)
		}

        cities[firstCity] = append(cities[firstCity], City{
            Name: secondCity,
            Distance: int(distance),
        })
        cities[secondCity] = append(cities[secondCity], City{
            Name: firstCity,
            Distance: int(distance),
        })
	}

    minDistance := -1
    for city := range cities {
        distance := travel(cities, []string{ city }, 0)
        if minDistance == -1 || distance < minDistance {
            minDistance = distance
        }
    }

    fmt.Printf("Part 1: %d\n", minDistance)

	if err = scanner.Err(); err != nil {
		log.Fatalf("Error reading from file: %v\n", err)
	}
}

func travel(cities map[string][]City, visited []string, distance int) int {
    current := visited[len(visited)-1]
    minDistance := -1

    for _, city := range cities[current] {
        if !slices.Contains(visited, city.Name) {
            dist := travel(cities, append(visited, city.Name), distance + city.Distance)
            if minDistance == -1 || dist < minDistance {
                minDistance = dist
            }
       }
    }
    
    if minDistance == -1 {
        return distance
    }

    return minDistance
}
