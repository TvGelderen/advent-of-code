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
    maxDistance := -1
    for city := range cities {
        minDist, maxDist := travel(cities, []string{ city }, 0)
        if minDistance == -1 || minDist < minDistance {
            minDistance = minDist
        }
        if maxDist > maxDistance {
            maxDistance = maxDist
        }
    }

    fmt.Printf("Part 1: %d\n", minDistance)
    fmt.Printf("Part 1: %d\n", maxDistance)

	if err = scanner.Err(); err != nil {
		log.Fatalf("Error reading from file: %v\n", err)
	}
}

func travel(cities map[string][]City, visited []string, distance int) (int, int) {
    current := visited[len(visited)-1]
    minDistance := -1
    maxDistance := -1

    for _, city := range cities[current] {
        if !slices.Contains(visited, city.Name) {
            minDist, maxDist := travel(cities, append(visited, city.Name), distance + city.Distance)
            if minDistance == -1 || minDist < minDistance {
                minDistance = minDist
            }
            if maxDist > maxDistance {
                maxDistance = maxDist
            }
       }
    }
    
    if minDistance == -1 {
        if maxDistance == -1 {
            return distance, distance
        }
        return distance, maxDistance
    } else if maxDistance == -1 {
        return minDistance, distance
    }

    return minDistance, maxDistance
}
