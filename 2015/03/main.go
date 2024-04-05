package main

import (
	"bufio"
	"fmt"
	"os"
)

type Coordinate struct {
	x int16
	y int16
}

func main() {
    part1()
    part2()
}

func part1() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
	}
	defer file.Close()

	var x int16 = 0
	var y int16 = 0
	houses := []Coordinate{
		{
			x: 0,
			y: 0,
		},
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		for _, ch := range scanner.Text() {
			switch ch {
			case '^':
				y++
			case '>':
				x++
			case 'v':
				y--
			case '<':
				x--
			}

			visited := false
			for _, house := range houses {
				if house.x == x && house.y == y {
					visited = true
					break
				}
			}

			if !visited {
				houses = append(houses, Coordinate{
					x: x,
					y: y,
				})
			}
		}
	}

	fmt.Printf("Part 1: %d\n", len(houses))

	if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
	}
}

func part2() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
	}
	defer file.Close()

	x := []int16{0, 0}
	y := []int16{0, 0}
	houses := []Coordinate{
		{
			x: 0,
			y: 0,
		},
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		for idx, ch := range scanner.Text() {
			i := idx % 2
			switch ch {
			case '^':
				y[i]++
			case '>':
				x[i]++
			case 'v':
				y[i]--
			case '<':
				x[i]--
			}

			visited := false
			for _, house := range houses {
				if house.x == x[i] && house.y == y[i] {
					visited = true
					break
				}
			}

			if !visited {
				houses = append(houses, Coordinate{
					x: x[i],
					y: y[i],
				})
			}
		}
	}

	fmt.Printf("Part 2: %d\n", len(houses))

	if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
	}
}
