package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
    file, err := os.Open("input.txt")
    if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
    }
    defer file.Close()

    size := 1000
    grid1 := make([][]bool, size)
    for i := 0; i < size; i++ {
        grid1[i] = make([]bool, 1000)
    }

    grid2 := make([][]int, size)
    for i := 0; i < size; i++ {
        grid2[i] = make([]int, 1000)
    }

    const (
        On = iota
        Off
        Toggle
    )

    var action int
    var start []string
    var end []string

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.Split(scanner.Text(), " ")
        if line[0] == "turn" {
            if line[1] == "on" {
                action = On
            }
            if line[1] == "off" {
                action = Off
            }

            start = strings.Split(line[2], ",")
            end = strings.Split(line[4], ",")
        }
        if line[0] == "toggle" {
            action = Toggle

            start = strings.Split(line[1], ",")
            end = strings.Split(line[3], ",")
        }

        startX, err := strconv.ParseInt(start[0], 10, 16)
        startY, err := strconv.ParseInt(start[1], 10, 16)
        endX, err := strconv.ParseInt(end[0], 10, 16)
        endY, err := strconv.ParseInt(end[1], 10, 16)
        if err != nil {
            fmt.Printf("Error parsing coordinates: %v", err)
            os.Exit(1)
        }

        for x := startX; x <= endX; x++ {
            for y := startY; y <= endY; y++ {
                switch action {
                case On:
                    grid1[y][x] = true
                    grid2[y][x]++
                case Off:
                    grid1[y][x] = false
                    if grid2[y][x] > 0 {
                        grid2[y][x]--
                    }
                case Toggle:
                    grid1[y][x] = !grid1[y][x]
                    grid2[y][x] += 2
                }
            }
        }
    }

    count := 0
    brightness := 0
    for y := 0; y < size; y++ {
        for x := 0; x < size; x++ {
            if grid1[y][x] {
                count++
            }
            brightness += grid2[y][x]
        }
    }

    fmt.Printf("Part 1: %d\n", count)
    fmt.Printf("Part 2: %d\n", brightness)

    if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
    }
}
